// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiDbService.h"
#include "Types.h"
#include "SQLite.h"

#include "SQLiteDbConnection.h"
#include "SQLiteTextSearchableTable.h"
#include "SQLiteTextSearchableTableFactory.h"
#include "SQLiteHelpers.h"
#include "SQLiteCellValue.h"
#include "SQLiteResultRow.h"
#include "SQLiteResultCells.h"
#include "SQLiteTextSearchableTableResults.h"
#include "SQLiteFtsQuerySpellingFixer.h"
#include "SQLiteSpellingSuggestionResults.h"
#include "SQLiteFtsTokenizerType.h"
#include "SQLiteFtsSnippetFormattingConfig.h"
#include "SQLiteFtsComponent.h"
#include "SQLiteFtsComponentFactory.h"
#include "SQLiteLatLongQueryBuilder.h"
#include "SQLiteTableQueryHelpers.h"
#include "PoiTableDto.h"
#include "PoiFtsResults.h"


namespace ExampleApp
{
    namespace PoiDb
    {
        namespace
        {
            enum FtsColumnIndices
            {
                fts_row_id = 0,
                fts_snippet,
                fts_offsets,
                FtsQueryColumnIndices_MAX
            };
            
            enum PoiColumnIndices
            {
                poi_id = 0,
                poi_name,
                poi_job_title,
                poi_image_filename,
                poi_workingGroup,
                poi_office_location,
                poi_desk_code,
                poi_interior_id,
                poi_interior_floor,
                poi_latitude_degrees,
                poi_longitude_degrees,
                PoiColumnIndices_MAX
            };
            
            const std::string categoryColumnName = "category";
            
            std::string GetImageUrl(const std::string& assetsBaseUrl, const std::string& rawImageFilenameField)
            {
                return rawImageFilenameField.empty() ? std::string() : assetsBaseUrl + rawImageFilenameField;
            }
            
            void SQLiteResultRowToPoiDto(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl, int columnOffset, PoiTableDto& out_poiRow)
            {
                out_poiRow.poi_id = resultRow.Cell(columnOffset + poi_id).AsInteger();
                out_poiRow.name = resultRow.Cell(columnOffset + poi_name).AsText();
                out_poiRow.job_title = resultRow.Cell(columnOffset + poi_job_title).AsText();
                out_poiRow.image_filename = resultRow.Cell(columnOffset + poi_image_filename).AsText();
                out_poiRow.office_location = resultRow.Cell(columnOffset + poi_office_location).AsText();
                out_poiRow.desk_code = resultRow.Cell(columnOffset + poi_desk_code).AsText();
                out_poiRow.interior_id = resultRow.Cell(columnOffset + poi_interior_id).AsText();
                out_poiRow.interior_floor = resultRow.Cell(columnOffset + poi_interior_floor).AsInteger();
                out_poiRow.latitude_degrees = resultRow.Cell(columnOffset + poi_latitude_degrees).AsReal();
                out_poiRow.longitude_degrees = resultRow.Cell(columnOffset + poi_longitude_degrees).AsReal();
            }
            
            void SQLiteResultRowToPoiDto(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl, PoiTableDto& out_poiRow)
            {
                return SQLiteResultRowToPoiDto(resultRow, assetsBaseUrl, 0, out_poiRow);
            }
            
            void SQLiteResultCellsToPoiDtos(const Eegeo::SQLite::SQLiteResultCells& resultCells, const std::string& assetsBaseUrl, std::vector<PoiTableDto>& out_poiTableResults)
            {
                out_poiTableResults.clear();
                out_poiTableResults.reserve(resultCells.RowCount());
                
                for (int i = 0; i < resultCells.RowCount(); ++i)
                {
                    PoiTableDto poiRow;
                    SQLiteResultRowToPoiDto(resultCells.Row(i), assetsBaseUrl, poiRow);
                    out_poiTableResults.push_back(poiRow);
                }
            }
            
            bool FtsQueryResultsToDto(const Eegeo::SQLite::SQLiteTextSearchableTableResults& ftsQueryResults, const std::string& assetsBaseUrl, PoiFtsResults& out_poiTableResults)
            {
                bool succeed = true;
                
                out_poiTableResults = PoiFtsResults();
                
                out_poiTableResults.resultsPerPage = ftsQueryResults.resultsPerPage;
                out_poiTableResults.totalResults = ftsQueryResults.totalResults;
                out_poiTableResults.pageOffset = ftsQueryResults.pageOffset;
                out_poiTableResults.nextPageOffset = ftsQueryResults.nextPageOffset;
                
                const Eegeo::SQLite::SQLiteResultCells& cells = *ftsQueryResults.resultCells;
                
                Eegeo_ASSERT(cells.RowCount() == 0 || (cells.ColumnCount() == FtsQueryColumnIndices_MAX + PoiColumnIndices_MAX));

                for (int row = 0; row < cells.RowCount(); ++row)
                {
                    const Eegeo::SQLite::SQLiteResultRow& resultRow = cells.Row(row);
                    
                    FullTextSearchDto ftsRow;
                    ftsRow.snippet = resultRow.Cell(fts_snippet).AsText();
                    const std::string& ftsOffsetText = resultRow.Cell(fts_offsets).AsText();
                    if (!Eegeo::SQLite::SQLiteTextSearchableTable::ParseOffsets(ftsOffsetText, ftsRow.offsets))
                    {
                        succeed = false;
                        Eegeo_ASSERT(false, "PoiDbService::Find error parsing full-text-search offsets");
                    }
                    
                    PoiTableDto poiRow;
                    SQLiteResultRowToPoiDto(resultRow, assetsBaseUrl, (int)FtsQueryColumnIndices_MAX, poiRow);
                    
                    out_poiTableResults.resultRows.push_back(poiRow);
                    out_poiTableResults.ftsResultRows.push_back(ftsRow);
                }
                
                return succeed;
                
            }
        }
        
        PoiDbService::PoiDbService(Eegeo::SQLite::SQLiteDbConnection* pSQLiteDbConnection,
                                   Eegeo::SQLite::SQLiteFtsComponent* pPoiFtsComponent,
                                   Eegeo::SQLite::SQLiteLatLongQueryBuilder* pLatLongQueryBuilder,
                                   const std::string& assetsBaseUrl,
                                   const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions)
        : m_pSQLiteDbConnection(pSQLiteDbConnection)
        , m_pPoiFtsComponent(pPoiFtsComponent)
        , m_pLatLongQueryBuilder(pLatLongQueryBuilder)
        , m_assetsBaseUrl(assetsBaseUrl)
        , m_spellFixOptions(spellFixOptions)
        {
            
        }
        
        PoiDbService::~PoiDbService()
        {
            Eegeo_DELETE m_pSQLiteDbConnection;
            Eegeo_DELETE m_pPoiFtsComponent;
            Eegeo_DELETE m_pLatLongQueryBuilder;
        }

        bool PoiDbService::SuggestSpelling(const std::string& query, Eegeo::SQLite::SQLiteSpellingSuggestionResults& out_spellingSuggestions)
        {
            const Eegeo::SQLite::SQLiteFtsQuerySpellingFixer& spellFixer = m_pPoiFtsComponent->GetFtsQuerySpellFixer();
            bool succeed = spellFixer.BuildSpellFixedFtsQuery(query, m_spellFixOptions, out_spellingSuggestions);
            if (!succeed)
            {
                Eegeo_TTY("PoiDbService::SuggestSpelling - error performing full-text-search spelling suggestion query");
                return false;
            }
            return true;
        }
        
        bool PoiDbService::FullTextSearch(const std::string& query, PoiFtsResults& out_results)
        {
            return FullTextSearch(query, -1, 0, out_results);
        }
        
        bool PoiDbService::FullTextSearch(const std::string& query, int resultsPerPage, int pageOffset, PoiFtsResults& out_results)
        {
            out_results = PoiFtsResults();
            
            const Eegeo::SQLite::SQLiteTextSearchableTable& ftsTable = m_pPoiFtsComponent->GetTextSearchableTable();
            
            Eegeo::SQLite::SQLiteTextSearchableTableResults queryResult;
            bool succeed = ftsTable.Find(query, resultsPerPage, pageOffset, queryResult);
            if (!succeed)
            {
                Eegeo_TTY("PoiDbService::FullTextSearch - error performing full-text-search query");
            }
            else
            {
                succeed = FtsQueryResultsToDto(queryResult, m_assetsBaseUrl, out_results);
                if (!succeed)
                {
                    Eegeo_TTY("PoiDbService::FullTextSearch - error parsing full-text-search results");
                }
            }

            Eegeo_DELETE queryResult.resultCells;
            
            return succeed;
        }
        
        bool PoiDbService::SelectRow(int rowId, PoiTableDto& out_poi)
        {
            out_poi = PoiTableDto();
            
            const Eegeo::SQLite::SQLiteTextSearchableTable& ftsTable = m_pPoiFtsComponent->GetTextSearchableTable();
         
            Eegeo::SQLite::SQLiteResultCells* pResult = NULL;
            
            bool succeed = Eegeo::SQLite::MakeQuery_SelectColumnsFromTableWhereXEqualsY("*", ftsTable, "ID", rowId).Execute(pResult);
            if (!succeed)
            {
                Eegeo_TTY("PoiDbService::FullTextSearch - error performing full-text-search query");
            }
            else if (pResult->RowCount() > 0)
            {
                SQLiteResultRowToPoiDto(pResult->Row(0), m_assetsBaseUrl, out_poi);
            }
            
            Eegeo_DELETE pResult;
            
            return succeed;
        }
        
        bool PoiDbService::CountRows(int& out_poiTableRowCount)
        {
            out_poiTableRowCount = 0;
            const Eegeo::SQLite::SQLiteTextSearchableTable& ftsTable = m_pPoiFtsComponent->GetTextSearchableTable();
            
            Eegeo::SQLite::SQLiteResultCells* pResult = NULL;
            
            bool succeed = Eegeo::SQLite::MakeQuery_Count(ftsTable).Execute(pResult);
            if (succeed)
            {
                out_poiTableRowCount = pResult->Cell(0, 0).AsInteger();
            }
            Eegeo_DELETE pResult;
            return succeed;
        }
        
        bool PoiDbService::CategorySearch(const std::string& categoryName, std::vector<PoiTableDto>& out_pois)
        {
            out_pois.clear();
            
            const Eegeo::SQLite::SQLiteTextSearchableTable& ftsTable = m_pPoiFtsComponent->GetTextSearchableTable();
            
            Eegeo::SQLite::SQLiteResultCells* pResult = NULL;
            
            bool succeed = Eegeo::SQLite::MakeQuery_SelectColumnsFromTableWhereXEqualsY("*", ftsTable, categoryColumnName, Eegeo::SQLite::ToSqlStringLiteral(categoryName))
                                .Execute(pResult);
            
            if (succeed)
            {
                SQLiteResultCellsToPoiDtos(*pResult, m_assetsBaseUrl, out_pois);
            }
            Eegeo_DELETE pResult;
            
            return succeed;
        }
        
        bool PoiDbService::CategoryRadiusSearch(const std::string& categoryName, double latitudeDegrees, double longitudeDegrees, double maxRadiusMetres, std::vector<PoiTableDto>& out_pois)
        {
            out_pois.clear();

            
            const Eegeo::SQLite::SQLiteTextSearchableTable& ftsTable = m_pPoiFtsComponent->GetTextSearchableTable();
            
            Eegeo::SQLite::SQLiteResultCells* pResult = NULL;
            
            const std::string& categoryConstraint = (categoryName == "*") ? "" : (categoryColumnName + "=" + Eegeo::SQLite::ToSqlStringLiteral(categoryName));
            
            const bool orderByDistance = true;
            const int maxResults = -1;
            Eegeo::SQLite::SQLiteTableQuery query = m_pLatLongQueryBuilder->BuildQuery_SelectColumnsFromTableWithinRadius("*", ftsTable, latitudeDegrees, longitudeDegrees, categoryConstraint, maxRadiusMetres, orderByDistance, maxResults);
            bool succeed = query.Execute(pResult);
            if (succeed)
            {
                SQLiteResultCellsToPoiDtos(*pResult, m_assetsBaseUrl, out_pois);
            }
            Eegeo_DELETE pResult;
            
            return succeed;
        }
        
        bool PoiDbService::SelectDistinctCategoryNames(std::vector<std::string>& categoryNames)
        {
            categoryNames.clear();
            
            const Eegeo::SQLite::SQLiteTextSearchableTable& ftsTable = m_pPoiFtsComponent->GetTextSearchableTable();
            
            Eegeo::SQLite::SQLiteResultCells* pResult = NULL;
            
            std::stringstream ss;
            ss << "DISTINCT " << categoryColumnName << " FROM " << ftsTable.GetTableName() << " ORDER BY " << categoryColumnName;
            Eegeo::SQLite::SQLiteTableQuery query = Eegeo::SQLite::SQLiteTableQuery::MakeSelect(ftsTable.GetDbConnection(), ss.str());
            
            bool succeed = query.Execute(pResult);
            
            if (succeed)
            {
                categoryNames.reserve(pResult->RowCount());
                for (int i = 0; i < pResult->RowCount(); ++i)
                {
                    categoryNames.push_back(pResult->Cell(i, 0).AsText());
                }
            }
            Eegeo_DELETE pResult;
            
            return succeed;
        }
        
        bool PoiDbService::RadiusSearch(double latitudeDegrees, double longitudeDegrees, double maxRadiusMetres, std::vector<PoiTableDto>& out_pois)
        {
            return CategoryRadiusSearch("*", latitudeDegrees, longitudeDegrees, maxRadiusMetres, out_pois);
        }
        
        bool PoiDbService::RadiusSearch(double latitudeDegrees, double longitudeDegrees, double maxRadiusMetres, const std::string& constraints, bool orderByDistance, int maxResults, std::vector<PoiTableDto>& out_pois, std::vector<double>& out_distances)
        {
            out_pois.clear();
            out_distances.clear();
            
            const Eegeo::SQLite::SQLiteTextSearchableTable& ftsTable = m_pPoiFtsComponent->GetTextSearchableTable();
            
            Eegeo::SQLite::SQLiteResultCells* pResult = NULL;
            
            Eegeo::SQLite::SQLiteTableQuery query = m_pLatLongQueryBuilder->BuildQuery_SelectColumnsAndDistanceFromTableWithinRadius("*", ftsTable, latitudeDegrees, longitudeDegrees, constraints, maxRadiusMetres, orderByDistance, maxResults);
            bool succeed = query.Execute(pResult);
            if (succeed)
            {
                SQLiteResultCellsToPoiDtos(*pResult, m_assetsBaseUrl, out_pois);

                int resultRowCount = pResult->RowCount();
                out_distances.reserve(resultRowCount);
                
                for (int i = 0; i < resultRowCount; ++i)
                {
                    double distanceMetres = pResult->Cell(i, PoiColumnIndices_MAX).AsReal();
                    out_distances.push_back(distanceMetres);
                }
            }
            Eegeo_DELETE pResult;
            
            return succeed;
        }
    }
}