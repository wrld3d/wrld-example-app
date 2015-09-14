// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerViewModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorsExitObserver.h"
#include "InteriorsExplorerInputDelegate.h"
#include "InteriorsStreamingController.h"
#include "InteriorPinScaleController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
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
                                                             ExampleApp::Metrics::IMetricsService& metricsService)
            {
                m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorsController, interiorSelectionModel, mapModeModel, messageBus, metricsService);
                m_pViewModel = Eegeo_NEW(View::InteriorsExplorerViewModel)(false, identityProvider.GetNextIdentity());
                m_pInteriorExitObserver = Eegeo_NEW(InteriorsExitObserver)(interiorsController, interiorSelectionController, globeCameraController, nativeUIFactories);
                m_pInteriorsExplorerInputDelegate = Eegeo_NEW(InteriorsExplorerInputDelegate)(interiorsController, interiorsPinsController, globeCameraController, messageBus);
                m_pInteriorsStreamingController = Eegeo_NEW(InteriorsStreamingController)(interiorSelectionController, cameraFrustumStreamingVolume);
                m_pInteriorPinScaleController = Eegeo_NEW(InteriorPinScaleController)(interiorsPinsController, appModeModel, messageBus);
            }
            
            InteriorsExplorerModule::~InteriorsExplorerModule()
            {
                Eegeo_DELETE m_pInteriorPinScaleController;
                Eegeo_DELETE m_pInteriorsExplorerInputDelegate;
                Eegeo_DELETE m_pInteriorExitObserver;
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pInteriorsStreamingController;
            }
            
            View::InteriorsExplorerViewModel& InteriorsExplorerModule::GetInteriorsExplorerViewModel() const
            {
                return *m_pViewModel;
            }
            
            ScreenControl::View::IScreenControlViewModel& InteriorsExplorerModule::GetScreenControlViewModel() const
            {
                return *m_pViewModel;
            }

            IInteriorsExplorerInputDelegate& InteriorsExplorerModule::GetInputDelegate() const
            {
                return *m_pInteriorsExplorerInputDelegate;
            }
        }
    }
}