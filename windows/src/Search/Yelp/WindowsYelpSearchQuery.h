// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IYelpSearchQuery.h"
#include "Types.h"
#include "SearchQuery.h"
#include "ICallback.h"
#include "WindowsNativeState.h"

#include "liboauthcpp.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class WindowsYelpSearchQuery : public SdkModel::IYelpSearchQuery, private Eegeo::NonCopyable
            {
            public:
                WindowsYelpSearchQuery(
                        WindowsNativeState& nativeState,
                        const std::string& yelpConsumerKey,
                        const std::string& yelpConsumerSecret,
                        const std::string& yelpOAuthToken,
                        const std::string& yelpOAuthTokenSecret,
                        const Search::SdkModel::SearchQuery& searchQuery,
                        Eegeo::Helpers::ICallback0& completionCallback);
                
                ~WindowsYelpSearchQuery();
                
                void Dispatch();
                
                void Cancel();
                
                void HandleQueryCompleted(const std::string& queryString, bool success);

                bool IsSucceeded();
                
                const std::string& ResponseString();
                
                const Search::SdkModel::SearchQuery& GetSearchQuery() const;
                
            private:
                Helpers::ReflectionHelpers::Method<System::String^, float, float, System::Delegate^> Search;
                
                WindowsNativeState& m_nativeState;
                Search::SdkModel::SearchQuery m_searchQuery;
                Eegeo::Helpers::ICallback0& m_completionCallback;
                std::string m_responseString;
                bool m_cancelled;
                bool m_dispatched;
                bool m_isSuccess;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;
            };
        }
    }
}
