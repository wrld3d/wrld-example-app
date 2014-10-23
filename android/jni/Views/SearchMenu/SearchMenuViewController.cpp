// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "SearchMenuViewController.h"
#include "Types.h"
#include "MenuItemModel.h"
#include "IMenuViewModel.h"
#include "IMenuModel.h"
#include "ICallback.h"
#include "ISearchQueryPerformer.h"
#include "ISearchService.h"
#include "ICategorySearchRepository.h"
#include "SearchResultModel.h"
#include "ISearchResultMenuViewModel.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
    	SearchMenuViewController::SearchMenuViewController(
	    		const std::string& viewClassName,
				AndroidNativeState& nativeState,
				ExampleApp::Menu::IMenuModel& menuModel,
				ExampleApp::Menu::IMenuViewModel& menuViewModel,
        		Search::ISearchService& searchService,
                Search::ISearchQueryPerformer& queryPerformer,
	            CategorySearch::ICategorySearchRepository& categorySearchRepository,
	            SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel
		)
		: Menu::MenuViewController(viewClassName, nativeState, menuModel, menuViewModel)
		, m_searchService(searchService)
    	, m_pSearchResultQueryIssuedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchMenuViewController, const Search::SearchQuery&>))(this, &SearchMenuViewController::HandleSearchQueryIssued))
    	, m_pSearchResultReceivedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SearchMenuViewController, const Search::SearchQuery&, const std::vector<Search::SearchResultModel> &>))(this, &SearchMenuViewController::HandleSearchResultReceived))
    	, m_queryPerformer(queryPerformer)
    	, m_categorySearchRepository(categorySearchRepository)
    	, m_searchResultMenuViewModel(searchResultMenuViewModel)
    	{
    		m_searchService.InsertOnReceivedQueryResultsCallback(*m_pSearchResultReceivedCallback);
    		m_searchService.InsertOnPerformedQueryCallback(*m_pSearchResultQueryIssuedCallback);
		}

    	SearchMenuViewController::~SearchMenuViewController()
		{
    		m_searchService.RemoveOnReceivedQueryResultsCallback(*m_pSearchResultReceivedCallback);
    		m_searchService.RemoveOnPerformedQueryCallback(*m_pSearchResultQueryIssuedCallback);

    		Eegeo_DELETE m_pSearchResultReceivedCallback;
    		Eegeo_DELETE m_pSearchResultQueryIssuedCallback;
		}

    	bool SearchMenuViewController::TryBeginDrag()
    	{
    	    if(m_searchResultMenuViewModel.CanInteract())
    	    {
    	    	return MenuViewController::TryBeginDrag();
    	    }

    	    return false;
    	}

    	void SearchMenuViewController::HandleViewClicked()
		{
    	    if(m_searchResultMenuViewModel.CanInteract())
    	    {
    	    	MenuViewController::HandleViewClicked();
    	    }
		}

    	void SearchMenuViewController::HandleClosed()
    	{
    		m_queryPerformer.RemoveSearchQueryResults();
    	    m_menuViewModel.RemoveFromScreen();
    	}

    	void SearchMenuViewController::RefreshViewHeader(const Search::SearchQuery& query, bool queryPending, int numResult)
    	{
    		AndroidSafeNativeThreadAttachment attached(m_nativeState);
    		JNIEnv* env = attached.envForThread;

    		jmethodID updateHeaderMethod = env->GetMethodID(m_uiViewClass, "updateHeader", "(Ljava/lang/String;ZI)V");
    		std::string headerString = CategorySearch::GetPresentationStringForQuery(m_categorySearchRepository, query);
    		jstring queryString = env->NewStringUTF(headerString.c_str());

    		env->CallVoidMethod(m_uiView, updateHeaderMethod, queryString, queryPending, numResult);
    		env->DeleteLocalRef(queryString);
    	}

    	void SearchMenuViewController::HandleSearchQueryIssued(const Search::SearchQuery& query)
    	{
    		RefreshViewHeader(query, true, 0);
    	}

        void SearchMenuViewController::HandleSearchResultReceived(
			const Search::SearchQuery& query,
			const std::vector<Search::SearchResultModel>& results)
		{
    		RefreshViewHeader(query, false, results.size());
		}
    }
}
