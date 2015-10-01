// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SQLite.h"

#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        namespace Parsers
        {
            class ISwallowPoiDbParser
            {
            public:
                virtual ~ISwallowPoiDbParser() { }
                
                virtual Search::SdkModel::SearchResultModel SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl, int columnOffset) = 0;
                
                virtual Search::SdkModel::SearchResultModel SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl) = 0;
            };
        }
    }
}