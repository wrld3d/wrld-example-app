#ifndef __ExampleApp__AppOnMap__
#define __ExampleApp__AppOnMap__

#include "IAppOnMap.h"
#include "IExample.h"
#include "Rendering.h"
#include "Space.h"
#include "Terrain.h"
#include "Roads.h"
#include "Navigation.h"
#include "Streaming.h"
#include "Traffic.h"
#include "Lighting.h"
#include "Helpers.h"
#include "Web.h"
#include "Location.h"
#include "GlobeCamera.h"
#import <UIKit/UIKit.h>

namespace ExampleTypes
{
    enum Examples
    {
        DebugSphere=0,
        ScreenUnproject,
        ScreenPick,
        TerrainHeightQuery,
        LoadModel,
        EnvironmentNotifier,
        WebRequest,
        FileIO,
        NavigationGraph,
        ModifiedRendering,
        ToggleTraffic,
        ResourceSpatialQuery,
        EnvironmentFlattening,
        Search,
        KeyboardInput,
        PODAnimation,
        Pick3DObject,
        DebugPrimitiveRendering,
        ControlCityThemes,
        RouteDrawing,
        Pins,
        RouteSimulation
    };
}

static const ExampleTypes::Examples g_defaultSelectedExample = ExampleTypes::RouteSimulation;

namespace Eegeo
{
    class ITouchController;
    class Blitter;
    
    namespace Search
    {
        namespace Service
        {
            class SearchService;
        }
    }
    
    namespace UI
    {
        class NativeUIFactories;
    }
    
    namespace Routes
    {
        class RouteService;
    }
}

class MyApp : public Eegeo::IAppOnMap
{
private:
    ExampleTypes::Examples m_selectedExampleType;
    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_globeCameraController;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* m_cameraTouchController;
    Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider& m_globeCameraInterestPointProvider;
    UIView* m_pView;
    Examples::IExample* pExample;
public:
    
    
    MyApp(Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider& globeCameraInterestPointProvider,
          UIView* pView,
          ExampleTypes::Examples selectedExample = g_defaultSelectedExample);
    
    ~MyApp();

    
    void OnStart ();
    
    void Update (float dt);
    
    void Draw (float dt);
    
    void JumpTo(double latitudeDegrees, double longitudeDegrees, double altitudeMetres, double headingDegrees, double distanceToInterestMetres);
    
    Eegeo::Camera::GlobeCamera::GlobeCameraController& GetCameraController() { return *m_globeCameraController; }
    
    Examples::IExample* CreateExample(ExampleTypes::Examples example,
                                      Eegeo::Rendering::RenderContext& renderContext,
                                      Eegeo::Space::LatLongAltitude interestLocation,
                                      Eegeo::Camera::ICameraProvider& cameraProvider,
                                      Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                      Eegeo::ITouchController& cameraTouchController,
                                      Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                      Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                      Eegeo::Helpers::IFileIO& fileIO,
                                      Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming,
                                      Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                      Eegeo::Resources::Roads::Navigation::NavigationGraphRepository& navigationGraphs,
                                      Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& buildingPool,
                                      Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& shadowPool,
                                      Eegeo::Streaming::IStreamingVolume& visibleVolume,
                                      Eegeo::Lighting::GlobalLighting& lighting,
                                      Eegeo::Lighting::GlobalFogging& fogging,
                                      Eegeo::Traffic::TrafficSimulation& trafficSimulation,
                                      Eegeo::Resources::ResourceSpatialQueryService& resourceSpatialQueryService,
                                      Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                      Eegeo::Search::Service::SearchService* searchService,
                                      Eegeo::UI::NativeUIFactories& nativeInputFactories,
                                      Eegeo::Location::IInterestPointProvider& interestPointProvider,
                                      Eegeo::Routes::RouteService& routeService);
    
    
    void Event_TouchRotate 			(const AppInterface::RotateData& data);
    void Event_TouchRotate_Start	(const AppInterface::RotateData& data);
    void Event_TouchRotate_End 		(const AppInterface::RotateData& data);
    
    void Event_TouchPinch 			(const AppInterface::PinchData& data);
    void Event_TouchPinch_Start 	(const AppInterface::PinchData& data);
    void Event_TouchPinch_End 		(const AppInterface::PinchData& data);
    
    void Event_TouchPan				(const AppInterface::PanData& data);
    void Event_TouchPan_Start		(const AppInterface::PanData& data);
    void Event_TouchPan_End 		(const AppInterface::PanData& data);
    
    void Event_TouchTap 			(const AppInterface::TapData& data);
    void Event_TouchDoubleTap		(const AppInterface::TapData& data);
    
    void Event_TouchDown 			(const AppInterface::TouchData& data);
    void Event_TouchMove 			(const AppInterface::TouchData& data);
    void Event_TouchUp 				(const AppInterface::TouchData& data);
};

#endif /* defined(__ExampleApp__AppOnMap__) */
