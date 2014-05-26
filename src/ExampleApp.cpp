//
//  ExampleApp.cpp
//  ExampleApp
//

#include "ExampleApp.h"
#include "GlobeCameraTouchController.h"
#include "RenderCamera.h"
#include "GlobeCameraController.h"
#include "GlobeCameraInterestPointProvider.h"
#include "GlobeCameraController.h"
#include "CameraHelpers.h"

//example factories
#include "CameraTransitionExampleFactory.h"
#include "ControlCityThemeExampleFactory.h"
#include "DebugPrimitiveRenderingExampleFactory.h"
#include "DebugSphereExampleFactory.h"
#include "DynamicText3DExampleFactory.h"
#include "EnvironmentFlatteningExampleFactory.h"
#include "EnvironmentNotifierExampleFactory.h"
#include "FileIOExampleFactory.h"
#include "KeyboardInputExampleFactory.h"
#include "LoadModelExampleFactory.h"
#include "ModifiedRenderingExampleFactory.h"
#include "NavigationGraphExampleFactory.h"
#include "Pick3DObjectExampleFactory.h"
#include "PinOverModelExampleFactory.h"
#include "PinsExampleFactory.h"
#include "PODAnimationExampleFactory.h"
#include "ResourceSpatialQueryExampleFactory.h"
#include "RouteDrawingExampleFactory.h"
#include "RouteSimulationAnimationExampleFactory.h"
#include "RouteThicknessPolicyExampleFactory.h"
#include "ScreenPickExampleFactory.h"
#include "ScreenUnprojectExampleFactory.h"
#include "SearchExampleFactory.h"
#include "SingleCityExampleFactory.h"
#include "ToggleTrafficExampleFactory.h"
#include "TrafficCongestionExampleFactory.h"
#include "WebRequestExampleFactory.h"

ExampleApp::ExampleApp(Eegeo::EegeoWorld* pWorld,
                       Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider& globeCameraInterestPointProvider,
                       Examples::ExampleController& exampleController)
: m_globeCameraController(NULL)
, m_cameraTouchController(NULL)
, m_globeCameraInterestPointProvider(globeCameraInterestPointProvider)
, m_pWorld(pWorld)
, m_exampleController(exampleController)
{
    Eegeo_ASSERT(&m_globeCameraInterestPointProvider != NULL);
    
    Eegeo::EegeoWorld& eegeoWorld = *pWorld;
    
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
    
    // override default configuration to enable two-finger pan gesture to control additional camera pitch
    touchControllerConfig.tiltEnabled = true;
    
    m_cameraTouchController = new Eegeo::Camera::GlobeCamera::GlobeCameraTouchController(touchControllerConfig);
    
    const bool useLowSpecSettings = false;
    Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(useLowSpecSettings);
    
    m_globeCameraController = new Eegeo::Camera::GlobeCamera::GlobeCameraController(eegeoWorld.GetTerrainHeightProvider(),
                                                                                    eegeoWorld.GetEnvironmentFlatteningService(),
                                                                                    eegeoWorld.GetResourceCeilingProvider(),
                                                                                    *m_cameraTouchController,
                                                                                    globeCameraControllerConfig);
    
    
    
    Eegeo::Camera::RenderCamera* renderCamera = m_globeCameraController->GetCamera();
    const Eegeo::Rendering::RenderContext& renderContext = eegeoWorld.GetRenderContext();
    renderCamera->SetViewport(0.f, 0.f, renderContext.GetScreenWidth(), renderContext.GetScreenHeight());
    eegeoWorld.SetCamera(renderCamera);
    
    m_globeCameraInterestPointProvider.SetGlobeCamera(m_globeCameraController);
    
    float interestPointLatitudeDegrees = 37.7858f;
    float interestPointLongitudeDegrees = -122.401f;
    float interestPointAltitudeMeters = 2.7;
    
    Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromDegrees(interestPointLatitudeDegrees,
                                                                                        interestPointLongitudeDegrees,
                                                                                        interestPointAltitudeMeters);
    
    
    
    float cameraControllerOrientationDegrees = 0.0f;
    float cameraControllerDistanceFromInterestPointMeters = 1781.0f;
    
    Eegeo::Space::EcefTangentBasis cameraInterestBasis;
    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location.ToECEF(), cameraControllerOrientationDegrees, cameraInterestBasis);
    
    m_globeCameraController->SetView(cameraInterestBasis, cameraControllerDistanceFromInterestPointMeters);
    
    //register all generic examples
    m_exampleController.RegisterCameraExample<Examples::CameraTransitionExampleFactory>(*m_globeCameraController);
    m_exampleController.RegisterExample<Examples::ControlCityThemeExampleFactory>();
    m_exampleController.RegisterExample<Examples::DebugPrimitiveRenderingExampleFactory>();
    m_exampleController.RegisterExample<Examples::DebugSphereExampleFactory>();
    m_exampleController.RegisterExample<Examples::DynamicText3DExampleFactory>();
    m_exampleController.RegisterExample<Examples::EnvironmentFlatteningExampleFactory>();
    m_exampleController.RegisterExample<Examples::EnvironmentNotifierExampleFactory>();
    m_exampleController.RegisterExample<Examples::FileIOExampleFactory>();
    //m_exampleController.RegisterExample<Examples::KeyboardInputExampleFactory>();
    m_exampleController.RegisterExample<Examples::LoadModelExampleFactory>();
    m_exampleController.RegisterExample<Examples::ModifiedRenderingExampleFactory>();
    m_exampleController.RegisterExample<Examples::NavigationGraphExampleFactory>();
    m_exampleController.RegisterExample<Examples::Pick3DObjectExampleFactory>();
    m_exampleController.RegisterExample<Examples::PinsExampleFactory>();
    m_exampleController.RegisterExample<Examples::PinOverModelExampleFactory>();
    m_exampleController.RegisterExample<Examples::PODAnimationExampleFactory>();
    m_exampleController.RegisterExample<Examples::ResourceSpatialQueryExampleFactory>();
    m_exampleController.RegisterExample<Examples::RouteDrawingExampleFactory>();
    m_exampleController.RegisterCameraExample<Examples::RouteSimulationAnimationExampleFactory>(*m_globeCameraController);
    m_exampleController.RegisterExample<Examples::RouteThicknessPolicyExampleFactory>();
    m_exampleController.RegisterExample<Examples::ScreenPickExampleFactory>();
    m_exampleController.RegisterExample<Examples::ScreenUnprojectExampleFactory>();
    m_exampleController.RegisterExample<Examples::SearchExampleFactory>(); 
    m_exampleController.RegisterCameraExample<Examples::SingleCityExampleFactory>(*m_globeCameraController);
    m_exampleController.RegisterExample<Examples::ToggleTrafficExampleFactory>();
    m_exampleController.RegisterExample<Examples::TrafficCongestionExampleFactory>();
    m_exampleController.RegisterExample<Examples::WebRequestExampleFactory>();
}

ExampleApp::~ExampleApp()
{
    delete m_globeCameraController;
    delete m_cameraTouchController;
}

void ExampleApp::OnPause()
{

}

void ExampleApp::OnResume()
{

}

void ExampleApp::Update (float dt)
{
    Eegeo::EegeoWorld& eegeoWorld = World();
    
    eegeoWorld.EarlyUpdate(dt);
    m_exampleController.EarlyUpdate(dt, *m_globeCameraController, *m_cameraTouchController);
    
    eegeoWorld.Update(dt);
    m_exampleController.Update(dt);
}

void ExampleApp::Draw (float dt)
{
    Eegeo::Rendering::GLState& glState = World().GetRenderContext().GetGLState();
    glState.ClearColor(0.8f, 0.8f, 0.8f, 1.f);
    World().Draw(dt);
    m_exampleController.Draw();
}

void ExampleApp::Event_TouchRotate(const AppInterface::RotateData& data)
{
    if(!m_exampleController.Event_TouchRotate(data))
    {
        m_cameraTouchController->Event_TouchRotate(data);
    }
}

void ExampleApp::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
    if(!m_exampleController.Event_TouchRotate_Start(data))
    {
        m_cameraTouchController->Event_TouchRotate_Start(data);
    }
}

void ExampleApp::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
    if(!m_exampleController.Event_TouchRotate_End(data))
    {
        m_cameraTouchController->Event_TouchRotate_End(data);
    }
}

void ExampleApp::Event_TouchPinch(const AppInterface::PinchData& data)
{
    if(!m_exampleController.Event_TouchPinch(data))
    {
        m_cameraTouchController->Event_TouchPinch(data);
    }
}

void ExampleApp::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
    if(!m_exampleController.Event_TouchPinch_Start(data))
    {
        m_cameraTouchController->Event_TouchPinch_Start(data);
    }
}

void ExampleApp::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
    if(!m_exampleController.Event_TouchPinch_End(data))
    {
        m_cameraTouchController->Event_TouchPinch_End(data);
    }
}

void ExampleApp::Event_TouchPan(const AppInterface::PanData& data)
{
    if(!m_exampleController.Event_TouchPan(data))
    {
        m_cameraTouchController->Event_TouchPan(data);
    }
}

void ExampleApp::Event_TouchPan_Start(const AppInterface::PanData& data)
{
    if(!m_exampleController.Event_TouchPan_Start(data))
    {
        m_cameraTouchController->Event_TouchPan_Start(data);
    }
}

void ExampleApp::Event_TouchPan_End(const AppInterface::PanData& data)
{
    if(!m_exampleController.Event_TouchPan_End(data))
    {
        m_cameraTouchController->Event_TouchPan_End(data);
    }
}

void ExampleApp::Event_TouchTap(const AppInterface::TapData& data)
{
    if(!m_exampleController.Event_TouchTap(data))
    {
        m_cameraTouchController->Event_TouchTap(data);
    }
}

void ExampleApp::Event_TouchDoubleTap(const AppInterface::TapData& data)
{
    if(!m_exampleController.Event_TouchDoubleTap(data))
    {
        m_cameraTouchController->Event_TouchDoubleTap(data);
    }
}

void ExampleApp::Event_TouchDown(const AppInterface::TouchData& data)
{
    if(!m_exampleController.Event_TouchDown(data))
    {
        m_cameraTouchController->Event_TouchDown(data);
    }
}

void ExampleApp::Event_TouchMove(const AppInterface::TouchData& data)
{
    if(!m_exampleController.Event_TouchMove(data))
    {
        m_cameraTouchController->Event_TouchMove(data);
    }
}

void ExampleApp::Event_TouchUp(const AppInterface::TouchData& data)
{
    if(!m_exampleController.Event_TouchUp(data))
    {
        m_cameraTouchController->Event_TouchUp(data);
    }
}

