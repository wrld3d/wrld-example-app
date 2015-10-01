// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <map>

#include "Types.h"

#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        class SwallowPoiDbService;
        
        class SwallowPoiDbCombinedService : private Eegeo::NonCopyable
        {
        public:
            SwallowPoiDbCombinedService(const std::map<std::string, SwallowPoiDbService*>& serviceMap);
            
            ~SwallowPoiDbCombinedService();
            
            void FullTextSearch(const std::string& query, std::vector<Search::SdkModel::SearchResultModel>& out_results);
            
            void CategorySearch(const std::string& categoryName, std::vector<Search::SdkModel::SearchResultModel>& out_results);
        protected:
            std::map<std::string, SwallowPoiDbService*> m_serviceMap;
        };
    }
}