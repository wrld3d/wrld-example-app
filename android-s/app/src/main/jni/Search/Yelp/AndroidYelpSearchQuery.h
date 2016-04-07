// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IYelpSearchQuery.h"
#include "Types.h"
#include "SearchQuery.h"
#include "ICallback.h"
#include "AndroidNativeState.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class AndroidYelpSearchQuery : public SdkModel::IYelpSearchQuery, private Eegeo::NonCopyable
            {
            public:
            	AndroidYelpSearchQuery(
                		AndroidNativeState& nativeState,
            			const std::string& yelpConsumerKey,
            			const std::string& yelpConsumerSecret,
            			const std::string& yelpOAuthToken,
            			const std::string& yelpOAuthTokenSecret,
            			const Search::SdkModel::SearchQuery& searchQuery,
            			Eegeo::Helpers::ICallback0& completionCallback);
                
                ~AndroidYelpSearchQuery();
                
                void Dispatch();
                
                void Cancel();
                
                void HandleQueryCompleted(bool success, const std::string& queryResult);

                bool IsSucceeded();
                
                const std::string& ResponseString();
                
                const Search::SdkModel::SearchQuery& GetSearchQuery() const;
                
            private:
                jclass m_yelpSearchQueryClass;
                jobject m_yelpSearchQuery;
        		AndroidNativeState& m_nativeState;
        		Search::SdkModel::SearchQuery m_searchQuery;
                Eegeo::Helpers::ICallback0& m_completionCallback;
                std::string m_responseString;
                bool m_cancelled;
                bool m_dispatched;
                bool m_isSuccess;
            };
        }
    }
}
