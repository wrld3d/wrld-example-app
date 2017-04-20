// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SelectMenuItemMessage.h"

namespace ExampleApp
{
    namespace Automation
    {
        SelectMenuItemMessage::SelectMenuItemMessage(int menuItem)
        : m_menuItem(menuItem)
        {
            
        }
        
        const int SelectMenuItemMessage::GetMenuItem() const
        {
            return m_menuItem;
        }
    }
}
