// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuView.h"
#include "Search.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class ISearchResultMenuView
            {
            public:
                virtual ~ISearchResultMenuView() { };

                virtual void SetHeader(const std::string& header, bool queryPending, size_t numResult) = 0;
                
                virtual void SetAttractMode(bool attractModeEnabled) = 0;

                virtual void InsertSearchClosed(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void RemoveSearchClosed(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
