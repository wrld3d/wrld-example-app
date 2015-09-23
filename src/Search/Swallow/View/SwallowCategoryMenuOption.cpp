// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowCategoryMenuOption.h"
#include "IMenuViewModel.h"
#include "CategorySearchSelectedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace View
            {
                SwallowCategoryMenuOption::SwallowCategoryMenuOption(std::string category,
                                                                     Menu::View::IMenuViewModel& menuViewModel,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
                : m_category(category)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
                {
                    
                }
                
                SwallowCategoryMenuOption::~SwallowCategoryMenuOption()
                {
                    
                }
                
                void SwallowCategoryMenuOption::Select()
                {
                    m_menuViewModel.Close();
                    m_messageBus.Publish(CategorySearch::CategorySearchSelectedMessage(m_category));
                }
            }
        }
    }
}
