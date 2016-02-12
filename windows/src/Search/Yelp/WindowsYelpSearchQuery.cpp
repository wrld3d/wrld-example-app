// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <sstream>

#include "WindowsYelpSearchQuery.h"
#include "WindowsAppThreadAssertionMacros.h"

#using "System.dll"
#include <msclr\marshal_cppstd.h>

#include "ReflectionHelpers.h"

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            public ref class YelpSearchQueryCallbackHandler
            {
            public:
                static void HandleCallBack(System::String^ str, System::IntPtr pointer)
                {
                    std::string data =  msclr::interop::marshal_as<std::string>(str);
                    WindowsYelpSearchQuery *view = (WindowsYelpSearchQuery*)pointer.ToPointer();
                    if (!data.empty())
                    {
                        view->HandleQueryCompleted(data, true);
                    }
                    else
                    {
                        view->HandleQueryCompleted(data, false);
                    }
                }
            };

            public delegate void CallbackDelegate(System::String^, System::IntPtr);

            WindowsYelpSearchQuery::WindowsYelpSearchQuery(
                    WindowsNativeState& nativeState,
                    const std::string& yelpConsumerKey,
                    const std::string& yelpConsumerSecret,
                    const std::string& yelpOAuthToken,
                    const std::string& yelpOAuthTokenSecret,
                    const Search::SdkModel::SearchQuery& searchQuery,
                    Eegeo::Helpers::ICallback0& completionCallback)
            : MaxRadiusMetres(40000.0f)
			, m_nativeState(nativeState)
            , m_searchQuery(searchQuery)
            , m_completionCallback(completionCallback)
            , m_responseString()
            , m_cancelled(false)
            , m_dispatched(false)
            , m_isSuccess(false)
			, m_yelpConsumerKey(yelpConsumerKey)
			, m_yelpConsumerSecret(yelpConsumerSecret)
			, m_yelpOAuthToken(yelpOAuthToken)
			, m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
            {
                m_uiViewClass = Helpers::ReflectionHelpers::GetTypeFromEntryAssembly("ExampleAppWPF.YelpAPIClient");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(Helpers::ReflectionHelpers::CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(Helpers::ReflectionHelpers::CreateObjects(gcnew IntPtr(this)));

                Search.SetupMethod(m_uiViewClass, m_uiView, "Search");
            }
            
            WindowsYelpSearchQuery::~WindowsYelpSearchQuery()
            {
            }
            
            void WindowsYelpSearchQuery::Dispatch()
            {
                ASSERT_NATIVE_THREAD

                Eegeo_ASSERT(!m_dispatched, "Cannot dispatch WindowsYelpSearchQuery if query has already been dispatched.\n");
                m_dispatched = true;

                CallbackDelegate^ function = gcnew CallbackDelegate(&YelpSearchQueryCallbackHandler::HandleCallBack);

				std::string searchTerm = "";
				std::string categoryFilter = "";

				if (m_searchQuery.IsCategory())
				{
					categoryFilter = m_searchQuery.Query();
				}
				else
				{
					searchTerm = m_searchQuery.Query();
				}

				int radiusFilter = (int)((m_searchQuery.Radius() > MaxRadiusMetres || !m_searchQuery.IsCategory()) ? MaxRadiusMetres : m_searchQuery.Radius());
                
				Search(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_yelpConsumerKey),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_yelpConsumerSecret),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_yelpOAuthToken),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(m_yelpOAuthTokenSecret),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(searchTerm),
					Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(categoryFilter),
					static_cast<float>(m_searchQuery.Location().GetLatitudeInDegrees()),
					static_cast<float>(m_searchQuery.Location().GetLongitudeInDegrees()),
					radiusFilter,
					function);
            }
            
            void WindowsYelpSearchQuery::Cancel()
            {
                ASSERT_NATIVE_THREAD

                Eegeo_ASSERT(m_dispatched, "Cannot cancel WindowsYelpSearchQuery until query has been dispatched.\n");
                m_cancelled = true;
            }

            void WindowsYelpSearchQuery::HandleQueryCompleted(const std::string& queryString, bool success)
            {
                //OutputDebugString(m_webRequestReturnData.c_str());
                if(!m_cancelled)
            	{
            		m_isSuccess = success;
            		m_responseString = queryString;
                	m_completionCallback();
            	}

                Eegeo_DELETE this;
            }
            
            bool WindowsYelpSearchQuery::IsSucceeded()
            {
                ASSERT_NATIVE_THREAD

                return m_isSuccess;
            }
            
            const std::string& WindowsYelpSearchQuery::ResponseString()
            {
                ASSERT_NATIVE_THREAD

                return m_responseString;
            }
            
            const Search::SdkModel::SearchQuery& WindowsYelpSearchQuery::GetSearchQuery() const
            {
                ASSERT_NATIVE_THREAD

                return m_searchQuery;
            }
        }
    }
}
