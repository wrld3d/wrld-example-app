// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerViewModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorsControllerExitObserver.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                                             Eegeo::Resources::Interiors::Camera::InteriorsCameraController& interiorsCameraController,
                                                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                             Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                             MapMode::SdkModel::IMapModeModel& mapModeModel,
                                                             ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorsController, interiorSelectionModel, mapModeModel, messageBus);
                m_pViewModel = Eegeo_NEW(View::InteriorsExplorerViewModel)(false, identityProvider.GetNextIdentity());
                m_pInteriorsControllerExitObserver = Eegeo_NEW(InteriorsControllerExitObserver)(interiorsController, globeCameraController);
            }
            
            InteriorsExplorerModule::~InteriorsExplorerModule()
            {
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
        }
    }
}