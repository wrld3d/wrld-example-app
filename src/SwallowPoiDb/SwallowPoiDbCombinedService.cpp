// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbCombinedService.h"

#include "SQLiteSpellingSuggestionResults.h"

#include "SwallowPoiDbService.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        const std::string categoryColumnName = "category";
        
        SwallowPoiDbCombinedService::SwallowPoiDbCombinedService(const std::map<std::string, SwallowPoiDbService*>& serviceMap)
        : m_serviceMap(serviceMap)
        {
            
        }
        
        SwallowPoiDbCombinedService::~SwallowPoiDbCombinedService()
        {
            for(std::map<std::string, SwallowPoiDbService*>::const_iterator it = m_serviceMap.begin(); it != m_serviceMap.end(); ++it)
            {
                Eegeo_DELETE (*it).second;
            }
            
            m_serviceMap.clear();
        }
        
        void SwallowPoiDbCombinedService::FullTextSearch(const std::string& query, std::vector<Search::SdkModel::SearchResultModel>& out_results)
        {
            for(std::map<std::string, SwallowPoiDbService*>::const_iterator it = m_serviceMap.begin(); it != m_serviceMap.end(); ++it)
            {
                Eegeo::SQLite::SQLiteSpellingSuggestionResults spellingSuggestions;
                (*it).second->SuggestSpelling(query, spellingSuggestions);
                
                (*it).second->FullTextSearch(query, out_results);
            }
        }
        
        void SwallowPoiDbCombinedService::CategorySearch(const std::string& categoryName, std::vector<Search::SdkModel::SearchResultModel>& out_results)
        {
            std::map<std::string, SwallowPoiDbService*>::const_iterator it = m_serviceMap.find(categoryName);
            
            if(it != m_serviceMap.end())
            {
                (*it).second->FullTableSearch(out_results);
            }
        }
    }
}