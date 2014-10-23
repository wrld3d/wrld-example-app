// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MenuSectionsViewModel.h"
#include <vector>
#include <algorithm>

namespace ExampleApp
{
    namespace Menu
    {
        void MenuSectionsViewModel::AddSection(IMenuSectionViewModel& section)
        {
            m_menuSections.push_back(&section);
        }
        
        void MenuSectionsViewModel::RemoveSection(IMenuSectionViewModel& section)
        {
            m_menuSections.erase(std::remove(m_menuSections.begin(), m_menuSections.end(), &section), m_menuSections.end());
        }
        
        IMenuSectionViewModel& MenuSectionsViewModel::GetMenuSection(int index) const
        {
            return *m_menuSections.at(index);
        }
    }
}
