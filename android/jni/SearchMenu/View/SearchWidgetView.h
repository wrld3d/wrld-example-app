// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
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
                jmethodID m_onSearchPerformed;
                jmethodID m_clearSearchResults;

                Eegeo::Helpers::CallbackCollection0 m_searchClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<int> m_resultSelectedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const int> m_navigationRequestedCallbacks;
                Eegeo::Helpers::CallbackCollection3<const std::string&, int, int> m_onItemSelectedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewOpenedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewClosedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_onSearchbarTextChangedCallbacks;

                void CallVoidVoidFunction(const char* func);

            public:
                SearchWidgetView(AndroidNativeState& nativeState,
                                 SearchProviders::MyTestSearchProvider& searchProvider);

                void UpdateMenuSectionViews(Menu::View::TSections& sections);

                void SetOnScreenStateToIntermediateValue(float value);

                void SetOnScreen();

                void SetOffScreen();

                void CloseMenu();

                void PerformSearch(const std::string& query, const QueryContext& context);

                void ClearSearchResults();

                void OnSearchResultsCleared();
                void OnSearchResultSelected(int index);

                void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);

                void OnSearchbarTextChanged(const std::string& newText);
                void InsertSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
                void RemoveSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);

                void OnNavigationRequest(int index);
                void InsertOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback);
                void RemoveOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback);

                void HandleItemSelected(const std::string& menuText, int sectionIndex, int itemIndex);
                void HandleViewOpenCompleted();
                void HandleViewCloseCompleted();

                void InsertOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback);
                void RemoveOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback);

                void InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback);

                void InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
