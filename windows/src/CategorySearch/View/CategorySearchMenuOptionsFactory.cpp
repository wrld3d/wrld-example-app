// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IMenuOption.h"
#include "CategorySearchModel.h"
#include "Search.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "IMenuReactionModel.h"
#include "IMenuIgnoredReactionModel.h"
#include "CategorySearchMenuOptionFactory.h"
#include "DesktopCategorySearchMenuOption.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace View
        {
                Menu::View::IMenuOption* CategorySearchMenuOptionFactory::CreateCategorySearchMenuOption(CategorySearchModel model,
                                                                                           Menu::View::IMenuViewModel& menuViewModel,
                                                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                                                           const Menu::View::IMenuReactionModel& menuReaction)
                {
                    return Eegeo_NEW(DesktopCategorySearchMenuOption)(model,
                                                                      menuViewModel,
                                                                      messageBus,
                                                                      menuReaction);
                }
        }
    }
}
