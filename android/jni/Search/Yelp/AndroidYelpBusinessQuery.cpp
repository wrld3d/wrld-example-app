// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidYelpBusinessQuery.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "YelpSearchJsonParser.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
        	AndroidYelpBusinessQuery::AndroidYelpBusinessQuery(
            		AndroidNativeState& nativeState,
        			const std::string& yelpConsumerKey,
        			const std::string& yelpConsumerSecret,
        			const std::string& yelpOAuthToken,
        			const std::string& yelpOAuthTokenSecret,
                    IYelpCategoryMapper& yelpCategoryMapper,
                    const std::string& locationIdentifier,
                    Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback)
            : m_nativeState(nativeState)
        	, m_yelpCategoryMapper(yelpCategoryMapper)
            , m_locationIdentifier(locationIdentifier)
            , m_callback(callback)
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

        	AndroidYelpBusinessQuery::~AndroidYelpBusinessQuery()
            {
            	ASSERT_NATIVE_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                env->DeleteGlobalRef(m_yelpSearchQuery);
                env->DeleteGlobalRef(m_yelpSearchQueryClass);
            }

            void AndroidYelpBusinessQuery::Dispatch()
            {
            	ASSERT_NATIVE_THREAD

                Eegeo_ASSERT(!m_dispatched, "Cannot dispatch AndroidYelpBusinessQuery if query has already been dispatched.\n");
            	m_dispatched = true;

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring queryStr = env->NewStringUTF(m_locationIdentifier.c_str());

                jmethodID dispatchBusinessQueryMethod = env->GetMethodID(m_yelpSearchQueryClass, "dispatchBusinessQuery", "(Ljava/lang/String;)V");

                env->CallVoidMethod(m_yelpSearchQuery, dispatchBusinessQueryMethod, queryStr);

                env->DeleteLocalRef(queryStr);
            }

            void AndroidYelpBusinessQuery::Cancel()
            {
            	ASSERT_NATIVE_THREAD

                Eegeo_ASSERT(m_dispatched, "Cannot cancel AndroidYelpSearchQuery until query has been dispatched.\n");
                m_cancelled = true;

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID cancelMethod = env->GetMethodID(m_yelpSearchQueryClass, "cancel", "()V");
                env->CallVoidMethod(m_yelpSearchQuery, cancelMethod);
            }

            void AndroidYelpBusinessQuery::HandleQueryCompleted(bool success, const std::string& queryResult)
            {
            	ASSERT_NATIVE_THREAD

        		m_isSuccess = success;
            	m_responseString = queryResult;

                if(!m_cancelled)
                {
                    SdkModel::SearchResultModel result;
                    if(TryParseYelpBusinessSearchResult(m_responseString, m_yelpCategoryMapper, result))
                    {
                        m_callback(SdkModel::IdentitySearchCallbackData::CreateSucceeded(m_locationIdentifier, result));
                    }
                    else
                    {
                        m_callback(SdkModel::IdentitySearchCallbackData::CreateFailed(m_locationIdentifier));
                    }
                }
                else
                {
                    m_callback(SdkModel::IdentitySearchCallbackData::CreateFailed(m_locationIdentifier));
                }

            	Eegeo_DELETE this;
            }

            bool AndroidYelpBusinessQuery::IsSucceeded()
            {
            	ASSERT_NATIVE_THREAD

                return m_isSuccess;
            }

            const std::string& AndroidYelpBusinessQuery::ResponseString()
            {
            	ASSERT_NATIVE_THREAD

                return m_responseString;
            }
        }
    }
}
