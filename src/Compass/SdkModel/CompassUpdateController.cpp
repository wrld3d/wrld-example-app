// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassUpdateController.h"
#include "CompassModel.h"
#include "NavigationService.h"
#include "CompassHeadingUpdateMessage.h"
#include "IInteriorsNavigationService.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            CompassUpdateController::CompassUpdateController(const std::shared_ptr<ICompassModel>& model,
                                                             const std::shared_ptr<Eegeo::Location::NavigationService>& navigationService,
                                                             const std::shared_ptr<InteriorsNavigation::SdkModel::IInteriorsNavigationService>& interiorsNavigationService,
                                                             const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                             const std::shared_ptr<AppModes::SdkModel::IAppModeModel>& appModeModel)
                : m_model(model)
                , m_navigationService(navigationService)
                , m_interiorsNavigationService(interiorsNavigationService)
                , m_messageBus(messageBus)
                , m_appModeModel(appModeModel)
            {
            }

            void CompassUpdateController::Update(float deltaSeconds)
            {
                m_messageBus->Publish(CompassHeadingUpdateMessage(m_model->GetHeadingRadians()));
                
                if(m_appModeModel->GetAppMode() == AppModes::SdkModel::WorldMode)
                {
                    m_model->TryUpdateToNavigationServiceGpsMode(m_navigationService->GetGpsMode());
                }
                else
                {
                    m_model->TryUpdateToNavigationServiceGpsMode(m_interiorsNavigationService->GetGpsMode());
                }
            }
        }
    }
}
