// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiDb.h"
#include "SQLite.h"

#include "SQLiteDbWebLoaderCompletedHandler.h"
#include "SQLiteTextSearchableTableOffsetInfo.h"
#include "SQLiteSpellfixOptions.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace PoiDb
    {
        class IPoiDbService
        {
        public:
            virtual ~IPoiDbService() {;}
            
            virtual bool SuggestSpelling(const std::string& query, Eegeo::SQLite::SQLiteSpellingSuggestionResults& out_spellingSuggestions) = 0;
            
            virtual bool FullTextSearch(const std::string& query, PoiFtsResults& out_results) = 0;
            
            virtual bool FullTextSearch(const std::string& query, int resultsPerPage, int pageOffset, PoiFtsResults& out_results) = 0;
            
            virtual bool SelectRow(int rowId, PoiTableDto& out_poi) = 0;
            
            virtual bool CountRows(int& out_poiTableRowCount) = 0;
            
            virtual bool SelectDistinctCategoryNames(std::vector<std::string>& out_categoryNames) = 0;
            
            virtual bool CategorySearch(const std::string& categoryName, std::vector<PoiTableDto>& out_pois) = 0;
            
            virtual bool CategoryRadiusSearch(const std::string& categoryName, double latitudeDegrees, double longitudeDegrees, double maxRadiusMetres, std::vector<PoiTableDto>& out_pois) = 0;
            
            virtual bool RadiusSearch(double latitudeDegrees, double longitudeDegrees, double maxRadiusMetres, std::vector<PoiTableDto>& out_pois) = 0;
            
            virtual bool RadiusSearch(double latitudeDegrees, double longitudeDegrees, double maxRadiusMetres, const std::string& constraints, bool orderByDistance, int maxResults, std::vector<PoiTableDto>& out_pois, std::vector<double>& out_distances) = 0;
        };
    }
}