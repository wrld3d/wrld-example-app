// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SearchResultModel.h"
#include "FindDirectionService.h"
#include "DirectionQueryResponseReceivedMessage.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"


namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            FindDirectionService::FindDirectionService(FindDirectionHttpRequestFactory& findDirectionHttpRequestFactory,FindDirectionResultJsonParser& findDirectionResultParser,Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,ExampleAppMessaging::TMessageBus& messageBus)
            : m_pCurrentRequest(NULL)
            , m_findDirectionHttpRequestFactory(findDirectionHttpRequestFactory)
            , m_handleResponseCallback(this,&FindDirectionService::HandleRouteDirectionResponse)
            , m_findDirectionResultParser(findDirectionResultParser)
            , m_failAlertHandler(this, &FindDirectionService::OnFailedToCallRouteResponse)
            , m_alertBoxFactory(alertBoxFactory)
            , m_messageBus(messageBus)

            {
                
            }
            FindDirectionService::~FindDirectionService()
            {
                
            }
            void FindDirectionService::InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.AddCallback(callback);
            }
            
            void FindDirectionService::RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.RemoveCallback(callback);
            }
            
            void FindDirectionService::PerformLocationQuerySearch(const Direction::SdkModel::FindDirectionQuery& findDirectionQuery)
            {
                if(m_pCurrentRequest != NULL)
                {
                    m_pCurrentRequest->Cancel();
                }
                
                m_pCurrentRequest = m_findDirectionHttpRequestFactory.CreateFindDirectionQuery(findDirectionQuery, m_handleResponseCallback);
                m_pCurrentRequest->Dispatch();

            }
            
            void FindDirectionService::HandleRouteDirectionResponse()
            {
                Eegeo_ASSERT(m_pCurrentRequest != NULL, "Find Direction request must have been performed");
                
                if(m_pCurrentRequest->IsSucceeded())
                {
                    const std::string& response(m_pCurrentRequest->ResponseString());
                    DirectionResultModel result =  m_findDirectionResultParser.ParseGeoNamesQueryResults(response);
                     m_messageBus.Publish(DirectionResultSection::DirectionQueryResponseReceivedMessage(result));
                    
                    if(result.GetCode() == "Error")
                    {
                         m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                    }

                }
                else
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                }
                m_pCurrentRequest = NULL;
            }
            
            void FindDirectionService::OnFailedToCallRouteResponse()
            {
                
            }


        }
    }
}
