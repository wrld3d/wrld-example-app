// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Search.h"
#include "ICallback.h"
#include "SearchMenu.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SelectFirstResult
        {
            namespace SdkModel
            {
                class SelectFirstResultSearchService
                {
                public:
                    
                    SelectFirstResultSearchService(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer);
                    
                    void PerformSearch(const std::string& queryString, const std::string& indoorMapId);
                    
                private:
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                };
            }
        }
    }
}


