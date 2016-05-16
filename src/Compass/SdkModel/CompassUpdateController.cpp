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
            CompassUpdateController::CompassUpdateController(ICompassModel& model,
                                                             Eegeo::Location::NavigationService& navigationService,
                                                             InteriorsNavigation::SdkModel::IInteriorsNavigationService& interiorsNavigationService,
                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                             AppModes::SdkModel::IAppModeModel& appModeModel)
                : m_model(model)
                , m_navigationService(navigationService)
                , m_interiorsNavigationService(interiorsNavigationService)
                , m_messageBus(messageBus)
                , m_appModeModel(appModeModel)
            {
            }

            void CompassUpdateController::Update(float deltaSeconds)
            {
                m_messageBus.Publish(CompassHeadingUpdateMessage(m_model.GetHeadingRadians()));
                
                if(m_appModeModel.GetAppMode() == AppModes::SdkModel::WorldMode)
                {
                    m_model.TryUpdateToNavigationServiceGpsMode(m_navigationService.GetGpsMode());
                }
                else
                {
                    m_model.TryUpdateToNavigationServiceGpsMode(m_interiorsNavigationService.GetGpsMode());
                }
            }
        }
    }
}
