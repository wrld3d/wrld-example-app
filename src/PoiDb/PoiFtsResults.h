// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiDb.h"
#include "PoiTableDto.h"
#include "FullTextSearchDto.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace PoiDb
    {
        //! Poi Full-text-search results
        struct PoiFtsResults
        {
            //! number of result rows returned per page
            int resultsPerPage;
            
            //! total result rows for query (regardless of resultsPerPage)
            int totalResults;
            
            //! page offset of these results (ie rows start at row index pageOffset*resultsPerPage
            int pageOffset;
            
            //! PageOffset of next page of results beyond this page (pageOffset + 1 if further results remain, -1 otherwise)
            int nextPageOffset;
            
            //! Poi table row results
            std::vector<PoiTableDto> resultRows;
            
            //! additional full-text-search information, each element corresponds to element at same index in resultsRows
            std::vector<FullTextSearchDto> ftsResultRows;
            
            PoiFtsResults()
            : resultsPerPage(0)
            , totalResults(0)
            , pageOffset(0)
            , nextPageOffset(0)
            {
                
            }
        };
    }
}