// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "FindDirectionQuery.h"
#include "FindDirectionHttpRequest.h"
#include "FindDirectionResultJsonParser.h"
#include "FindDirectionHttpRequestFactory.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class FindDirectionService
            {
            private:
                
                Eegeo::Helpers::CallbackCollection2<const FindDirectionQuery&, const std::vector<Search::SdkModel::SearchResultModel>& > m_findDirectionqueryResponseReceivedCallbacks;
                FindDirectionHttpRequest* m_pCurrentRequest;
                FindDirectionHttpRequestFactory& m_findDirectionHttpRequestFactory;
                Eegeo::Helpers::TCallback0<FindDirectionService> m_handleResponseCallback;
                FindDirectionResultJsonParser& m_findDirectionResultParser;
                
                void HandleRouteDirectionResponse();

            public:
                
                FindDirectionService(FindDirectionHttpRequestFactory& findDirectionHttpRequestFactory,FindDirectionResultJsonParser& m_findDirectionResultParser);
                ~FindDirectionService();
                void InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const FindDirectionQuery&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback);
                
                void RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback2<const FindDirectionQuery&, const std::vector<Search::SdkModel::SearchResultModel>& >& callback);
                void PerformLocationQuerySearch(const Direction::SdkModel::FindDirectionQuery& findDirectionQuery);

            };
        }
    }
}