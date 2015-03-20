// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidYelpSearchQuery.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            AndroidYelpSearchQuery::AndroidYelpSearchQuery(
            		AndroidNativeState& nativeState,
        			const std::string& yelpConsumerKey,
        			const std::string& yelpConsumerSecret,
        			const std::string& yelpOAuthToken,
        			const std::string& yelpOAuthTokenSecret,
            		const SdkModel::SearchQuery& searchQuery,
            		Eegeo::Helpers::ICallback0& completionCallback)
            : m_nativeState(nativeState)
            , m_searchQuery(searchQuery)
            , m_completionCallback(completionCallback)
            , m_responseString()
            , m_cancelled(false)
            , m_dispatched(false)
            , m_isSuccess(false)
            {
            	ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com/eegeo/search/yelp/AndroidYelpSearchQuery");
                jclass objClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_yelpSearchQueryClass = static_cast<jclass>(env->NewGlobalRef(objClass));
                jmethodID objCtor = env->GetMethodID(m_yelpSearchQueryClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;J)V");

                jstring yelpConsumerKeyStr = env->NewStringUTF(yelpConsumerKey.c_str());
                jstring yelpConsumerSecretStr = env->NewStringUTF(yelpConsumerSecret.c_str());
                jstring yelpOAuthTokenStr = env->NewStringUTF(yelpOAuthToken.c_str());
                jstring yelpOAuthTokenSecretStr = env->NewStringUTF(yelpOAuthTokenSecret.c_str());

                jobject instance = env->NewObject(
                		m_yelpSearchQueryClass,
                		objCtor,
                		m_nativeState.activity,
                		yelpConsumerKeyStr,
                		yelpConsumerSecretStr,
                		yelpOAuthTokenStr,
                		yelpOAuthTokenSecretStr,
                		(jlong)(this)
                );

                m_yelpSearchQuery = env->NewGlobalRef(instance);

                env->DeleteLocalRef(yelpOAuthTokenSecretStr);
                env->DeleteLocalRef(yelpOAuthTokenStr);
                env->DeleteLocalRef(yelpConsumerSecretStr);
                env->DeleteLocalRef(yelpConsumerKeyStr);
            }
            
            AndroidYelpSearchQuery::~AndroidYelpSearchQuery()
            {
            	ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                env->DeleteGlobalRef(m_yelpSearchQuery);
                env->DeleteGlobalRef(m_yelpSearchQueryClass);
            }
            
            void AndroidYelpSearchQuery::Dispatch()
            {
            	ASSERT_NATIVE_THREAD

                Eegeo_ASSERT(!m_dispatched, "Cannot dispatch AndroidYelpSearchQuery if query has already been dispatched.\n");
            	m_dispatched = true;

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring queryStr = env->NewStringUTF(m_searchQuery.Query().c_str());

                jmethodID dispatchMethod = env->GetMethodID(m_yelpSearchQueryClass, "dispatch", "(Ljava/lang/String;ZDDF)V");
                env->CallVoidMethod(
                		m_yelpSearchQuery,
                		dispatchMethod,
                		queryStr,
                		m_searchQuery.IsCategory(),
                		m_searchQuery.Location().GetLatitudeInDegrees(),
                		m_searchQuery.Location().GetLongitudeInDegrees(),
                		m_searchQuery.Radius());

                env->DeleteLocalRef(queryStr);
            }
            
            void AndroidYelpSearchQuery::Cancel()
            {
            	ASSERT_NATIVE_THREAD

                Eegeo_ASSERT(m_dispatched, "Cannot cancel AndroidYelpSearchQuery until query has been dispatched.\n");
                m_cancelled = true;

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID cancelMethod = env->GetMethodID(m_yelpSearchQueryClass, "cancel", "()V");
                env->CallVoidMethod(m_yelpSearchQuery, cancelMethod);
            }

            void AndroidYelpSearchQuery::HandleQueryCompleted(bool success, const std::string& queryResult)
            {
            	ASSERT_NATIVE_THREAD

            	if(!m_cancelled)
            	{
            		m_isSuccess = success;
            		m_responseString = queryResult;
                	m_completionCallback();
            	}

            	Eegeo_DELETE this;
            }
            
            bool AndroidYelpSearchQuery::IsSucceeded()
            {
            	ASSERT_NATIVE_THREAD

                return m_isSuccess;
            }
            
            const std::string& AndroidYelpSearchQuery::ResponseString()
            {
            	ASSERT_NATIVE_THREAD

                return m_responseString;
            }
            
            const SdkModel::SearchQuery& AndroidYelpSearchQuery::GetSearchQuery() const
            {
            	ASSERT_NATIVE_THREAD

                return m_searchQuery;
            }
        }
    }
}
