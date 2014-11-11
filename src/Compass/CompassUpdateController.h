// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Compass.h"
#include "ICompassUpdateController.h"
#include "Location.h"
#include "CompassGpsMode.h"
#include "NavigationService.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
    namespace Compass
    {
        class CompassUpdateController : public ICompassUpdateController, private Eegeo::NonCopyable
        {
        public:
            
            CompassUpdateController(ICompassModel& model,
                                    Eegeo::Location::NavigationService& navigationService,
                                    ExampleApp::ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            void Update(float deltaSeconds);
            
        private:
            ICompassModel& m_model;
            Eegeo::Location::NavigationService& m_navigationService;
            ExampleApp::ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
        };
    }
}
