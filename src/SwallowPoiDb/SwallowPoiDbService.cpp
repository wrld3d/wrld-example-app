// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbService.h"

#include "SQLiteFtsComponent.h"
#include "SQLiteFtsQuerySpellingFixer.h"
#include "SQLiteResultCells.h"
#include "SQLiteTableQueryHelpers.h"
#include "SQLiteTextSearchableTable.h"
#include "SQLiteTextSearchableTableResults.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        const std::string categoryColumnName = "category";
        
        SwallowPoiDbService::SwallowPoiDbService(Eegeo::SQLite::SQLiteFtsComponent* pPoiFtsComponent,
                                                 const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions,
                                                 Parsers::ISwallowPoiDbParser* pSwallowPoiDbParser,
                                                 const std::string& assetsBaseUrl)
        : m_pPoiFtsComponent(pPoiFtsComponent)
        , m_spellFixOptions(spellFixOptions)
        , m_pSwallowPoiDbParser(pSwallowPoiDbParser)
        , m_assetsBaseUrl(assetsBaseUrl)
        {
            
        }
        
        SwallowPoiDbService::~SwallowPoiDbService()
        {
            Eegeo_DELETE m_pSwallowPoiDbParser;
            
            Eegeo_DELETE m_pPoiFtsComponent;
        }
        
        bool SwallowPoiDbService::SuggestSpelling(const std::string& query, Eegeo::SQLite::SQLiteSpellingSuggestionResults& out_spellingSuggestions)
        {
            const Eegeo::SQLite::SQLiteFtsQuerySpellingFixer& spellFixer = m_pPoiFtsComponent->GetFtsQuerySpellFixer();
            bool succeed = spellFixer.BuildSpellFixedFtsQuery(query, m_spellFixOptions, out_spellingSuggestions);
            if (!succeed)
            {
                Eegeo_TTY("SwallowPoiDbService::SuggestSpelling - error performing full-text-search spelling suggestion query");
                return false;
            }
            return true;
        }
        
        void SwallowPoiDbService::FullTextSearch(const std::string& query, std::vector<Search::SdkModel::SearchResultModel>& out_results)
        {
            const Eegeo::SQLite::SQLiteTextSearchableTable& ftsTable = m_pPoiFtsComponent->GetTextSearchableTable();
            
            Eegeo::SQLite::SQLiteTextSearchableTableResults queryResult;
            bool succeed = ftsTable.Find(query, -1, 0, queryResult);
            
            if (!succeed)
            {
                Eegeo_TTY("SwallowPoiDbService::FullTextSearch - error performing full-text-search query");
            }
            else
            {
                for(int i = 0; i < queryResult.resultCells->RowCount(); ++i)
                {
                    out_results.push_back(m_pSwallowPoiDbParser->SQLiteResultRowToSearchResult(queryResult.resultCells->Row(i), m_assetsBaseUrl));
                }
            }
            
            Eegeo_DELETE queryResult.resultCells;
        }
        
        void SwallowPoiDbService::FullTableSearch(std::vector<Search::SdkModel::SearchResultModel> &out_results)
        {
            const Eegeo::SQLite::SQLiteTextSearchableTable& ftsTable = m_pPoiFtsComponent->GetTextSearchableTable();
            
            Eegeo::SQLite::SQLiteResultCells* pResult = NULL;
            
            bool succeed = Eegeo::SQLite::MakeQuery_SelectAll(ftsTable).Execute(pResult);
            
            if (succeed)
            {
                for(int i = 0; i < pResult->RowCount(); ++i)
                {
                    out_results.push_back(m_pSwallowPoiDbParser->SQLiteResultRowToSearchResult(pResult->Row(i), m_assetsBaseUrl, 0));
                }
            }
            
            Eegeo_DELETE pResult;
        }
    }
}