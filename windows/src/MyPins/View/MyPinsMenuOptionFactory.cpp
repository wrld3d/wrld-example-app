// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

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
#include "DesktopMyPinMenuOption.h"
#include "IMenuIgnoredReactionModel.h"
#include "MyPinMenuOptionFactory.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
                Menu::View::IMenuOption* MyPinMenuOptionFactory::CreateMyPinMenuOption(SdkModel::MyPinModel::TPinIdType pinId,
                                                               const Eegeo::Space::LatLong& pinLocation,
                                                               const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                               int targetFloor,
                                                               Menu::View::IMenuViewModel& menuViewModel,
                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                               const Menu::View::IMenuReactionModel& menuReaction,
                                                               Menu::View::IMenuIgnoredReactionModel& ignoredReactionModel)
                {
                    return Eegeo_NEW(DesktopMyPinMenuOption)(pinId,
                                                             pinLocation,
                                                             interiorId,
                                                             targetFloor,
                                                             menuViewModel,
                                                             messageBus,
                                                             menuReaction,
                                                             ignoredReactionModel);
                }
        }
    }
}
