// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Automation
    {
        class SelectMenuItemMessage
        {
            int m_menuItem;
        public:
            SelectMenuItemMessage(int menuItem);
            const int GetMenuItem() const;
        };
    }
}
