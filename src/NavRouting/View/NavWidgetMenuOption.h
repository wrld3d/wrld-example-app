// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include "NavRouting.h"
#include "Menu.h"
#include "Types.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetMenuOption : public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
            private:
                SdkModel::NavRoutingController& m_routingController;
                SdkModel::INavRoutingModel& m_routingModel;
            public:
                NavWidgetMenuOption(SdkModel::INavRoutingModel& m_routingModel,
                                    SdkModel::NavRoutingController& routingController);

                ~NavWidgetMenuOption();

                void Select();
            };
        }
    }
}
