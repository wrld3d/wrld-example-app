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

                CompassUpdateController(const std::shared_ptr<ICompassModel>& model,
                                        const std::shared_ptr<Eegeo::Location::NavigationService>& navigationService,
                                        const std::shared_ptr<InteriorsNavigation::SdkModel::IInteriorsNavigationService>& interiorsNavigationService,
                                        const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                        const std::shared_ptr<AppModes::SdkModel::IAppModeModel>& appModeModel);

                void Update(float deltaSeconds);

            private:
                const std::shared_ptr<ICompassModel> m_model;
                const std::shared_ptr<Eegeo::Location::NavigationService> m_navigationService;
                const std::shared_ptr<InteriorsNavigation::SdkModel::IInteriorsNavigationService> m_interiorsNavigationService;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<AppModes::SdkModel::IAppModeModel> m_appModeModel;
            };
        }
    }
}
