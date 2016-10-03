// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once
#include "ISearchResultRepository.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                class IHighlightColorMapper
                {
                public:
                    virtual ~IHighlightColorMapper() {}
                    
                    virtual Eegeo::v4 GetColor(const Search::SdkModel::SearchResultModel& result, const std::string highlightColor) const = 0;
                };
            }
        }
    }
}