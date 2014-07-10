// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PinOverModelExample.h"

#include "RegularTexturePageLayout.h"
#include "RenderContext.h"
#include "Node.h"
#include "EffectHandler.h"
#include "RenderQueue.h"

namespace Examples
{
PinOverModelExample::PinOverModelExample(
    Eegeo::Helpers::ITextureFileLoader& textureLoader,
    Eegeo::Rendering::GlBufferPool& glBufferPool,
    Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
    Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
    Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
    Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
    Eegeo::Rendering::RenderableFilters& renderableFilters,
    const Eegeo::Camera::ICameraProvider& cameraProvider,
    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
    Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
    Eegeo::Rendering::RenderContext& renderContext,
    Eegeo::Helpers::IFileIO& fileIO,
    Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
    Eegeo::Lighting::GlobalFogging& fogging,
    Eegeo::Rendering::Materials::NullMaterial& nullMat,
    Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController
)
	:m_pin0UserData("Pin Zero(0) User Data")
	,m_pPin0(NULL)
	,m_renderContext(renderContext)
	,m_fileIO(fileIO)
	,m_textureRequestor(textureRequestor)
	,m_pModel(NULL)
	,m_globalFogging(fogging)
	,m_renderableFilters(renderableFilters)
	,m_nullMat(nullMat)
	,m_globeCameraStateRestorer(cameraController)
{
	textureLoader.LoadTexture(m_pinIconsTexture, "pin_over_model_example/PinIconTexturePage.png", true);
	Eegeo_ASSERT(m_pinIconsTexture.textureId != 0);

	// This example uses a texture page containing 2 x 2 icons.
	// Increase the following number to use a texture page containing more icons
	// (e.g. 3 for a page containing 3 x 3 icons)
	int numberOfTilesAlongEachAxisOfTexturePage = 2;
	m_pPinIconsTexturePageLayout = Eegeo_NEW(Eegeo::Rendering::RegularTexturePageLayout)(numberOfTilesAlongEachAxisOfTexturePage);

	// The following values specify the size and shape of the Pins within the 3D world.
	int spriteWidthInMetres = 100;
	int spriteHeightInMetres = 100;

	// N.B. The implementation for PinModule is given in PinModule.h as a guide for Apps that
	// require an alternate configuration of the various Pin related components.
	m_pPinsModule = Eegeo_NEW(Eegeo::Pins::PinsModule)(
	                    m_pinIconsTexture.textureId,
	                    *m_pPinIconsTexturePageLayout,
	                    glBufferPool,
	                    shaderIdGenerator,
	                    materialIdGenerator,
	                    vertexBindingPool,
	                    vertexLayoutPool,
	                    renderableFilters,
	                    cameraProvider,
	                    terrainHeightProvider,
	                    spriteWidthInMetres,
	                    spriteHeightInMetres,
	                    Eegeo::Rendering::LayerIds::PlaceNames,
	                    environmentFlatteningService
	                );

	CreateExamplePins();
}

PinOverModelExample::~PinOverModelExample()
{
	// Delete the PinsModule and all of its underlying components.
	// N.B. Deleting the PinRepository will delete all Pins it contains.
	// However, responsibility for managing the lifetime of any user data on those Pins is the responsbility
	// of the App.
	Eegeo_DELETE(m_pPinsModule);

	// Delete the icon texture and its layout.
	Eegeo_DELETE m_pPinIconsTexturePageLayout;
	glDeleteTextures(1, &m_pinIconsTexture.textureId);

	m_renderableFilters.RemoveRenderableFilter(m_pMyRenderableFilter);

	Eegeo_DELETE m_pMyRenderableFilter;
	Eegeo_DELETE m_pMyModelRenderable;
}

void PinOverModelExample::CreateExamplePins()
{
	// Get the repository of all currently active Pins.
	Eegeo::Pins::PinRepository& pinRepository = m_pPinsModule->GetRepository();

	// Create test pins and add them to the repository.
	Eegeo::Pins::TPinId pin0Id = 0;
	Eegeo::Space::LatLong pin0Location = Eegeo::Space::LatLong::FromDegrees(37.7858,-122.401);
	int pin0Icon = 0;
	Eegeo::Pins::Pin* pPin0 = Eegeo_NEW(Eegeo::Pins::Pin)(pin0Id, pin0Location, 30, pin0Icon, &m_pin0UserData);
	pinRepository.AddPin(pPin0);

	m_pPin0 = pPin0;
}

void PinOverModelExample::Start()
{
	m_pModel = Eegeo::Model::CreateFromPODFile("pin_over_model_example/Test_ROBOT_ARM.pod", m_fileIO, m_renderContext.GetGLState(), &m_textureRequestor, "pin_over_model_example/");
	Eegeo_ASSERT(m_pModel->GetRootNode());

	m_pMyModelRenderable = Eegeo_NEW (MyModelRenderable)(*m_pModel, m_renderContext, m_globalFogging, m_nullMat);
	m_pMyRenderableFilter = Eegeo_NEW (MyRenderableFilter)(*m_pMyModelRenderable);
	m_renderableFilters.AddRenderableFilter(m_pMyRenderableFilter);
}

void PinOverModelExample::Suspend()
{
	delete m_pModel;
	m_pModel = NULL;
}

void PinOverModelExample::Update(float dt)
{
	// Update the PinsModule to query terrain heights and update screen space coordinats for the Pins.
	m_pPinsModule->Update(dt);

	m_pModel->UpdateAnimator(1.0f/30.0f);
}

void PinOverModelExample::Draw()
{
}

PinOverModelExample::MyModelRenderable::MyModelRenderable(Eegeo::Model& model,
        Eegeo::Rendering::RenderContext& renderContext,
        Eegeo::Lighting::GlobalFogging& globalFogging,
        Eegeo::Rendering::Materials::NullMaterial& nullMat)
	: Eegeo::Rendering::RenderableBase(Eegeo::Rendering::LayerIds::Buildings,
	                                   Eegeo::Space::LatLong::FromDegrees(37.7858,-122.401).ToECEF(),
	                                   &nullMat)
	, m_model(model)
	, m_renderContext(renderContext)
	, m_globalFogging(globalFogging)
{

}

void PinOverModelExample::MyModelRenderable::Render(Eegeo::Rendering::GLState& glState) const
{
	Eegeo::m44 transform;
	Eegeo::dv3 location = Eegeo::Space::LatLong::FromDegrees(37.7858,-122.401).ToECEF();
	Eegeo::v3 up(location.Norm().ToSingle());
	Eegeo::v3 forward = (location  - Eegeo::v3(0.f, 1.f, 0.f)).Norm().ToSingle();
	Eegeo::v3 right(Eegeo::v3::Cross(up, forward).Norm());
	forward = Eegeo::v3::Cross(up, right);
	Eegeo::v3 cameraRelativePos = (location - m_renderContext.GetCameraOriginEcef()).ToSingle();
	Eegeo::m44 scaleMatrix;
	scaleMatrix.Scale(1.f);
	Eegeo::m44 cameraRelativeTransform;
	cameraRelativeTransform.SetFromBasis(right, up, forward, cameraRelativePos);
	Eegeo::m44::Mul(transform, cameraRelativeTransform, scaleMatrix);
	transform.SetRow(3, Eegeo::v4(cameraRelativePos, 1.f));

	glState.DepthTest.Enable();
	glState.DepthFunc(GL_LEQUAL);

	//loaded model faces are ccw
	glState.FrontFace(GL_CCW);

	m_model.GetRootNode()->SetVisible(true);
	m_model.GetRootNode()->SetLocalMatrix(transform);
	m_model.GetRootNode()->UpdateRecursive();
	m_model.GetRootNode()->UpdateSphereRecursive();
	m_model.GetRootNode()->DrawRecursive(m_renderContext, m_globalFogging, NULL, true, false);

	glState.FrontFace(GL_CW);

	Eegeo::EffectHandler::Reset();
}

PinOverModelExample::MyRenderableFilter::MyRenderableFilter(Eegeo::Rendering::RenderableBase& renderable)
	: m_renderable(renderable)
{

}
void PinOverModelExample::MyRenderableFilter::EnqueueRenderables(Eegeo::Rendering::RenderContext& renderContext,
        Eegeo::Rendering::RenderQueue& renderQueue)
{
	renderQueue.EnqueueRenderable(m_renderable);
}
}
