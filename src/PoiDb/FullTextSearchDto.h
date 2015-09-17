// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiDb.h"
#include "SQLiteTextSearchableTableOffsetInfo.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace PoiDb
    {
        struct FullTextSearchDto
        {
            //! formatted text highlighting context of occurrence of search term. See http://www.sqlite.org/fts3.html#section_4_2
            std::string snippet;
            
            //! Detailed breakdown of occurrence of search term
            std::vector<Eegeo::SQLite::SQLiteTextSearchableTableOffsetInfo> offsets;
        };
    }
}