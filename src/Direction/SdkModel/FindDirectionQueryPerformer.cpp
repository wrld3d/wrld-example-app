// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "FindDirectionQueryPerformer.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {

            FindDirectionQueryPerformer::FindDirectionQueryPerformer(FindDirectionService& findDirectionsService)
            : m_findDirectionService(findDirectionsService)
            , m_pFindDirectionResultResponseReceivedCallback( Eegeo_NEW((Eegeo::Helpers::TCallback2<FindDirectionQueryPerformer, const FindDirectionQuery&, const std::vector<Search::SdkModel::SearchResultModel>&>))(this, &FindDirectionQueryPerformer::HandleSearchResultsResponseReceived))

            {
                m_findDirectionService.InsertOnReceivedQueryResultsCallback(*m_pFindDirectionResultResponseReceivedCallback);

            }
            
            FindDirectionQueryPerformer::~FindDirectionQueryPerformer()
            {
                m_findDirectionService.RemoveOnReceivedQueryResultsCallback(*m_pFindDirectionResultResponseReceivedCallback);
                Eegeo_DELETE m_pFindDirectionResultResponseReceivedCallback;
            
            }
            
            void FindDirectionQueryPerformer::PerformFindDirectionQuery( const Eegeo::Space::LatLongAltitude& startLocation, const Eegeo::Space::LatLongAltitude& endlocation, bool isInterior)
            {
                FindDirectionQuery findDirectionQuery(startLocation, endlocation, isInterior);
                m_findDirectionService.PerformLocationQuerySearch(findDirectionQuery);
            }
            
            void FindDirectionQueryPerformer::HandleSearchResultsResponseReceived(const FindDirectionQuery& query,const std::vector<Search::SdkModel::SearchResultModel>& results)
            {
            
            }

            
        }
    }
}
