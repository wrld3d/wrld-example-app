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
                                                                     bool forceInteriorQuery,
                                                                     Menu::View::IMenuViewModel& menuViewModel,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
                : m_category(category)
                , m_interior(forceInteriorQuery)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
                , m_hasRadiusOverride(false)
                , m_radiusOverride(0.f)
                {
                    
                }
                
                SwallowCategoryMenuOption::SwallowCategoryMenuOption(std::string category,
                                                                     bool forceInteriorQuery,
                                                                     Menu::View::IMenuViewModel& menuViewModel,
                                                                     float radius,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
                : m_category(category)
                , m_interior(forceInteriorQuery)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
                , m_hasRadiusOverride(true)
                , m_radiusOverride(radius)
                {
                    
                }
                
                SwallowCategoryMenuOption::~SwallowCategoryMenuOption()
                {
                    
                }
                
                void SwallowCategoryMenuOption::Select()
                {
                    m_menuViewModel.Close();
                    if (m_hasRadiusOverride)
                    {
                        m_messageBus.Publish(CategorySearch::CategorySearchSelectedMessage(m_category, m_interior, m_radiusOverride));
                    }
                    else
                    {
                        m_messageBus.Publish(CategorySearch::CategorySearchSelectedMessage(m_category, m_interior));
                    }
                }
            }
        }
    }
}
