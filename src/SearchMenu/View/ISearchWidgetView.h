// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CallbackCollection.h"
#include "IMenuView.h"

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

                virtual void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
