// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "Interiors.h"
#include "Types.h"
#include "IInteriorsExplorerModule.h"
#include "ScreenControlViewModelIncludes.h"
#include "IIdentity.h"
#include "BidirectionalBus.h"
#include "MapMode.h"
#include "GlobeCamera.h"
#include "Metrics.h"
#include "NativeUIFactories.h"
#include "Streaming.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerModule : public IInteriorsExplorerModule, private Eegeo::NonCopyable
            {
            public:
                InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                        Eegeo::Resources::Interiors::Camera::InteriorsCameraController& interiorsCameraController,
                                        Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                        Eegeo::Resources::Interiors::InteriorSelectionController& interiorSelectionController,
                                        Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                        Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                        Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                        Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                        Eegeo::Helpers::IIdentityProvider& identityProvider,
                                        MapMode::SdkModel::IMapModeModel& mapModeModel,
                                        AppModes::SdkModel::IAppModeModel& appModeModel,
                                        ExampleAppMessaging::TMessageBus& messageBus,
                                        ExampleApp::Metrics::IMetricsService& metricsService);

                ~InteriorsExplorerModule();
                
                View::InteriorsExplorerViewModel& GetInteriorsExplorerViewModel() const;
                
                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;

                IInteriorsExplorerInputDelegate& GetInputDelegate() const;
                
            private:
                
                InteriorsExplorerModel* m_pModel;
                View::InteriorsExplorerViewModel* m_pViewModel;
                InteriorsExitObserver* m_pInteriorExitObserver;
                IInteriorsExplorerInputDelegate* m_pInteriorsExplorerInputDelegate;
                InteriorsStreamingController* m_pInteriorsStreamingController;
                InteriorPinScaleController* m_pInteriorPinScaleController;
            };
        }
    }
}