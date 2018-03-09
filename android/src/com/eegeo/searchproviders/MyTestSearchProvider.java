// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

import android.app.Activity;

import com.wrld.widgets.R;
import com.wrld.widgets.searchbox.model.SearchProvider;
import com.wrld.widgets.searchbox.model.SearchProviderResultsReadyCallback;
import com.wrld.widgets.searchbox.model.SearchResult;
import com.wrld.widgets.searchbox.model.SearchResultPropertyString;
import com.wrld.widgets.searchbox.view.ISearchResultViewFactory;

import com.eegeo.searchmenu.SearchWidgetResult;
import com.eegeo.searchproviders.QueryContext;

import java.util.HashSet;

public class MyTestSearchProvider implements SearchProvider
{
	private long										m_nativeCallerPointer;
	private SearchResultViewFactory						m_resultFactory;
	private HashSet<SearchProviderResultsReadyCallback>	m_callbacks;
	private String										m_lastQueryText;

	public class SearchResultInfo
	{
		public String name;
		public String description;
		public String iconName;
	}

	public MyTestSearchProvider(long nativeCallerPointer, Activity activity)
	{
		m_nativeCallerPointer = nativeCallerPointer;
		m_resultFactory       = new SearchResultViewFactory(R.layout.search_result, activity);
		m_callbacks           = new HashSet<SearchProviderResultsReadyCallback>();
		m_lastQueryText       = "";
	}

	@Override
	public String getTitle()
	{
		return m_lastQueryText;
	}

	@Override
	public void getSearchResults(String queryText, Object queryContext)
	{
		m_lastQueryText = queryText;

		if (queryContext == null)
		{
			SearchProvidersJniMethods.search(m_nativeCallerPointer, queryText);
			return;
		}

		QueryContext context = (QueryContext)queryContext;

		SearchProvidersJniMethods.searchRefresh(m_nativeCallerPointer,
											    queryText,
												context.IsTag(),
												context.TryInterior(),
												context.ShouldZoomToBuildingsView(),
												context.Latitude(),
												context.Longitude(),
												context.Altitude(),
												context.Radius());
	}

	public void onSearchCompleted(SearchResultInfo[] searchResults)
	{
		executeCallbacks(WrapResults(searchResults), true);
	}

	@Override
	public void cancelSearch()
	{
		// TO DO - cancel ongoing search within the native thread

		SearchProvidersJniMethods.cancel(m_nativeCallerPointer);

		executeCallbacks(new SearchResult[0], false);
	}

	@Override
	public ISearchResultViewFactory getResultViewFactory()
	{
		return m_resultFactory;
	}

	@Override
	public void addSearchCompletedCallback(SearchProviderResultsReadyCallback searchProviderResultsReadyCallback)
	{
		m_callbacks.add(searchProviderResultsReadyCallback);
	}

	@Override
	public void removeSearchCompletedCallback(SearchProviderResultsReadyCallback searchProviderResultsReadyCallback)
	{
		m_callbacks.remove(searchProviderResultsReadyCallback);
	}

	private void executeCallbacks(SearchResult[] results, boolean success)
	{
		for (SearchProviderResultsReadyCallback callback : m_callbacks)
			callback.onQueryCompleted(results, success);
	}

	private SearchResult[] WrapResults(SearchResultInfo[] results)
	{
		SearchResult[] wrappedResults = new SearchResult[results.length];

		for (int i = 0; i < results.length; i++)
			wrappedResults[i] = WrapResult(i,
										   results[i].name,
										   results[i].description,
										   results[i].iconName);

		return wrappedResults;
	}

	private SearchResult WrapResult(int index, String title, String description, String iconName)
	{
		return new SearchWidgetResult(index, title, description, iconName);
	}
}