// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

import com.eegeo.ProjectSwallowApp.R;
import com.wrld.widgets.searchbox.model.SearchProvider;
import com.wrld.widgets.searchbox.model.SearchProviderResultsReadyCallback;
import com.wrld.widgets.searchbox.model.SearchResult;
import com.wrld.widgets.searchbox.model.SearchResultPropertyString;
import com.wrld.widgets.searchbox.model.DefaultSearchResult;
import com.wrld.widgets.searchbox.view.ISearchResultViewFactory;
import com.wrld.widgets.searchbox.view.DefaultSearchResultViewFactory;
import java.util.HashSet;
import org.json.JSONObject;
import android.util.Log;

public class MyTestSearchProvider implements SearchProvider
{
	private long										m_nativeCallerPointer;
	private DefaultSearchResultViewFactory				m_resultFactory;
	private HashSet<SearchProviderResultsReadyCallback>	m_callbacks;

	public class SearchResultInfo
	{
		public String name;
		public String description;
	}

	public MyTestSearchProvider(long nativeCallerPointer)
	{
		m_nativeCallerPointer = nativeCallerPointer;
		m_resultFactory       = new DefaultSearchResultViewFactory(R.layout.search_result);
		m_callbacks           = new HashSet<SearchProviderResultsReadyCallback>();
	}

	@Override
	public String getTitle()
	{
		return "My Test Search Provider";
	}

	@Override
	public void getSearchResults(String queryText, Object queryContext)
	{
		SearchProvidersJniMethods.search(m_nativeCallerPointer, queryText);
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
				wrappedResults[i] = WrapResult(results[i].name,
											   results[i].description);

		return wrappedResults;
	}

	private SearchResult WrapResult(String title, String description)
	{
		return new DefaultSearchResult(
			title,
			new SearchResultPropertyString("Description", description)
		);
	}
}