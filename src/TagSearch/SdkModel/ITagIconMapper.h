// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            class ITagIconMapper
            {
            public:
                virtual ~ITagIconMapper() { }
                
                virtual ExampleApp::Search::SdkModel::TagIconKey GetIconKeyForTags(const std::vector<std::string>& tags) const = 0;
            };
        }
    }
}
