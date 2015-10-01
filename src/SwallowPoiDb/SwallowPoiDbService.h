// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SQLiteSpellfixOptions.h"

#include "ISwallowPoiDbParser.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        class SwallowPoiDbService : private Eegeo::NonCopyable
        {
        public:
            SwallowPoiDbService(Eegeo::SQLite::SQLiteFtsComponent* pPoiFtsComponent,
                                const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions,
                                Parsers::ISwallowPoiDbParser* pSwallowPoiDbParser,
                                const std::string& assetsBaseUrl);
            
            ~SwallowPoiDbService();
            
            bool SuggestSpelling(const std::string& query, Eegeo::SQLite::SQLiteSpellingSuggestionResults& out_spellingSuggestions);
            
            void FullTextSearch(const std::string& query, std::vector<Search::SdkModel::SearchResultModel>& out_results);
            
            void FullTableSearch(std::vector<Search::SdkModel::SearchResultModel> &out_results);
            
            void CategorySearch(const std::string& categoryName, std::vector<Search::SdkModel::SearchResultModel>& out_results);
        protected:
            Eegeo::SQLite::SQLiteFtsComponent* m_pPoiFtsComponent;
            Eegeo::SQLite::SQLiteSpellfixOptions m_spellFixOptions;
            Parsers::ISwallowPoiDbParser* m_pSwallowPoiDbParser;
            std::string m_assetsBaseUrl;
        };
    }
}