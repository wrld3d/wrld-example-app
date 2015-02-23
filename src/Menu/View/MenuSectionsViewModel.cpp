// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuSectionsViewModel.h"
#include <vector>
#include <algorithm>

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            size_t NumberOfCells(const std::vector<IMenuSectionViewModel*>& set)
            {
                size_t numberOfCells = 0;

                for (int i = 0; i < set.size(); ++i)
                {
                    const IMenuSectionViewModel& section = *set.at(i);
                    numberOfCells += section.GetTotalItemCount();
                }

                return numberOfCells;
            }

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
}
