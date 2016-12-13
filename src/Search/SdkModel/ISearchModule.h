// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "TagSearch.h"
#include "InteriorMenuObserver.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class ISearchModule
            {
            public:
                virtual ~ISearchModule() { }

                virtual ISearchResultRepository& GetSearchResultRepository() const = 0;

                virtual ISearchQueryPerformer& GetSearchQueryPerformer() const = 0;

                virtual ISearchRefreshService& GetSearchRefreshService() const = 0;
                
                virtual ExampleApp::TagSearch::SdkModel::ITagSearchModule& GetTagSearchModule() const = 0;
                
                virtual MyPins::ISearchResultMyPinsService& GetSearchResultMyPinsService() const = 0;
                
                virtual MyPins::IMyPinsSearchResultRefreshService& GetMyPinsSearchResultRefreshService() const = 0;
                
                virtual InteriorMenuObserver& GetInteriorMenuObserver() const = 0;
            };
        }
    }
}
