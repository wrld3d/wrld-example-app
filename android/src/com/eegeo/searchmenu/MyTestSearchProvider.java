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
import java.util.HashMap;
import java.util.HashSet;

class MyTestSearchProvider implements SearchProvider
{
	private HashMap<String, SearchResult[]>				m_map;
	private DefaultSearchResultViewFactory				m_resultFactory;
	private HashSet<SearchProviderResultsReadyCallback>	m_callbacks;

	MyTestSearchProvider()
	{
		m_map = new HashMap<String, SearchResult[]>();

		m_map.put("hotels", new SearchResult[] {
			WrapResult("The Mighty Surveyor",		"A fine rest for the tired soul."),
			WrapResult("The Impoverished Wanderer","Budget accommodation for the connoisseur."),
			WrapResult("The Sultry Joint",			"We turn a blind eye to anything."),
			WrapResult("The Captain's Eye",		"Where the captain lost it.")
		});

		m_map.put("restaurants", new SearchResult[] {
			WrapResult("La Belle Fourchette",		"Design food with a twist."),
			WrapResult("Habemus Papa",				"Meals per metric ton."),
			WrapResult("Il Lamento della Mamma",	"Family restaurant for the homesick."),
			WrapResult("The Cloaca",				"Abandon all hope, ye who enter here.")
		});

		m_resultFactory = new DefaultSearchResultViewFactory(R.layout.search_result);
		m_callbacks     = new HashSet<SearchProviderResultsReadyCallback>();
	}

	public String getTitle()
	{
		return "My Test Search Provider";
	}

	public void getSearchResults(String queryText, Object queryContext)
	{
		SearchResult[] results = m_map.get(queryText);

		executeCallbacks(results, true);
	}

	public void cancelSearch()
	{
		executeCallbacks(new SearchResult[0], false);
	}

	public ISearchResultViewFactory getResultViewFactory()
	{
		return m_resultFactory;
	}

	public void addSearchCompletedCallback(SearchProviderResultsReadyCallback searchProviderResultsReadyCallback)
	{
		m_callbacks.add(searchProviderResultsReadyCallback);
	}

	public void removeSearchCompletedCallback(SearchProviderResultsReadyCallback searchProviderResultsReadyCallback)
	{
		m_callbacks.remove(searchProviderResultsReadyCallback);
	}

	private void executeCallbacks(SearchResult[] results, boolean success)
	{
		for (SearchProviderResultsReadyCallback callback : m_callbacks)
			callback.onQueryCompleted(results, success);
	}

	private SearchResult WrapResult(String title, String description)
	{
		return new DefaultSearchResult(
			title,
			new SearchResultPropertyString("Description", description)
		);
	}
}