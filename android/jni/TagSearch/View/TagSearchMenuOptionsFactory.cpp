// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IMenuOption.h"
#include "TagSearchModel.h"
#include "Search.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "IMenuReactionModel.h"
#include "TagSearchMenuOptionFactory.h"
#include "TagSearchMenuOption.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
                Menu::View::IMenuOption* TagSearchMenuOptionFactory::CreateTagSearchMenuOption(TagSearchModel model,
                                                                                               Menu::View::IMenuViewModel& menuViewModel,
                                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                                               const Menu::View::IMenuReactionModel& menuReaction)
                {
                    return Eegeo_NEW(TagSearchMenuOption)(model,
                                                          menuViewModel,
                                                          messageBus,
                                                          menuReaction);
                }
        }
    }
}
