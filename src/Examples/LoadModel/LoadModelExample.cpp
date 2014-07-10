// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "LoadModelExample.h"
#include "ShaderCompiler.h"
#include "Model.h"
#include "ModelMaterial.h"
#include "Mesh.h"
#include "Node.h"
#include <sys/time.h>

namespace Examples
{
const size_t BoundsVisualiser::NumVerts = 8;
const size_t BoundsVisualiser::NumIndices = 36;

LoadModelExample::LoadModelExample(Eegeo::Rendering::RenderContext& renderContext,
                                   Eegeo::Space::LatLongAltitude interestLocation,
                                   Eegeo::Helpers::IFileIO& fileIO,
                                   Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                                   Eegeo::Lighting::GlobalFogging& fogging,
                                   Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_renderContext(renderContext)
	,m_interestLocation(interestLocation)
	,m_fileIO(fileIO)
	,m_textureRequestor(textureRequestor)
	,m_pModel(NULL)
	,m_boundsVisualiser(renderContext)
	,m_globalFogging(fogging)
	,m_pDiscMaterial(NULL)
	,m_elapsedTime(0.0f)
	,m_globeCameraStateRestorer(cameraController)
{
}

void LoadModelExample::Start()
{
	m_pModel = Eegeo::Model::CreateFromPODFile("load_model_example/sanfrancisco_vehicles_alpha.POD", m_fileIO, m_renderContext.GetGLState(), &m_textureRequestor, "load_model_example/");

	//the layout of this resource is assumed - a "Vehicles" node should exist
	Eegeo::Node* parentNode = m_pModel->FindNode("Vehicles");
	Eegeo_ASSERT(parentNode);

	// Print details of the materials in the POD.
	for(int i = 0; i < m_pModel->GetNumMaterials(); i++)
	{
		Eegeo::ModelMaterial* pMaterial = m_pModel->GetMaterial(i);
		Eegeo_TTY(
		    "Material: %s %s alpha=%f\n",
		    pMaterial->GetName().c_str(),
		    (pMaterial->GetMaterialFlags() & Eegeo::kMaterialFlag_Blend) ? "blended" : "opaque",
		    pMaterial->GetAlpha()
		);
	}

	// Look up the material for the disc so that we can animate its alpha value.
	if(!m_pModel->TryGetMaterialByName("load_model_example/alpha_disc_material", m_pDiscMaterial))
	{
		Eegeo_TTY("Failed to find disc material.\n");
	}

	//it should have some children, which are the vehicle meshes...
	Eegeo_ASSERT(parentNode->GetNumChildNodes() > 0);

	//select a vehicle.
	m_mesh.m_pNode = parentNode->GetChildNode(0);
}

void LoadModelExample::Suspend()
{
	//destroy the example...
	m_mesh.m_pNode = NULL;

	delete m_pModel;
	m_pModel = NULL;
}

void LoadModelExample::Update(float dt)
{
	//let's put the vehicle in the air
	m_interestLocation.SetAltitude(100.0f);

	//put the vehicle at interest point
	m_mesh.m_positionEcef = m_interestLocation.ToECEF();

	//up is relative to earth location, normal to tangent plane formed at surface below model
	m_mesh.m_up = m_mesh.m_positionEcef.Norm().ToSingle();

	//cross with north pole (0,1,0) for a forward vector
	m_mesh.m_forward = Eegeo::v3::Cross(m_mesh.m_up, Eegeo::v3(0.0f, 1.0f, 0.0f));

	//set some big scale value so we can see the vehicle - vary between x20 and x70
	m_mesh.m_scale = 20.0f + ((sin(m_elapsedTime)/ 2.0f + 0.5) * 50.0f);

	// pulse the opacity of the disk material up and down over time.
	if(m_pDiscMaterial != NULL)
	{
		m_pDiscMaterial->SetAlpha(fabs(sin(m_elapsedTime * 2)));
	}

	m_elapsedTime += dt;
}

void LoadModelExample::Draw()
{
	//form basis
	Eegeo::v3 up(m_mesh.m_up);
	Eegeo::v3 forward = -m_mesh.m_forward; //model is facing reverse (-ve z)
	Eegeo::v3 right(Eegeo::v3::Cross(up, forward).Norm());
	up = Eegeo::v3::Cross(forward, right);

	//compute a camera local position
	Eegeo::v3 cameraRelativePos = (m_mesh.m_positionEcef - m_renderContext.GetCameraOriginEcef()).ToSingle();

	//generate a transform from this basis and position...
	Eegeo::m44 cameraRelativeTransform;
	cameraRelativeTransform.SetFromBasis(right, up, forward, cameraRelativePos);

	Eegeo::m44 scaleMatrix;
	scaleMatrix.Scale(m_mesh.m_scale);

	//...and scale
	Eegeo::m44 transform;
	Eegeo::m44::Mul(transform, cameraRelativeTransform, scaleMatrix);
	transform.SetRow(3, Eegeo::v4(cameraRelativePos, 1.0f));

	//update the mesh instance with the transform
	m_mesh.m_pNode->SetLocalMatrix(transform);
	m_mesh.m_pNode->UpdateRecursive();
	m_mesh.m_pNode->UpdateSphereRecursive();
	m_mesh.m_pNode->UpdateBBRecursive();

	// Enable z buffering.
	Eegeo::Rendering::GLState& glState = m_renderContext.GetGLState();
	glState.DepthTest.Enable();
	glState.DepthFunc(GL_LEQUAL);
	glState.DepthMask(GL_TRUE);

	//draw the mesh
	m_mesh.m_pNode->DrawRecursive(m_renderContext, m_globalFogging, NULL, true, true);

	Eegeo::v3 min, max;
	m_mesh.m_pNode->GetMinExtent(min);
	m_mesh.m_pNode->GetMaxExtent(max);
	m_boundsVisualiser.Draw(min, max);
}

BoundsVisualiser::BoundsVisualiser(Eegeo::Rendering::RenderContext& renderContext)
	:m_renderContext(renderContext)
{
	CompileShaders();
}

BoundsVisualiser::~BoundsVisualiser()
{
	delete m_pShader;
	m_pShader = NULL;
}

std::string BoundsVisualiser::VertexShader()
{
	return
	    "attribute vec3 pos;\n"
	    "uniform mat4 mvp;\n"
	    "void main(void) { \n"
	    "gl_Position = mvp * vec4(pos.xyz, 1.0);\n"
	    "}";
}

std::string BoundsVisualiser::FragmentShader()
{
	return
	    "void main(void) { \n"
	    "gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0); \n"
	    "}";
}

void BoundsVisualiser::CompileShaders()
{
	std::string vertexShaderCode = VertexShader();
	std::string fragmentShaderCode = FragmentShader();

	GLuint vertexShader = Eegeo::Helpers::ShaderCompiler::CompileShader(vertexShaderCode, GL_VERTEX_SHADER);
	GLuint fragmentShader = Eegeo::Helpers::ShaderCompiler::CompileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

	m_pShader = new Shader;
	m_pShader->m_programHandle = glCreateProgram();
	glAttachShader(m_pShader->m_programHandle, vertexShader);
	glAttachShader(m_pShader->m_programHandle, fragmentShader);
	glLinkProgram(m_pShader->m_programHandle);

	GLint linkSuccess;
	glGetProgramiv(m_pShader->m_programHandle, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE)
	{
		GLchar messages[256];
		glGetProgramInfoLog(m_pShader->m_programHandle, sizeof(messages), 0, &messages[0]);
		Eegeo_TTY("%s\n", &messages[0]);
		return;
	}

	Eegeo_GL(glUseProgram(m_pShader->m_programHandle));

	m_pShader->m_positionSlot = glGetAttribLocation(m_pShader->m_programHandle, "pos");
	m_pShader->m_mvpUniform = glGetUniformLocation(m_pShader->m_programHandle, "mvp");
}

void BoundsVisualiser::InitMeshGLBuffers(Vertex* verts, u16* indices)
{
	Eegeo_GL(glGenBuffers(1, &m_glVertexBuffer));
	Eegeo_GL(glBindBuffer(GL_ARRAY_BUFFER, m_glVertexBuffer));
	Eegeo_GL(glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex) * NumVerts), verts, GL_STATIC_DRAW));
	Eegeo_GL(glBindBuffer (GL_ARRAY_BUFFER, 0));

	Eegeo_GL(glGenBuffers(1, &m_glIndexBuffer));
	Eegeo_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glIndexBuffer));
	Eegeo_GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(u16) * NumIndices), indices, GL_STATIC_DRAW));
	Eegeo_GL(glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0));
}

void BoundsVisualiser::Build(const Eegeo::v3& minExtents, const Eegeo::v3& maxExtents)
{
	Vertex vertexBuffer[NumVerts];
	u16 indexBuffer[NumIndices];

	float minX = minExtents.GetX();
	float minY = minExtents.GetY();
	float minZ = minExtents.GetZ();
	float maxX = maxExtents.GetX();
	float maxY = maxExtents.GetY();
	float maxZ = maxExtents.GetZ();

	std::vector<Eegeo::v3> verts;
	verts.push_back(Eegeo::v3(minX, minY, minZ));
	verts.push_back(Eegeo::v3(minX, minY, maxZ));
	verts.push_back(Eegeo::v3(minX, maxY, minZ));
	verts.push_back(Eegeo::v3(minX, maxY, maxZ));
	verts.push_back(Eegeo::v3(maxX, minY, minZ));
	verts.push_back(Eegeo::v3(maxX, minY, maxZ));
	verts.push_back(Eegeo::v3(maxX, maxY, minZ));
	verts.push_back(Eegeo::v3(maxX, maxY, maxZ));

	for(size_t i = 0; i < NumVerts; ++ i)
	{
		vertexBuffer[i].m_x = verts[i].GetX();
		vertexBuffer[i].m_y = verts[i].GetY();
		vertexBuffer[i].m_z = verts[i].GetZ();
	}

	indexBuffer[0] = 0;
	indexBuffer[1] = 1;
	indexBuffer[2] = 2;

	indexBuffer[3] = 1;
	indexBuffer[4] = 3;
	indexBuffer[5] = 2;

	indexBuffer[6] = 4;
	indexBuffer[7] = 5;
	indexBuffer[8] = 6;

	indexBuffer[9] = 5;
	indexBuffer[10] = 7;
	indexBuffer[11] = 6;

	indexBuffer[12] = 4;
	indexBuffer[13] = 1;
	indexBuffer[14] = 0;

	indexBuffer[15] = 4;
	indexBuffer[16] = 5;
	indexBuffer[17] = 1;

	indexBuffer[18] = 5;
	indexBuffer[19] = 3;
	indexBuffer[20] = 1;

	indexBuffer[21] = 7;
	indexBuffer[22] = 3;
	indexBuffer[23] = 5;

	indexBuffer[24] = 2;
	indexBuffer[25] = 3;
	indexBuffer[26] = 7;

	indexBuffer[27] = 7;
	indexBuffer[28] = 6;
	indexBuffer[29] = 2;

	indexBuffer[30] = 4;
	indexBuffer[31] = 0;
	indexBuffer[32] = 6;

	indexBuffer[33] = 2;
	indexBuffer[34] = 6;
	indexBuffer[35] = 0;

	InitMeshGLBuffers(vertexBuffer, indexBuffer);
}

void BoundsVisualiser::DestroyGeometry()
{
	Eegeo_GL(glDeleteBuffers(1, &m_glVertexBuffer));
	Eegeo_GL(glDeleteBuffers(1, &m_glIndexBuffer));

	m_glVertexBuffer = 0;
	m_glIndexBuffer = 0;
}

void BoundsVisualiser::Draw(const Eegeo::v3& minExtents, const Eegeo::v3& maxExtents)
{
	Build(minExtents, maxExtents);

	Eegeo_GL(glUseProgram(m_pShader->m_programHandle));

	Eegeo::m44 mvp;
	Eegeo::m44 w;
	w.Identity();
	Eegeo::m44::Mul(mvp, m_renderContext.GetViewProjectionMatrix(), w);

	Eegeo_GL(glUniformMatrix4fv(m_pShader->m_mvpUniform, 1, 0, (const GLfloat*)&mvp));

	Eegeo_GL(glEnableVertexAttribArray(m_pShader->m_positionSlot));

	Eegeo_GL(glBindBuffer(GL_ARRAY_BUFFER, m_glVertexBuffer));
	Eegeo_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glIndexBuffer));

	Eegeo_GL(glVertexAttribPointer(m_pShader->m_positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0));

	for(u32 j = 0; j < NumIndices; j+=3)
	{
		Eegeo_GL(glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_SHORT, (void*)(j * 2)));
	}

	Eegeo_GL(glBindBuffer (GL_ARRAY_BUFFER, 0));
	Eegeo_GL(glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0));

	DestroyGeometry();
}

}
