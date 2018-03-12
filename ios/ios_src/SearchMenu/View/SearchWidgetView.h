// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchWidgetView.h"
#include "SearchMenuView.h"

#import <WrldSearchWidget/WrldSearchWidget.h>

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchWidgetView : public SearchMenu::View::ISearchWidgetView
            {
            private:
                SearchMenuView* m_pView;
                WRLDSearchWidgetViewController* m_pSearchWidgetViewController;

            public:
                SearchWidgetView(SearchMenuView* view);
                ~SearchWidgetView();

                UIViewController* GetWidgetController() const;
                UIView* GetWidgetView() const;

                void UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged);

                void RefreshSearch(const std::string& query, const QueryContext& context);

                void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void HandleItemSelected(int sectionIndex, int itemIndex);
                void InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback);
                void RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback);
            };
        }
    }
}
