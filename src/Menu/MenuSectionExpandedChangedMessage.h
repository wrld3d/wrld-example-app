// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Menu
    {
        class MenuSectionExpandedChangedMessage
        {
            std::string m_menuSectionName;
            bool m_isExpanded;
            
        public:
            MenuSectionExpandedChangedMessage(const std::string& menuSectionName, bool isExpanded);
            
            bool IsExpanded() const;
            
            const std::string& MenuSectionName() const;
        };
    }
}
