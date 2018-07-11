// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CallbackCollection.h"
#include "IMenuView.h"
#include "QueryContext.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class ISearchWidgetView: public ScreenControl::View::IScreenControlView
            {
            public:
                virtual ~ISearchWidgetView() { }

                virtual void UpdateMenuSectionViews(Menu::View::TSections& sections) = 0;

                virtual void CloseMenu() = 0;

                virtual void PerformSearch(const std::string& query, const QueryContext& context) = 0;

                virtual void ClearSearchResults() = 0;

                virtual void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                virtual void RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                
                virtual void InsertSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
                virtual void RemoveSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;

                virtual void InsertOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback) = 0;
                virtual void RemoveOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback) = 0;

                virtual void HandleItemSelected(const std::string&, int sectionIndex, int itemIndex) = 0;

                virtual void InsertOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback) = 0;
                virtual void RemoveOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback) = 0;

                virtual void InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
