// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "IdentitySearchCallbackData.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class IYelpSearchQueryFactory
            {
            public:
                virtual ~IYelpSearchQueryFactory() { }
                
                virtual IYelpSearchQuery* CreateYelpSearchForQuery(const SdkModel::SearchQuery& query,
                                                                   Eegeo::Helpers::ICallback0& completionCallback,
                                                                   SdkModel::ISearchResultParser& searchResultParser) = 0;
                
                virtual IYelpSearchQuery* CreateYelpSearchForSpecificLocation(const std::string& locationIdentifier,
                                                                              Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback,
                                                                              SdkModel::ISearchResultParser& searchResultParser) = 0;
            };
        }
    }
}
