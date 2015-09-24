// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IGeoNamesParser.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class GeoNamesJsonParser : public IGeoNamesParser, private Eegeo::NonCopyable
                {
                public:
                    
                    void ParseGeoNamesQueryResults(const std::string& serialized,
                                                   std::vector<GeoNamesSearchResultDto>& out_results);
                    
                };
            }
        }
    }
}
