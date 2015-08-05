// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerViewModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorsControllerExitObserver.h"
#include "InteriorsExplorerInputDelegate.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                                             Eegeo::Resources::Interiors::Camera::InteriorsCameraController& interiorsCameraController,
                                                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                             Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                                             Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                             MapMode::SdkModel::IMapModeModel& mapModeModel,
                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                             ExampleApp::Metrics::IMetricsService& metricsService)
            {
                m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorsController, interiorSelectionModel, mapModeModel, messageBus, metricsService);
                m_pViewModel = Eegeo_NEW(View::InteriorsExplorerViewModel)(false, identityProvider.GetNextIdentity());
                m_pInteriorsControllerExitObserver = Eegeo_NEW(InteriorsControllerExitObserver)(interiorsController, globeCameraController);
                m_pInteriorsExplorerInputDelegate = Eegeo_NEW(InteriorsExplorerInputDelegate)(interiorsController, interiorsPinsController, globeCameraController);
            }
            
            InteriorsExplorerModule::~InteriorsExplorerModule()
            {
                Eegeo_DELETE m_pInteriorsExplorerInputDelegate;
                Eegeo_DELETE m_pInteriorsControllerExitObserver;
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pViewModel;
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