// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once
#include "IHighlightColorMapper.h"
#include "ISearchResultRepository.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                class HighlightColorMapper : public IHighlightColorMapper
                {
                public:
                    HighlightColorMapper(const Eegeo::v4& defaultColor)
                    : m_defaultColor(defaultColor)
                    {}
                    
                    Eegeo::v4 GetColor(const Search::SdkModel::SearchResultModel& result, const std::string highlightColor) const;
                private:
                    const Eegeo::v4 m_defaultColor;
                };
            }
        }
    }
}