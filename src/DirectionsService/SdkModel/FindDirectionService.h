// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "FindDirectionQuery.h"
#include "FindDirectionHttpRequest.h"
#include "FindDirectionResultJsonParser.h"
#include "FindDirectionHttpRequestFactory.h"
#include "SearchResultModel.h"
#include "BidirectionalBus.h"


namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class FindDirectionService
            {
            private:
                
                Eegeo::Helpers::CallbackCollection1<const DirectionResultModel&> m_findDirectionqueryResponseReceivedCallbacks;
                FindDirectionHttpRequest* m_pCurrentRequest;
                FindDirectionHttpRequestFactory& m_findDirectionHttpRequestFactory;
                Eegeo::Helpers::TCallback0<FindDirectionService> m_handleResponseCallback;
                FindDirectionResultJsonParser& m_findDirectionResultParser;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                
                void HandleRouteDirectionResponse();

            public:
                
                FindDirectionService(FindDirectionHttpRequestFactory& findDirectionHttpRequestFactory,FindDirectionResultJsonParser& m_findDirectionResultParser,ExampleAppMessaging::TMessageBus& messageBus);
                ~FindDirectionService();
                void InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback);
                
                void RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback);
                void PerformLocationQuerySearch(const Direction::SdkModel::FindDirectionQuery& findDirectionQuery);

            };
        }
    }
}