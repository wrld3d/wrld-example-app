// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchWidgetView.h"
#include "SearchMenuView.h"
#include "WidgetSearchResultModel.h"

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
                WRLDSearchModel* m_pSearchModel;
                WRLDSearchProviderHandle* m_pSearchProviderHandle;
                WRLDSuggestionProviderHandle* m_pSuggestionProviderHandle;
                
                Eegeo::Helpers::CallbackCollection0 m_searchClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<int> m_resultSelectedCallbacks;
                Eegeo::Helpers::CallbackCollection3<const std::string&, int, int> m_onItemSelectedCallbacks;
                
            public:
                SearchWidgetView(SearchMenuView* view,
                                 id<WRLDSearchProvider> searchProvider,
                                 id<WRLDSuggestionProvider> suggestionProvider);
                ~SearchWidgetView();
                
                UIViewController* GetWidgetController() const;
                UIView* GetWidgetView() const;
                
                void OnSearchResultSelected(int index);
                
                void UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged);
                
                void SetFullyOnScreenOpen();
                void SetFullyOnScreenClosed();
                
                void PerformSearch(const std::string& query, const QueryContext& context);
                
                void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                
                void HandleItemSelected(const std::string& menuText, int sectionIndex, int itemIndex);
                
                void InsertOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback);
                void RemoveOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback);
                
                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();
            };
        }
    }
}
