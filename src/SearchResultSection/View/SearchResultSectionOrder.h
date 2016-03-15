// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultSectionOrder.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            class SearchResultSectionOrder : public ISearchResultSectionOrder
            {
            public:
                
                SearchResultSectionOrder(const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);
                
                bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b);
                
            private:
                
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
            };
        }
    }
}