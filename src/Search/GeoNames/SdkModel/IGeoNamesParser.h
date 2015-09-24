// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "GeoNamesSearchResultDto.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class IGeoNamesParser
                {
                public:
                    virtual ~IGeoNamesParser() { }
                    
                    virtual void ParseGeoNamesQueryResults(const std::string& serialized,
                                                           std::vector<GeoNamesSearchResultDto>& out_results) = 0;
                    
                };
            }
        }
    }
}
