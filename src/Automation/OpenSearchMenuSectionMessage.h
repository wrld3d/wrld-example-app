// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <functional>
#include "IMenuSectionViewModel.h"

namespace ExampleApp
{
    namespace Automation
    {
        class OpenSearchMenuSectionMessage
        {
                const std::function<bool(const Menu::View::IMenuSectionViewModel&)> m_shouldOpenMenuSection;
        public:
            OpenSearchMenuSectionMessage(const std::function<bool(const Menu::View::IMenuSectionViewModel&)> shouldOpenMenuSection)
                : m_shouldOpenMenuSection(shouldOpenMenuSection)
            {}

            const bool ShouldOpenMenuSectionMessage(const Menu::View::IMenuSectionViewModel& menuSection) const
            {
                return m_shouldOpenMenuSection(menuSection);
            }
        };
    }
}
