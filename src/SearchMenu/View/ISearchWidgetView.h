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
            class ISearchWidgetView
            {
            public:
                virtual void UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged) = 0;

                virtual void PerformSearch(const std::string& query, const QueryContext& context) = 0;

                virtual void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                virtual void RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                virtual void HandleItemSelected(int sectionIndex, int itemIndex) = 0;
                virtual void InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback) = 0;
                virtual void RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback) = 0;
            };
        }
    }
}
