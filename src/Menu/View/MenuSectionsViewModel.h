// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuSectionsViewModel.h"
#include "IMenuSectionViewModel.h"
#include "Types.h"
#include "Menu.h"
#include <vector>

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            size_t NumberOfCells(const std::vector<IMenuSectionViewModel*>& set);

            class MenuSectionsViewModel : public IMenuSectionsViewModel, private Eegeo::NonCopyable
            {
            public:
                void AddSection(IMenuSectionViewModel& section);
                void RemoveSection(IMenuSectionViewModel& section);

                size_t SectionsCount() const
                {
                    return m_menuSections.size();
                }


                size_t NumberOfCells() const
                {
                    return View::NumberOfCells(m_menuSections);
                }

                IMenuSectionViewModel& GetMenuSection(int index) const;

            private:

                std::vector<IMenuSectionViewModel*> m_menuSections;
            };
        }
    }
}
