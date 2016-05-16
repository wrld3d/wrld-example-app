// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Compass.h"
#include "ICompassUpdateController.h"
#include "Location.h"
#include "CompassGpsMode.h"
#include "NavigationService.h"
#include "BidirectionalBus.h"
#include "InteriorsNavigation.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class CompassUpdateController : public ICompassUpdateController, private Eegeo::NonCopyable
            {
            public:

                CompassUpdateController(ICompassModel& model,
                                        Eegeo::Location::NavigationService& navigationService,
                                        InteriorsNavigation::SdkModel::IInteriorsNavigationService& interiorsNavigationService,
                                        ExampleAppMessaging::TMessageBus& messageBus,
                                        AppModes::SdkModel::IAppModeModel& appModeModel);

                void Update(float deltaSeconds);

            private:
                ICompassModel& m_model;
                Eegeo::Location::NavigationService& m_navigationService;
                InteriorsNavigation::SdkModel::IInteriorsNavigationService& m_interiorsNavigationService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                AppModes::SdkModel::IAppModeModel& m_appModeModel;
            };
        }
    }
}
