// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRouting.h"
#include "Location.h"
#include "Search.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {
                class INavTurnByTurnCompletionHandler
                {
                public:
                    virtual ~INavTurnByTurnCompletionHandler() {}
                    virtual void HighlightOnCompletion(const Search::SdkModel::SearchResultModel& m_searchResultModel) = 0;

                };
            }
        }
    }
}
