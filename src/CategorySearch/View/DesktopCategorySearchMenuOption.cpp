// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DesktopCategorySearchMenuOption.h"
#include "ISearchQueryPerformer.h"
#include "IMenuViewModel.h"
#include "CategorySearchSelectedMessage.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace View
        {
            DesktopCategorySearchMenuOption::DesktopCategorySearchMenuOption(CategorySearchModel model,
                    Menu::View::IMenuViewModel& menuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    const Menu::View::IMenuReactionModel& menuReaction)
                : m_model(model)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
                , m_menuReaction(menuReaction)
            {
            }

            DesktopCategorySearchMenuOption::~DesktopCategorySearchMenuOption()
            {

            }

            void DesktopCategorySearchMenuOption::Select()
            {
                if (m_menuReaction.GetShouldCloseMenu())
                {
                    m_menuViewModel.Close();
                }

                m_messageBus.Publish(CategorySearchSelectedMessage(m_model.SearchCategory(), m_model.Interior()));
            }
        }
    }
}
