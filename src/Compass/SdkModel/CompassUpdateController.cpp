// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassUpdateController.h"
#include "CompassModel.h"
#include "NavigationService.h"
#include "CompassHeadingUpdateMessage.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            CompassUpdateController::CompassUpdateController(ICompassModel& model,
                                                             Eegeo::Location::NavigationService& navigationService,
                                                             ExampleAppMessaging::TMessageBus& messageBus)
                : m_model(model)
                , m_navigationService(navigationService)
                , m_messageBus(messageBus)
            {
            }

            void CompassUpdateController::Update(float deltaSeconds)
            {
                m_messageBus.Publish(CompassHeadingUpdateMessage(m_model.GetHeadingRadians()));
                
                m_model.TryUpdateToNavigationServiceGpsMode(m_navigationService.GetGpsMode());
            }
        }
    }
}
