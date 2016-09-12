// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "MenuModel.h"
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
            class PlaceJumpMenuModel : public Menu::View::MenuModel
            {
            };
            
            class PlaceJumpMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                PlaceJumpMenuOptionsModel(const std::shared_ptr<PlaceJumpMenuModel>& placeJumpModel) : Menu::View::MenuOptionsModel(*placeJumpModel)
                {
                }
            };
            
            class PlaceJumpMenuOption : public Menu::View::IMenuOption
            {
            public:
                PlaceJumpMenuOption(PlaceJumpModel jumpModel,
                                    const std::shared_ptr<Menu::View::IMenuViewModel>& menuViewModel,
                                    const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                    const std::shared_ptr<Metrics::IMetricsService>& metricsService,
                                    const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReaction);

                void Select();

            private:

                PlaceJumpModel m_jumpModel;
                const std::shared_ptr<Menu::View::IMenuViewModel> m_menuViewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;

                const std::shared_ptr<const Menu::View::IMenuReactionModel> m_menuReaction;
            };
        }
    }
}
