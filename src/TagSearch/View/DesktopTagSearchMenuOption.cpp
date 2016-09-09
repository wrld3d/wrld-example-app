// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DesktopTagSearchMenuOption.h"
#include "ISearchQueryPerformer.h"
#include "IMenuViewModel.h"
#include "TagSearchSelectedMessage.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            DesktopTagSearchMenuOption::DesktopTagSearchMenuOption(TagSearchModel model,
                    Menu::View::IMenuViewModel& menuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    const Menu::View::IMenuReactionModel& menuReaction)
                : m_model(model)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
                , m_menuReaction(menuReaction)
            {
            }

            DesktopTagSearchMenuOption::~DesktopTagSearchMenuOption()
            {

            }

            void DesktopTagSearchMenuOption::Select()
            {
                if (m_menuReaction.GetShouldCloseMenu())
                {
                    m_menuViewModel.Close();
                }

                m_messageBus.Publish(TagSearchSelectedMessage(m_model.SearchTag(), m_model.Interior()));
            }
        }
    }
}
