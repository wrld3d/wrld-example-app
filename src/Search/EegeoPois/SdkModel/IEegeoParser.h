// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class IEegeoParser
                {
                public:
                    virtual ~IEegeoParser() { }
                    
                    virtual void ParseEegeoQueryResults(const std::string& serialized,
                                                            std::vector<Search::SdkModel::SearchResultModel>& out_results) = 0;
                    
                };
            }
        }
    }
}
