// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "IMenuOption.h"
#include "MyPinModel.h"
#include "BidirectionalBus.h"
#include "MyPinSelectedMessage.h"
#include "IMenuViewModel.h"
#include "MyPinModel.h"
#include "LatLongAltitude.h"
#include "InteriorId.h"
#include <string>
#include "IMenuReactionModel.h"
#include "IModalityController.h"
#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            class MyPinMenuOptionFactory
            {
                MyPinMenuOptionFactory();
                ~MyPinMenuOptionFactory();
            public:
                static Menu::View::IMenuOption* CreateMyPinMenuOption(SdkModel::MyPinModel::TPinIdType pinId,
                                                               const Eegeo::Space::LatLong& pinLocation,
                                                               const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                               int targetFloor,
                                                               Menu::View::IMenuViewModel& menuViewModel,
                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                               const Menu::View::IMenuReactionModel& menuReaction,
                                                               Menu::View::IMenuIgnoredReactionModel& menuIgnoredModel);
            };
        }
    }
}
