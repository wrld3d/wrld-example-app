// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "IMenuView.h"
#include "MenuView.h"
#include "ISearchWidgetView.h"
#include "MyTestSearchProvider.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchWidgetView : public SearchMenu::View::ISearchWidgetView
            {
            private:
                AndroidNativeState& m_nativeState;
                jclass m_uiViewClass;
                jobject m_uiView;
                jmethodID m_onSearchRefreshed;

                Eegeo::Helpers::CallbackCollection0 m_searchClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<int> m_resultSelectedCallbacks;

            public:
                SearchWidgetView(AndroidNativeState& nativeState,
                                 SearchProviders::MyTestSearchProvider& searchProvider);

                void UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged);

                void RefreshSearch(const std::string& query, const QueryContext& context);

                void OnSearchResultsCleared();
                void OnSearchResultSelected(int index);

                void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
            };
        }
    }
}
