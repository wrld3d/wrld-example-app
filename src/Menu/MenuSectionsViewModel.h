// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMenuSectionsViewModel.h"
#include "Types.h"
#include "Menu.h"
#include <vector>

namespace ExampleApp
{
	namespace Menu
	{
		class MenuSectionsViewModel : public IMenuSectionsViewModel, private Eegeo::NonCopyable
		{
		public:
			void AddSection(IMenuSectionViewModel& section);
			void RemoveSection(IMenuSectionViewModel& section);

			size_t SectionsCount() const
			{
				return m_menuSections.size();
			}

			IMenuSectionViewModel& GetMenuSection(int index) const;

		private:

			std::vector<IMenuSectionViewModel*> m_menuSections;
		};
	}
}
