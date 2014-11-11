// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassUpdateController.h"
#include "CompassModel.h"
#include "NavigationService.h"
#include "CompassHeadingUpdateMessage.h"

namespace ExampleApp
{
    namespace Compass
    {
        CompassUpdateController::CompassUpdateController(ICompassModel& model,
                                                         Eegeo::Location::NavigationService& navigationService,
                                                         ExampleApp::ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        : m_model(model)
        , m_navigationService(navigationService)
        , m_nativeToUiMessageBus(nativeToUiMessageBus)
        {
        }
        
        void CompassUpdateController::Update(float deltaSeconds)
        {
            m_nativeToUiMessageBus.Publish(CompassHeadingUpdateMessage(m_model.GetHeadingRadians()));
            m_model.TryUpdateToNavigationServiceGpsMode(m_navigationService.GetGpsMode());
        }
    }
}
