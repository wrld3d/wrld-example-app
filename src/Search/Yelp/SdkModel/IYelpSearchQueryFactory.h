// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "IdentitySearchCallbackData.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class IYelpSearchQueryFactory
                {
                public:
                    virtual ~IYelpSearchQueryFactory() { }
                    
                    virtual IYelpSearchQuery* CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                       Eegeo::Helpers::ICallback0& completionCallback) = 0;
                    
                    virtual IYelpSearchQuery* CreateYelpSearchForSpecificLocation(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                                  Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback) = 0;
                };
            }
        }
    }
}
