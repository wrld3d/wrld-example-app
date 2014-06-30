// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PinsWithAttachedJavaUIExample.h"
#include "RegularTexturePageLayout.h"
#include "VectorMath.h"
#include "Pin.h"
#include "Logger.h"
#include "Geometry.h"

namespace Examples
{
PinsWithAttachedJavaUIExample::PinsWithAttachedJavaUIExample(
    Eegeo::EegeoWorld& world,
    AndroidNativeState& nativeState,
    Eegeo::Rendering::RenderContext& renderContext,
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
    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController
)
	: m_nativeState(nativeState)
	, m_renderContext(renderContext)
	, m_world(world)
	, m_buttonID(0)
	, m_hudPinControllerClass(NULL)
	, m_hudPinController(NULL)
	, m_updateLocationMethodId(NULL)
	, m_pinUserData("Pin User Data")
	, m_globeCameraStateRestorer(globeCameraController)
{
	textureLoader.LoadTexture(m_pinIconsTexture, "pins_with_attached_java_ui_example/PinIconTexturePage.png", true);
	Eegeo_ASSERT(m_pinIconsTexture.textureId != 0);

	int numberOfTilesAlongEachAxisOfTexturePage = 2;
	m_pPinIconsTexturePageLayout = Eegeo_NEW(Eegeo::Rendering::RegularTexturePageLayout)(
	                                   numberOfTilesAlongEachAxisOfTexturePage);

	// The following values specify the size and shape of the Pins within the 3D world.
	int spriteWidthInMetres = 100;
	int spriteHeightInMetres = 100;

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
	                    environmentFlatteningService);

	CreateExamplePins();
}

PinsWithAttachedJavaUIExample::~PinsWithAttachedJavaUIExample()
{
	Eegeo_DELETE(m_pPinsModule);

	// Delete the icon texture and its layout.
	Eegeo_DELETE m_pPinIconsTexturePageLayout;
	glDeleteTextures(1, &m_pinIconsTexture.textureId);
}

void PinsWithAttachedJavaUIExample::CreateExamplePins()
{
	// Get the repository of all currently active Pins.
	Eegeo::Pins::PinRepository& pinRepository = m_pPinsModule->GetRepository();

	// Create test pin and add it to the repository.
	Eegeo::Pins::TPinId pinId = 0;
	Eegeo::Space::LatLong pinLocation = Eegeo::Space::LatLong::FromDegrees(37.7858,-122.401);
	int pinIcon = 0;
	Eegeo::Pins::Pin* pPin = Eegeo_NEW(Eegeo::Pins::Pin)(pinId, pinLocation, 0, pinIcon, &m_pinUserData);
	pinRepository.AddPin(pPin);
}

void PinsWithAttachedJavaUIExample::Start()
{
	EXAMPLE_LOG("PinsWithAttachedJavaUIExample::Start()");
}

void PinsWithAttachedJavaUIExample::Suspend()
{
	//if we have not started and don't have a pin handle, nothing to do in suspend()
	if(m_buttonID == 0)
	{
		return;
	}

	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the method to remove a pin, and remove the pins with our cached IDs
	jmethodID removeJavaPinButton = env->GetMethodID(m_hudPinControllerClass, "removeJavaPinButton", "(I)V");

	env->CallVoidMethod(m_hudPinController, removeJavaPinButton, m_buttonID);

	//delete the persistent references to the class and object
	env->DeleteGlobalRef(m_hudPinControllerClass);
	env->DeleteGlobalRef(m_hudPinController);

	//reset the button handle
	m_buttonID = 0;
}

void PinsWithAttachedJavaUIExample::Update(float dt)
{
	// Update the PinsModule to query terrain heights and update screen space coordinates for the Pins.
	m_pPinsModule->Update(dt);
}

void PinsWithAttachedJavaUIExample::Draw()
{
	//lazily create the pin button when we start drawing so it is not displayed on top of the loading screen
	if(m_world.Initialising())
	{
		return;
	}
	else if(m_buttonID == 0)
	{
		CreateJavaUIButton();
	}

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	Eegeo_ASSERT(m_buttonID != 0);

	// Get the pin position on the screen
	Eegeo::Pins::PinRepository& pinRepo = m_pPinsModule->GetRepository();
	Eegeo::Pins::Pin* pPin = pinRepo.GetPinAtIndex(0);
	Eegeo_ASSERT(pPin != NULL);

	Eegeo::Pins::PinController& pinController = m_pPinsModule->GetController();
	Eegeo::Geometry::Bounds2D pinScreenBounds = Eegeo::Geometry::Bounds2D::Empty();
	pinController.GetScreenBoundsForPin(*pPin, pinScreenBounds);
	Eegeo::v2 screenPosition = pinScreenBounds.center();

	// now update the java ui to be in sync with the pin, positioned above it on screen.
	// the pixel nudging is hard-coded for simplicity; you should probably do something more sophisticated
	// (based on the size of your pin & java ui assets)
	const int buttonOffsetPixelsX = 40;
	const int buttonOffsetPixelsY = 110;

	env->CallVoidMethod(
	    m_hudPinController,
	    m_updateLocationMethodId,
	    m_buttonID,
	    screenPosition.GetX() - buttonOffsetPixelsX,
	    screenPosition.GetY() - buttonOffsetPixelsY
	);
}

bool PinsWithAttachedJavaUIExample::Event_TouchTap(const AppInterface::TapData& data)
{
	Eegeo::v2 screenTapPoint = Eegeo::v2(data.point.GetX(), data.point.GetY());

	Eegeo_TTY("Searching for Pins intersecting tap point %d,%d...", (int) screenTapPoint.GetX(), (int) screenTapPoint.GetY());

	Eegeo::Pins::PinController& pinController = m_pPinsModule->GetController();
	std::vector<Eegeo::Pins::Pin*> intersectingPinsClosestToCameraFirst;
	if(pinController.TryGetPinsIntersectingScreenPoint(screenTapPoint, intersectingPinsClosestToCameraFirst))
	{
		Eegeo_TTY("found %ld :\n", intersectingPinsClosestToCameraFirst.size());

		for(std::vector<Eegeo::Pins::Pin*>::const_iterator it = intersectingPinsClosestToCameraFirst.begin(); it != intersectingPinsClosestToCameraFirst.end(); ++it)
		{
			Eegeo::Pins::Pin* pPin = *it;

			Eegeo_TTY("\tId=%d, User Data='%s'\n", pPin->GetId(), ((std::string*) pPin->GetUserData())->c_str());
		}

		return true;
	}
	else
	{
		Eegeo_TTY("none found.\n");
		return false;
	}
}

void PinsWithAttachedJavaUIExample::CreateJavaUIButton()
{
	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the java HudPinController class
	jstring strClassName = env->NewStringUTF("com/eegeo/examples/hudpincontroller/HudPinController");
	jclass hudPinControllerClass = m_nativeState.LoadClass(env, strClassName);
	env->DeleteLocalRef(strClassName);

	//create a persistent reference to the class
	m_hudPinControllerClass = static_cast<jclass>(env->NewGlobalRef(hudPinControllerClass));

	//cache the update method as we will call it frequently
	m_updateLocationMethodId = env->GetMethodID(m_hudPinControllerClass, "updatePinButtonScreenLocation", "(IFF)V");

	//get the method to add a pin - only keep a local reference as we wont use again
	jmethodID addJavaPinButton = env->GetMethodID(m_hudPinControllerClass, "addJavaPinButton", "()I");

	//get the constructor for the HudPinController, which takes the activity as a parameter
	jmethodID hudPinControllerConstructor = env->GetMethodID(m_hudPinControllerClass, "<init>", "(Lcom/eegeo/MainActivity;)V");

	//construct an instance of the HudPinController, and create and cache a persistent reference to it.
	//we will make calls on to this instance, and it will add elements to the UI for us form Java.
	jobject instance = env->NewObject(m_hudPinControllerClass, hudPinControllerConstructor, m_nativeState.activity);
	m_hudPinController = env->NewGlobalRef(instance);

	//use the addJavaPinButton method on the hudPinController instance to add a pin to the hud.
	//we will get back an integer reference to the pin which we can use to update and remove it later,
	//so cache this
	m_buttonID = env->CallIntMethod(m_hudPinController, addJavaPinButton);
}
}



