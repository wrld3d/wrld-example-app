// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IYelpSearchQuery.h"
#include "Types.h"
#include "ICallback.h"
#include "WindowsNativeState.h"
#include "IYelpCategoryMapper.h"
#include "IdentitySearchCallbackData.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class WindowsYelpBusinessQuery : public SdkModel::IYelpSearchQuery, private Eegeo::NonCopyable
            {
            public:
                WindowsYelpBusinessQuery(
                    WindowsNativeState& nativeState,
                    const std::string& yelpConsumerKey,
                    const std::string& yelpConsumerSecret,
                    const std::string& yelpOAuthToken,
                    const std::string& yelpOAuthTokenSecret,
                    SdkModel::IYelpCategoryMapper& yelpCategoryMapper,
                    const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                    Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);

                ~WindowsYelpBusinessQuery();

                void Dispatch();

                void Cancel();

                void HandleQueryCompleted(bool success, const std::string& queryResult);

                bool IsSucceeded();

                const std::string& ResponseString();

            private:
                //jclass m_yelpSearchQueryClass;
                //jobject m_yelpSearchQuery;
                WindowsNativeState& m_nativeState;
                SdkModel::IYelpCategoryMapper& m_yelpCategoryMapper;
                Search::SdkModel::SearchResultModel m_outdatedSearchResult;
                Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& m_callback;
                std::string m_responseString;
                bool m_cancelled;
                bool m_dispatched;
                bool m_isSuccess;
            };
        }
    }
}