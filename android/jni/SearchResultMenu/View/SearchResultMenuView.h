// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuView.h"
//#include "ISearchResultMenuView.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchMenuView : public Menu::View::MenuView//, public SearchResultMenu::View::ISearchResultMenuView
            {
            private:
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;

            public:
                SearchMenuView(AndroidNativeState& nativeState,
                               const std::string& viewClassName);

                void SetHeader(const std::string& header, bool queryPending, size_t numResult);

                void SetAttractMode(bool attractModeEnabled);

                void HandleSearchClosed();

                void InsertSearchClosed(Eegeo::Helpers::ICallback0& callback);

                void RemoveSearchClosed(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
