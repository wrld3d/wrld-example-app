// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PlaceJumpMenuOption.h"
#include "FlurryWrapper.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace View
        {
            PlaceJumpMenuOption::PlaceJumpMenuOption(PlaceJumpModel jumpModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_jumpModel(jumpModel)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
            {
            }

            void PlaceJumpMenuOption::Select()
            {
                FLURRY_SET_EVENT("UIItem: Placejump", "Name", m_jumpModel.GetName().c_str());
                m_menuViewModel.Close();
                m_messageBus.Publish(PlaceJumpSelectedMessage(m_jumpModel));
            }
        }
    }
}
