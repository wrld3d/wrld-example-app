// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiViewController.h"
#include "Types.h"
#include "ISearchResultPoiViewModel.h"
#include "SearchResultModel.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
namespace SearchResultPoi
{
SearchResultPoiViewController::SearchResultPoiViewController(
    AndroidNativeState& nativeState,
    ISearchResultPoiViewModel& searchResultPoiViewModel
)
	: m_nativeState(nativeState)
	, m_searchResultPoiViewModel(searchResultPoiViewModel)
	, m_pSearchResultPoiOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultPoiViewController>)(this, &SearchResultPoiViewController::SearchResultPoiOpenedCallback))
	, m_pSearchResultPoiClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultPoiViewController>)(this, &SearchResultPoiViewController::SearchResultPoiClosedCallback))
{
	ASSERT_UI_THREAD

	m_searchResultPoiViewModel.InsertOpenedCallback(*m_pSearchResultPoiOpenedCallback);
	m_searchResultPoiViewModel.InsertClosedCallback(*m_pSearchResultPoiClosedCallback);

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jstring strClassName = env->NewStringUTF("com/eegeo/searchresultpoiview/SearchResultPoiView");
	jclass uiClass = m_nativeState.LoadClass(env, strClassName);
	env->DeleteLocalRef(strClassName);

	m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
	jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/mobileexampleapp/MainActivity;J)V");

	jobject instance = env->NewObject(
	                       m_uiViewClass,
	                       uiViewCtor,
	                       m_nativeState.activity,
	                       (jlong)(this)
	                   );

	m_uiView = env->NewGlobalRef(instance);
}

SearchResultPoiViewController::~SearchResultPoiViewController()
{
	ASSERT_UI_THREAD

	m_searchResultPoiViewModel.RemoveOpenedCallback(*m_pSearchResultPoiOpenedCallback);
	m_searchResultPoiViewModel.RemoveClosedCallback(*m_pSearchResultPoiClosedCallback);

	Eegeo_DELETE m_pSearchResultPoiOpenedCallback;
	Eegeo_DELETE m_pSearchResultPoiClosedCallback;

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;
	jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
	env->CallVoidMethod(m_uiView, removeHudMethod);
	env->DeleteGlobalRef(m_uiView);
	env->DeleteGlobalRef(m_uiViewClass);
}

void SearchResultPoiViewController::HandleCloseButtonPressed()
{
	ASSERT_UI_THREAD

	if(m_searchResultPoiViewModel.IsOpen())
	{
		m_searchResultPoiViewModel.Close();
	}
}

void SearchResultPoiViewController::SearchResultPoiOpenedCallback()
{
	ASSERT_UI_THREAD

	if(!m_searchResultPoiViewModel.TryAcquireReactorControl())
	{
		if(m_searchResultPoiViewModel.IsOpen())
		{
			m_searchResultPoiViewModel.Close();
		}
		return;
	}

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	const Search::SearchResultModel& model = m_searchResultPoiViewModel.GetSearchResultModel();

	jstring titleStr = env->NewStringUTF(model.GetTitle().c_str());
	jstring addressStr = env->NewStringUTF(model.GetAddress().c_str());
	jstring phoneStr = env->NewStringUTF(model.GetPhone().c_str());
	jstring urlStr = env->NewStringUTF(model.GetWebUrl().c_str());
	jstring categoryStr = env->NewStringUTF(model.GetCategory().c_str());

	jmethodID displayPoiInfo = env->GetMethodID(m_uiViewClass, "displayPoiInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	env->CallVoidMethod(m_uiView, displayPoiInfo, titleStr, addressStr, phoneStr, urlStr, categoryStr);

	env->DeleteLocalRef(urlStr);
	env->DeleteLocalRef(phoneStr);
	env->DeleteLocalRef(addressStr);
	env->DeleteLocalRef(titleStr);
	env->DeleteLocalRef(categoryStr);
}

void SearchResultPoiViewController::SearchResultPoiClosedCallback()
{
	ASSERT_UI_THREAD

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jmethodID dismissPoiInfo = env->GetMethodID(m_uiViewClass, "dismissPoiInfo", "()V");
	env->CallVoidMethod(m_uiView, dismissPoiInfo);
}
}
}
