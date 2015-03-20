// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IYelpSearchQuery.h"
#include "Types.h"
#include "ICallback.h"
#include "AndroidNativeState.h"
#include "IYelpCategoryMapper.h"
#include "IdentitySearchCallbackData.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class AndroidYelpBusinessQuery : public IYelpSearchQuery, private Eegeo::NonCopyable
            {
            public:
            	AndroidYelpBusinessQuery(
                		AndroidNativeState& nativeState,
            			const std::string& yelpConsumerKey,
            			const std::string& yelpConsumerSecret,
            			const std::string& yelpOAuthToken,
            			const std::string& yelpOAuthTokenSecret,
                        IYelpCategoryMapper& yelpCategoryMapper,
                        const std::string& locationIdentifier,
                        Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback);

                ~AndroidYelpBusinessQuery();

                void Dispatch();

                void Cancel();

                void HandleQueryCompleted(bool success, const std::string& queryResult);

                bool IsSucceeded();

                const std::string& ResponseString();

            private:
                jclass m_yelpSearchQueryClass;
                jobject m_yelpSearchQuery;
        		AndroidNativeState& m_nativeState;
                IYelpCategoryMapper& m_yelpCategoryMapper;
                const std::string& m_locationIdentifier;
                Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& m_callback;
                std::string m_responseString;
                bool m_cancelled;
                bool m_dispatched;
                bool m_isSuccess;
            };
        }
    }
}
