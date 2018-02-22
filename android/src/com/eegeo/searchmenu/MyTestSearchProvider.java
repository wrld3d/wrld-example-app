// Test implementation of the SearchProvider interface

package com.eegeo.searchmenu;

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

class MyTestSearchProvider implements SearchProvider
{
	private long										m_nativeCallerPointer;
	private DefaultSearchResultViewFactory				m_resultFactory;
	private HashSet<SearchProviderResultsReadyCallback>	m_callbacks;

	MyTestSearchProvider(long nativeCallerPointer)
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
		SearchMenuViewJniMethods.PerformSearchQuery(m_nativeCallerPointer, queryText);
	}

	public void onSearchCompleted(String[] searchResults)
	{
		executeCallbacks(WrapResults(searchResults), true);
	}

	@Override
	public void cancelSearch()
	{
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

	private SearchResult[] WrapResults(String[] results)
	{
		SearchResult[] wrappedResults = new SearchResult[results.length];

		for (int i = 0; i < results.length; i++)
		{
			try
			{
				JSONObject json = new JSONObject(results[i]);

				String title       = json.optString("name");
				String description = json.optString("details");

				wrappedResults[i] = WrapResult(title, description);
			}
			catch(Exception exception)
			{
				Log.e("Eegeo", "MyTestSearchProvider: Failed to read json data object: " + exception.getMessage());
			}
		}

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