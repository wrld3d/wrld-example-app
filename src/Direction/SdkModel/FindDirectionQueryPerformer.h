// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "SearchResultModel.h"
#include "FindDirectionQuery.h"
#include "FindDirectionService.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class FindDirectionQueryPerformer : private Eegeo::NonCopyable
            {
            private:
                
                FindDirectionService& m_findDirectionService;
                Eegeo::Helpers::ICallback2<const FindDirectionQuery&, const std::vector<Search::SdkModel::SearchResultModel>&> *m_pFindDirectionResultResponseReceivedCallback;


            public:
                
                FindDirectionQueryPerformer(FindDirectionService& findDirectionsService);
                ~FindDirectionQueryPerformer();
                void PerformFindDirectionQuery( const Eegeo::Space::LatLongAltitude& startLocation, const Eegeo::Space::LatLongAltitude& endlocation, bool isInterior);
                void HandleSearchResultsResponseReceived(const FindDirectionQuery& query,const std::vector<Search::SdkModel::SearchResultModel>& results);
                
                void Dummy(){}
            };
        }
    }
}