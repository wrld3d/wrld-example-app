// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "FindDirectionQuery.h"
#include "FindDirectionHttpRequest.h"
#include "FindDirectionResultJsonParser.h"
#include "FindDirectionHttpRequestFactory.h"
#include "SearchResultModel.h"
#include "BidirectionalBus.h"

#include "IAlertBoxFactory.h"
#include "AlertBox.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

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
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<FindDirectionService> m_failAlertHandler;
                
                void HandleRouteDirectionResponse();
                void OnFailedToCallRouteResponse();

            public:
                
                FindDirectionService(FindDirectionHttpRequestFactory& findDirectionHttpRequestFactory,FindDirectionResultJsonParser& m_findDirectionResultParser,Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,ExampleAppMessaging::TMessageBus& messageBus);
                ~FindDirectionService();
                void InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback);
                
                void RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback);
                void PerformLocationQuerySearch(const Direction::SdkModel::FindDirectionQuery& findDirectionQuery);

            };
        }
    }
}