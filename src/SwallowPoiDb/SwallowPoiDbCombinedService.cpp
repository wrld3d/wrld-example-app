// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbCombinedService.h"

#include "SQLiteResultCells.h"
#include "SQLiteSpellingSuggestionResults.h"
#include "SQLiteTable.h"
#include "SQLiteTableQueryHelpers.h"

#include "SwallowPoiDbService.h"
#include "SwallowPoiDbTransitionParser.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        const std::string categoryColumnName = "category";
        
        SwallowPoiDbCombinedService::SwallowPoiDbCombinedService(const std::map<std::string, SwallowPoiDbService*>& serviceMap,
                                                                 Eegeo::SQLite::SQLiteTable* pTransitionsTable)
        : m_serviceMap(serviceMap)
        , m_pTransitionsTable(pTransitionsTable)
        {
            
        }
        
        SwallowPoiDbCombinedService::~SwallowPoiDbCombinedService()
        {
            for(std::map<std::string, SwallowPoiDbService*>::const_iterator it = m_serviceMap.begin(); it != m_serviceMap.end(); ++it)
            {
                Eegeo_DELETE (*it).second;
            }
            
            m_serviceMap.clear();
            
            Eegeo_DELETE m_pTransitionsTable;
        }
        
        void SwallowPoiDbCombinedService::FullTextSearch(const std::string& query, std::vector<Search::SdkModel::SearchResultModel>& out_results)
        {
            for(std::map<std::string, SwallowPoiDbService*>::const_iterator it = m_serviceMap.begin(); it != m_serviceMap.end(); ++it)
            {
                Eegeo::SQLite::SQLiteSpellingSuggestionResults spellingSuggestions;
                (*it).second->SuggestSpelling(query, spellingSuggestions);
                
                (*it).second->FullTextSearch(spellingSuggestions.spellCheckedSearchQuery, out_results);
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
        
        void SwallowPoiDbCombinedService::GetTransitionResults(std::vector<Search::SdkModel::SearchResultModel>& out_results)
        {
            Eegeo_ASSERT(m_pTransitionsTable != NULL, "Couldn't find transition table in SwallowPoiDbService");
            
            Eegeo::SQLite::SQLiteResultCells* pResult = NULL;
            
            bool succeed = Eegeo::SQLite::MakeQuery_SelectAll(*m_pTransitionsTable).Execute(pResult);
            
            Parsers::SwallowPoiDbTransitionParser swallowPoiDbTransitionParser;
            
            if (succeed)
            {
                for(int i = 0; i < pResult->RowCount(); ++i)
                {
                    out_results.push_back(swallowPoiDbTransitionParser.SQLiteResultRowToSearchResult(pResult->Row(i), "", 0));
                }
            }
            
            Eegeo_DELETE pResult;
        }
    }
}