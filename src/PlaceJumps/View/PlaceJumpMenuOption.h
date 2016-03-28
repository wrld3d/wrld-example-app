// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "LatLongAltitude.h"
#include "CameraHelpers.h"
#include "IPlaceJumpController.h"
#include "IPlaceJumpsModel.h"
#include "Logger.h"
#include "IMenuViewModel.h"
#include "BidirectionalBus.h"
#include "PlaceJumpSelectedMessage.h"
#include "IMetricsService.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace View
        {
            class PlaceJumpMenuOption : public Menu::View::IMenuOption
            {
            public:
                PlaceJumpMenuOption(PlaceJumpModel jumpModel,
                                    Menu::View::IMenuViewModel& menuViewModel,
                                    ExampleAppMessaging::TMessageBus& messageBus,
                                    Metrics::IMetricsService& metricsService,
                                    const Menu::View::IMenuReactionModel& menuReaction);

                void Select();

            private:

                PlaceJumpModel m_jumpModel;
                Menu::View::IMenuViewModel& m_menuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Metrics::IMetricsService& m_metricsService;

                const Menu::View::IMenuReactionModel& m_menuReaction;
            };
        }
    }
}
