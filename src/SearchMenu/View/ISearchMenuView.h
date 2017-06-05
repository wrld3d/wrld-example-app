// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "IMenuSectionViewModel.h"
#include <vector>

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class ISearchMenuView
            {
            public:
                virtual ~ISearchMenuView() { }
                
                virtual void SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection) = 0;
                
                virtual void RemoveSeachKeyboard() = 0;
                
                virtual void SetSearchInProgress(bool inProgress) = 0;
                
                virtual void SetEditText(const std::string& searchText, bool isTag) = 0;
                virtual std::string GetEditText() = 0;

                virtual bool HasTagSearch() = 0;
                
                virtual void SetSearchResultCount(int searchResultCount) = 0;

                virtual void HideSearchResultCount() = 0;

                virtual void RemoveSearchQueryResults() = 0;
                
                virtual void CollapseAll() = 0;
                
                virtual void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
                virtual void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
                
                virtual void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void InsertSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                virtual void RemoveSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                
                virtual void HandleSearchItemSelected(int index) = 0;

                virtual void SetMenuSections(const std::vector<Menu::View::IMenuSectionViewModel*>& sections) = 0;
            };
        }
    }
}
