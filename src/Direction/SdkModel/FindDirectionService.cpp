// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SearchResultModel.h"
#include "FindDirectionService.h"


namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            FindDirectionService::FindDirectionService(FindDirectionHttpRequestFactory& findDirectionHttpRequestFactory,FindDirectionResultJsonParser& findDirectionResultParser)
            : m_pCurrentRequest(NULL)
            , m_findDirectionHttpRequestFactory(findDirectionHttpRequestFactory)
            , m_handleResponseCallback(this,&FindDirectionService::HandleRouteDirectionResponse)
            , m_findDirectionResultParser(findDirectionResultParser)

            {
                
            }
            FindDirectionService::~FindDirectionService()
            {
                
            }
            void FindDirectionService::InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const FindDirectionQuery&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.AddCallback(callback);
            }
            
            void FindDirectionService::RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const FindDirectionQuery&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.RemoveCallback(callback);
            }
            
            void FindDirectionService::PerformLocationQuerySearch(const Direction::SdkModel::FindDirectionQuery& findDirectionQuery)
            {
                m_pCurrentRequest = m_findDirectionHttpRequestFactory.CreateYelpSearchForQuery(findDirectionQuery, m_handleResponseCallback);
                m_pCurrentRequest->Dispatch();

            }
            
            void FindDirectionService::HandleRouteDirectionResponse()
            {
                Eegeo_ASSERT(m_pCurrentRequest != NULL, "Find Direction request must have been performed");
                
                
                if(m_pCurrentRequest->IsSucceeded())
                {
                    const std::string& response(m_pCurrentRequest->ResponseString());
                    m_findDirectionResultParser.ParseGeoNamesQueryResults(response);
                }
                
                m_pCurrentRequest = NULL;
            }


        }
    }
}
