// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IPoiDbService.h"
#include "Types.h"
#include "SQLite.h"

#include "SQLiteDbWebLoaderCompletedHandler.h"
#include "SQLiteSpellfixOptions.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace PoiDb
    {
        /*! \brief allows query operations to be performed on a db table containing Point-of-interest records
         */
        class PoiDbService : public IPoiDbService, Eegeo::NonCopyable
        {
        public:
            PoiDbService(Eegeo::SQLite::SQLiteDbConnection* pSQLiteDbConnection,
                         Eegeo::SQLite::SQLiteFtsComponent* pPoiFtsComponent,
                         Eegeo::SQLite::SQLiteLatLongQueryBuilder* pLatLongQueryBuilder,
                         const std::string& assetsBaseUrl,
                         const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions);
            
            virtual ~PoiDbService();
            
            /*! \brief Obtain spelling correction suggestions for input query term, based on words contained in the PoiDb corpus
             *  \param query. Input string. If this contains more than one word, attempts to parse as SQLite FTS Enhanced Query Syntax (http://www.sqlite.org/fts3.html#section_3_1), and performs a spelling suggestion for each non-keyword term.
             *  \param out_spellingSuggestions. Field spellCheckedSearchQuery provides a best-suggestion for the input, suitable
             *  for subsequently passing as query param of FullTestSearch. Field spellFixedTerms contains more detailed spelling
             *  suggestion information, with an element for each of the input query terms.
             *  \return true if no error occurred, false otherwise
             */
            virtual bool SuggestSpelling(const std::string& query, Eegeo::SQLite::SQLiteSpellingSuggestionResults& out_spellingSuggestions);
            
            /*! \brief Perform a full-text-search of poi table
             *  \param query. Input terms to seach for. May include AND, OR, NOT, parenthesis, quoted phrases, adhering to SQLite FTS Enhanced Query Syntax
             *  \param out_results. Results of search.
             *  \return true if no error occurred, false otherwise
             */
            virtual bool FullTextSearch(const std::string& query, PoiFtsResults& out_results);
            
            /*! \brief Perform a full-text-search of poi table
             *  \param query. Input terms to seach for. May include AND, OR, NOT, parenthesis, quoted phrases, adhering to SQLite FTS Enhanced Query Syntax
             *  \param resultsPerPage. Limit of number of results to be returned. Pass zero or negative for no limit.
             *  \param pageOffset. Offset of start of paginated results - ie row index of results will start at (pageOffset*resultsPerPage)
             *  \param out_results. Results of search.
             *  \return true if no error occurred, false otherwise
             */
            virtual bool FullTextSearch(const std::string& query, int resultsPerPage, int pageOffset, PoiFtsResults& out_results);
            
            /*! \brief Perform a SELECT on poi table for a single row of specified id
             *  \param rowId. Value of ID column to select
             *  \param out_poi. Result poi row.
             *  \return true if no error occurred, false otherwise
             */
            virtual bool SelectRow(int rowId, PoiTableDto& out_poi);
            
            /*! \brief Count number of rows in poi table
             *  \param out_poiTableRowCount number of rows in poi table
             *  \return true if no error occurred, false otherwise
             */
            virtual bool CountRows(int& out_poiTableRowCount);
            
            /*! Obtain distinct values of rows in the Category column of poi table
             *  \param out_categoryNames resultant category names
             *  \return true if no error occurred, false otherwise
             */
            virtual bool SelectDistinctCategoryNames(std::vector<std::string>& out_categoryNames);
            
            /*! \brief Obtain all poi rows matching a category
             *  \param categoryName category value to match. May be "*", in which case all rows are selected
             *  \param out_pois poi rows matching input category
             *  \return true if no error occurred, false otherwise
             */
            virtual bool CategorySearch(const std::string& categoryName, std::vector<PoiTableDto>& out_pois);
            
            /*! \brief Obtain all poi rows matching a category and that are located within a specified circle
             *  \param categoryName category value to match. May be "*", in which case all rows are selected
             *  \param latitudeDegrees latitude of search centre in degrees
             *  \param longitudeDegrees longitude of search centre in degrees, in range -180 -> 180
             *  \param maxRadiusMetres max distance of selected poi from search centre
             *  \param out_pois poi row results.
             *  \return true if no error occurred, false otherwise
             */
            virtual bool CategoryRadiusSearch(const std::string& categoryName, double latitudeDegrees, double longitudeDegrees, double maxRadiusMetres, std::vector<PoiTableDto>& out_pois);
            
            /*! \brief Obtain all poi rows that are located within a specified circle
             *  \param latitudeDegrees latitude of search centre in degrees
             *  \param longitudeDegrees longitude of search centre in degrees, in range -180 -> 180
             *  \param maxRadiusMetres max distance of selected poi from search centre
             *  \param out_pois poi row results.
             *  \return true if no error occurred, false otherwise
             */
            virtual bool RadiusSearch(double latitudeDegrees, double longitudeDegrees, double maxRadiusMetres, std::vector<PoiTableDto>& out_pois);
            
            /*! \brief Obtain all poi rows that are located within a specified circle, and matching specified SQL "WHERE" contraints
             *  \param latitudeDegrees latitude of search centre in degrees
             *  \param longitudeDegrees longitude of search centre in degrees, in range -180 -> 180
             *  \param maxRadiusMetres max distance of selected poi from search centre
             *  \param orderByDistance. true to order results by ascending distance from search centre.
             *  \param maxResults. Limit results to maximum number of rows (<=0 for no limit)
             *  \param constraints. Expression evaluating to true or false as condition of a WHERE clause within SELECT statement.
             *  \param out_pois poi row results.
             *  \param out_distances distances, in metres, of result pois from search centre. Each element corresponds to element at same
             *  index in out_pois.
             *  \return true if no error occurred, false otherwise
             */
            virtual bool RadiusSearch(double latitudeDegrees, double longitudeDegrees, double maxRadiusMetres, const std::string& constraints, bool orderByDistance, int maxResults, std::vector<PoiTableDto>& out_pois, std::vector<double>& out_distances);
            
            
        private:
            Eegeo::SQLite::SQLiteDbConnection* m_pSQLiteDbConnection;
            Eegeo::SQLite::SQLiteFtsComponent* m_pPoiFtsComponent;
            Eegeo::SQLite::SQLiteLatLongQueryBuilder* m_pLatLongQueryBuilder;
            Eegeo::SQLite::SQLiteSpellfixOptions m_spellFixOptions;
            const std::string m_assetsBaseUrl;
        };
    }
}