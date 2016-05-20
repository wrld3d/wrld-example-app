// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuSectionExpandedChangedMessage.h"

namespace ExampleApp
{
    namespace Menu
    {
        MenuSectionExpandedChangedMessage::MenuSectionExpandedChangedMessage(const std::string& menuSectionName, bool isExpanded)
        : m_menuSectionName(menuSectionName)
        , m_isExpanded(isExpanded)
        {
        }
        
        bool MenuSectionExpandedChangedMessage::IsExpanded() const
        {
            return m_isExpanded;
        }
        
        const std::string& MenuSectionExpandedChangedMessage::MenuSectionName() const
        {
            return m_menuSectionName;
        }
    }
}