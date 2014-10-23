// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "SecondaryMenuViewController.h"
#include "Types.h"
#include "MenuItemModel.h"
#include "IMenuViewModel.h"
#include "IMenuModel.h"
#include "ICallback.h"
#include "ISearchService.h"
#include "SearchQuery.h"
#include "ISearchQueryPerformer.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
    	SecondaryMenuViewController::SecondaryMenuViewController(
	    		const std::string& viewClassName,
				AndroidNativeState& nativeState,
				ExampleApp::Menu::IMenuModel& menuModel,
				ExampleApp::Menu::IMenuViewModel& menuViewModel,
				Search::ISearchService& searchService,
				Search::ISearchQueryPerformer& searchQueryPerformer
		)
		: Menu::MenuViewController(viewClassName, nativeState, menuModel, menuViewModel)
		, m_searchService(searchService)
    	, m_searchQueryPerformer(searchQueryPerformer)
        , m_pPerformedQueryCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SecondaryMenuViewController, const Search::SearchQuery&>))(this, &SecondaryMenuViewController::PerformedQueryCallback))
        , m_pReceivedQueryResponseCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SecondaryMenuViewController, const Search::SearchQuery&, const std::vector<Search::SearchResultModel>&>))(this, &SecondaryMenuViewController::ReceivedQueryResponseCallback))
        , m_pMenuOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SecondaryMenuViewController, OpenableControlViewModel::IOpenableControlViewModel&, float>))(this, &SecondaryMenuViewController::HandleOpenStateChanged))
		{
            m_menuViewModel.InsertOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
            m_searchService.InsertOnPerformedQueryCallback(*m_pPerformedQueryCallback);
            m_searchService.InsertOnReceivedQueryResultsCallback(*m_pReceivedQueryResponseCallback);
		}

    	SecondaryMenuViewController::~SecondaryMenuViewController()
		{
            m_searchService.RemoveOnPerformedQueryCallback(*m_pPerformedQueryCallback);
            m_searchService.RemoveOnReceivedQueryResultsCallback(*m_pReceivedQueryResponseCallback);
            m_menuViewModel.RemoveOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);

            Eegeo_DELETE m_pPerformedQueryCallback;
            Eegeo_DELETE m_pReceivedQueryResponseCallback;
            Eegeo_DELETE m_pMenuOpenStateChangedCallback;
		}

    	void SecondaryMenuViewController::HandleSearch(const std::string& searchQuery)
    	{
    		if(!searchQuery.empty())
    		{
    			m_searchQueryPerformer.PerformSearchQuery(searchQuery, false);
    			m_menuViewModel.Close();
    		}
    	}

        void SecondaryMenuViewController::HandleOpenStateChanged(
			OpenableControlViewModel::IOpenableControlViewModel& viewModel,
			float& openState)
        {
            if(openState != 1.f)
            {
    			AndroidSafeNativeThreadAttachment attached(m_nativeState);
    			JNIEnv* env = attached.envForThread;
    			jmethodID removeSeachKeyboard = env->GetMethodID(m_uiViewClass, "removeSeachKeyboard", "()V");
    			env->CallVoidMethod(m_uiView, removeSeachKeyboard);
            }
        }

        void SecondaryMenuViewController::PerformedQueryCallback(const Search::SearchQuery& query)
        {
			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID disableEditText = env->GetMethodID(m_uiViewClass, "disableEditText", "()V");
			env->CallVoidMethod(m_uiView, disableEditText);
        }

        void SecondaryMenuViewController::ReceivedQueryResponseCallback(const Search::SearchQuery& query, const std::vector<Search::SearchResultModel>& results)
        {
			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID enableEditText = env->GetMethodID(m_uiViewClass, "enableEditText", "()V");
			env->CallVoidMethod(m_uiView, enableEditText);
        }
    }
}
