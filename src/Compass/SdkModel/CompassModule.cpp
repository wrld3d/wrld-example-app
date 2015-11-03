// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassModule.h"
#include "CompassViewModel.h"
#include "CompassModel.h"
#include "CompassUpdateController.h"


namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            CompassModule::CompassModule(Eegeo::Location::NavigationService& navigationService,
                                         InteriorsNavigation::SdkModel::IInteriorsNavigationService& interiorsNavigationService,
                                         Eegeo::Location::ILocationService& locationService,
                                         ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                                         Eegeo::Helpers::IIdentityProvider& identityProvider,
                                         ExampleAppMessaging::TMessageBus& messageBus,
                                         Metrics::IMetricsService& metricsService,
                                         InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorExplorerModel,
                                         AppModes::SdkModel::IAppModeModel& appModeModel,
                                         Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory)
            {
                m_pModel = Eegeo_NEW(CompassModel)(navigationService,
                                                   interiorsNavigationService,
                                                   locationService,
                                                   cameraController,
                                                   metricsService,
                                                   interiorExplorerModel,
                                                   appModeModel,
                                                   alertBoxFactory);
                
                m_pViewModel = Eegeo_NEW(View::CompassViewModel)(identityProvider.GetNextIdentity(), false);
                m_pCompassUpdateController = Eegeo_NEW(CompassUpdateController)(*m_pModel, navigationService, interiorsNavigationService, messageBus, appModeModel);
                m_pCompassModeObserver = Eegeo_NEW(CompassModeObserver)(*m_pModel, messageBus);
                m_pCompassViewCycledObserver = Eegeo_NEW(CompassViewCycledObserver)(*m_pModel, messageBus);
            }

            CompassModule::~CompassModule()
            {
                Eegeo_DELETE m_pCompassViewCycledObserver;
                Eegeo_DELETE m_pCompassModeObserver;
                Eegeo_DELETE m_pCompassUpdateController;
                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pModel;
            }

            ICompassModel& CompassModule::GetCompassModel() const
            {
                return *m_pModel;
            }

            View::ICompassViewModel& CompassModule::GetCompassViewModel() const
            {
                return *m_pViewModel;
            }

            ICompassUpdateController& CompassModule::GetCompassUpdateController() const
            {
                return *m_pCompassUpdateController;
            }

            ScreenControl::View::IScreenControlViewModel& CompassModule::GetScreenControlViewModel() const
            {
                return m_pViewModel->GetScreenControlViewModel();
            }
        }
    }
}
