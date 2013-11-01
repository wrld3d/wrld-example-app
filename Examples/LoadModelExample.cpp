#include "LoadModelExample.h"
#include "ShaderCompiler.h"
#include <sys/time.h>

namespace Examples
{
    LoadModelExample::LoadModelExample(Eegeo::Rendering::RenderContext& renderContext,
                                       Eegeo::Space::LatLongAltitude interestLocation,
                                       Eegeo::Helpers::IFileIO& fileIO,
                                       Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                       Eegeo::Lighting::GlobalFogging& fogging)
    :renderContext(renderContext)
    ,interestLocation(interestLocation)
    ,fileIO(fileIO)
    ,textureLoader(textureLoader)
    ,pModel(NULL)
    ,boundsVisualiser(renderContext)
    ,globalFogging(fogging)
    {
        
    }
    
    void LoadModelExample::Start()
    {
        pModel = new Eegeo::Model(renderContext.GetGLState(), textureLoader, fileIO);
        
        //this is a .pod resource file included in the build
        pModel->Load("SanFrancisco_Vehicles.pod");
        
        //the layout of this resource is assumed - a "Vehicles" node should exist
        Eegeo::Node* parentNode = pModel->FindNode("Vehicles");
        Eegeo_ASSERT(parentNode);
        
        //it should have some children, which are the vehicle meshes...
        Eegeo_ASSERT(parentNode->GetNumChildNodes() > 0);

        //select a random vehicle
        srand(time(NULL));
        mesh.node = parentNode->GetChildNode(rand() % parentNode->GetNumChildNodes());;
    }
    
    void LoadModelExample::Suspend()
    {
        //destroy the example...
        mesh.node = NULL;
        
        delete pModel;
        pModel = NULL;
    }
    
    void LoadModelExample::Update()
    {
        //let's put the vehicle in the air
        interestLocation.SetAltitude(37.0f);
        
        //put the vehicle at interest point
        mesh.positionEcef = interestLocation.ToECEF();
        
        //up is relative to earth location, normal to tangent plane formed at surface below model
        mesh.up = mesh.positionEcef.Norm().ToSingle();
        
        //cross with north pole (0,1,0) for a forward vector
        mesh.forward = Eegeo::v3::Cross(mesh.up, Eegeo::v3(0.0f, 1.0f, 0.0f));
        
        //set some big scale value so we can see the vehicle - vary between x20 and x70
        struct timeval time;
        gettimeofday(&time, NULL);
        mesh.scale = 20.0f + ((sin(time.tv_sec)/ 2.0f + 0.5) * 50.0f);
    }
    
    void LoadModelExample::Draw()
    {
        //form basis
        Eegeo::v3 up(mesh.up);
        Eegeo::v3 forward = -mesh.forward; //model is facing reverse (-ve z)
        Eegeo::v3 right(Eegeo::v3::Cross(up, forward).Norm());
        up = Eegeo::v3::Cross(forward, right);
        
       
        //compute a camera local position
        Eegeo::v3 cameraRelativePos = (mesh.positionEcef - renderContext.GetCameraOriginEcef()).ToSingle();
        
        //generate a transform from this basis and position...
        Eegeo::m44 cameraRelativeTransform;
        cameraRelativeTransform.SetFromBasis(right, up, forward, cameraRelativePos);
        
        Eegeo::m44 scaleMatrix;
        scaleMatrix.Scale(mesh.scale);
        
        //...and scale
        Eegeo::m44 transform;
        Eegeo::m44::Mul(transform, cameraRelativeTransform, scaleMatrix);
        transform.SetRow(3, Eegeo::v4(cameraRelativePos, 1.0f));
        
        //update the mesh instance with the transform
        mesh.node->SetLocalMatrix(transform);
        mesh.node->UpdateRecursive();
        mesh.node->UpdateSphereRecursive();
        mesh.node->UpdateBBRecursive();
        
        //draw the mesh
        mesh.node->Draw(renderContext, globalFogging);
        
        Eegeo::v3 min, max;
        mesh.node->GetMinExtent(min);
        mesh.node->GetMaxExtent(max);
        boundsVisualiser.Draw(min, max);
    }
    
    BoundsVisualiser::BoundsVisualiser(Eegeo::Rendering::RenderContext& renderContext)
    :renderContext(renderContext)
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
            vertexBuffer[i].x = verts[i].GetX();
            vertexBuffer[i].y = verts[i].GetY();
            vertexBuffer[i].z = verts[i].GetZ();
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
        Eegeo::m44::Mul(mvp, renderContext.GetViewProjectionMatrix(), w);
        
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
