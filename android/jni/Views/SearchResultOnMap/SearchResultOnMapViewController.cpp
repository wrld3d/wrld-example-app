// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapViewController.h"
#include "Types.h"
#include "ISearchResultPoiViewModel.h"
#include "IModalityModel.h"
#include "SearchResultModel.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidSearchResultSerializer.h"

namespace ExampleApp
{
namespace SearchResultOnMap
{
SearchResultOnMapViewController::SearchResultOnMapViewController(
    AndroidNativeState& nativeState,
    ExampleApp::SearchResultOnMap::ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
    ScreenControlViewModel::IScreenControlViewModel& searchResultPoiScreenControlViewModel,
    SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
    float pinDiameter
)
	: m_nativeState(nativeState)
	, m_searchResultOnMapInFocusViewModel(searchResultOnMapInFocusViewModel)
	, m_searchResultPoiScreenControlViewModel(searchResultPoiScreenControlViewModel)
	, m_searchResultPoiViewModel(searchResultPoiViewModel)
	, m_pSearchResultOnMapFocusOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultOnMapViewController>)(this, &SearchResultOnMapViewController::SearchResultOnMapFocusOpenedCallback))
	, m_pSearchResultOnMapFocusClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultOnMapViewController>)(this, &SearchResultOnMapViewController::SearchResultOnMapFocusClosedCallback))
	, m_pSearchResultOnMapFocusUpdatedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultOnMapViewController>)(this, &SearchResultOnMapViewController::SearchResultOnMapFocusUpdatedCallback))
	, m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SearchResultOnMapViewController, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &SearchResultOnMapViewController::OnScreenStateChangedCallback))
	, m_pinOffset(pinDiameter / 2.f)
{
	ASSERT_UI_THREAD

	m_searchResultOnMapInFocusViewModel.InsertOpenedCallback(*m_pSearchResultOnMapFocusOpenedCallback);
	m_searchResultOnMapInFocusViewModel.InsertClosedCallback(*m_pSearchResultOnMapFocusClosedCallback);
	m_searchResultOnMapInFocusViewModel.InsertUpdateCallback(*m_pSearchResultOnMapFocusUpdatedCallback);

	m_searchResultPoiScreenControlViewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jstring strClassName = env->NewStringUTF("com/eegeo/searchresultonmapview/SearchResultOnMapView");
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

SearchResultOnMapViewController::~SearchResultOnMapViewController()
{
	ASSERT_UI_THREAD

	m_searchResultPoiScreenControlViewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);

	m_searchResultOnMapInFocusViewModel.RemoveUpdateCallback(*m_pSearchResultOnMapFocusUpdatedCallback);
	m_searchResultOnMapInFocusViewModel.RemoveOpenedCallback(*m_pSearchResultOnMapFocusOpenedCallback);
	m_searchResultOnMapInFocusViewModel.RemoveClosedCallback(*m_pSearchResultOnMapFocusClosedCallback);

	Eegeo_DELETE m_pSearchResultOnMapFocusUpdatedCallback;
	Eegeo_DELETE m_pSearchResultOnMapFocusOpenedCallback;
	Eegeo_DELETE m_pSearchResultOnMapFocusClosedCallback;
	Eegeo_DELETE m_pOnScreenStateChangedCallback;

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;
	jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
	env->CallVoidMethod(m_uiView, removeHudMethod);
	env->DeleteGlobalRef(m_uiView);
	env->DeleteGlobalRef(m_uiViewClass);
}

void SearchResultOnMapViewController::HandleSearchResultOnMapClicked()
{
	ASSERT_UI_THREAD

	//if(m_modalityObserver.GetModality() == 0.f)
	{
		if(m_searchResultOnMapInFocusViewModel.IsOpen())
		{
			Search::SearchResultModel model = m_searchResultOnMapInFocusViewModel.GetSearchResultModel();
			m_searchResultPoiViewModel.Open(model);
		}
	}
}

void SearchResultOnMapViewController::SearchResultOnMapFocusOpenedCallback()
{
	ASSERT_UI_THREAD

	const Eegeo::v2& location = m_searchResultOnMapInFocusViewModel.ScreenLocation();
	float offsetY = location.y - m_pinOffset;

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	const Search::SearchResultModel& model = m_searchResultOnMapInFocusViewModel.GetSearchResultModel();
	jstring titleStr = env->NewStringUTF(model.GetTitle().c_str());
	jstring detailsStr = env->NewStringUTF(model.GetAddress().c_str());

	jmethodID showAtScreenLocation = env->GetMethodID(m_uiViewClass, "showAtScreenLocation", "(Ljava/lang/String;Ljava/lang/String;FFF)V");
	env->CallVoidMethod(m_uiView, showAtScreenLocation, titleStr, detailsStr, location.x, offsetY, m_searchResultPoiScreenControlViewModel.OnScreenState());

	env->DeleteLocalRef(titleStr);
	env->DeleteLocalRef(detailsStr);
}

void SearchResultOnMapViewController::SearchResultOnMapFocusClosedCallback()
{
	ASSERT_UI_THREAD

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jmethodID dismiss = env->GetMethodID(m_uiViewClass, "dismiss", "()V");
	env->CallVoidMethod(m_uiView, dismiss);
}

void SearchResultOnMapViewController::SearchResultOnMapFocusUpdatedCallback()
{
	ASSERT_UI_THREAD

	const Eegeo::v2& location = m_searchResultOnMapInFocusViewModel.ScreenLocation();
	float offsetY = location.y - m_pinOffset;

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	jmethodID updateScreenLocation = env->GetMethodID(m_uiViewClass, "updateScreenLocation", "(FF)V");
	env->CallVoidMethod(m_uiView, updateScreenLocation, location.x, offsetY);
}

void SearchResultOnMapViewController::OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
{
	ASSERT_UI_THREAD

	if(m_searchResultOnMapInFocusViewModel.IsOpen())
	{
		AndroidSafeNativeThreadAttachment attached(m_nativeState);
		JNIEnv* env = attached.envForThread;

		jmethodID updateScreenVisibility = env->GetMethodID(m_uiViewClass, "updateScreenVisibility", "(F)V");
		env->CallVoidMethod(m_uiView, updateScreenVisibility, onScreenState);
	}
}
}
}
