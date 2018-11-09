// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

import android.app.Activity;
import android.graphics.Typeface;
import android.support.v4.content.res.ResourcesCompat;

import com.eegeo.mobileexampleapp.R;
import com.wrld.widgets.search.model.SearchProvider;
import com.wrld.widgets.search.model.SearchProviderResultsReadyCallback;
import com.wrld.widgets.search.model.SearchResult;
import com.wrld.widgets.search.model.SuggestionProvider;
import com.wrld.widgets.search.view.DefaultSuggestionViewFactory;
import com.wrld.widgets.search.view.ISearchResultViewFactory;

import com.eegeo.searchmenu.SearchWidgetResult;
import com.wrld.widgets.search.view.TextHighlighter;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class MyTestSearchProvider implements SearchProvider, SuggestionProvider, SearchResultNavigationHandler
{
	private long										m_nativeCallerPointer;
	private SearchResultViewFactory						m_resultFactory;
	private ISearchResultViewFactory					m_suggestionResultFactory;
	private HashSet<SearchProviderResultsReadyCallback>	m_callbacks;
	private HashSet<SearchProviderResultsReadyCallback>	m_suggestion_callbacks;
	private SearchResultNavigationHandler 				m_navRequestHandler;

	private List<SearchResultNavigationHandler> m_navRequestHandlers;

	public class SearchResultInfo
	{
		public String name;
		public String description;
		public String iconName;
	}

	public MyTestSearchProvider(long nativeCallerPointer, Activity activity, boolean navigationEnabled)
	{
		m_nativeCallerPointer = nativeCallerPointer;

		if(navigationEnabled) {
			m_resultFactory = new SearchResultViewFactory(R.layout.search_result_navigation, activity, this);
		}
		else {
			m_resultFactory = new SearchResultViewFactory(com.wrld.widgets.search.R.layout.search_result, activity);
		}

		int textHighlightColor = ResourcesCompat.getColor(activity.getResources(), R.color.search_widget_text_primary, null);
		Typeface searchViewTextTypeface = ResourcesCompat.getFont(activity, R.font.open_sans_semibold);
		m_suggestionResultFactory = new DefaultSuggestionViewFactory(R.layout.search_suggestion, new TextHighlighter(textHighlightColor, searchViewTextTypeface));
		m_callbacks           = new HashSet<>();
		m_suggestion_callbacks = new HashSet<>();

		m_navRequestHandlers = new ArrayList<>();
	}

	public void showNavButtons(boolean enabled) {
		m_resultFactory.showNavButton(enabled);
	}

	@Override
	public String getTitle()
	{
		return "search";
	}

	@Override
	public void getSearchResults(String queryText, Object queryContext)
	{
		if (queryContext == null)
		{
			SearchProvidersJniMethods.search(m_nativeCallerPointer, queryText);
			return;
		}

		QueryContext context = (QueryContext)queryContext;

		SearchProvidersJniMethods.searchWithContext(m_nativeCallerPointer,
													queryText,
													context.ClearPreviousResults(),
													context.IsTag(),
													context.TagText(),
													context.TryInterior(),
													context.UsesLocation(),
													context.Latitude(),
													context.Longitude(),
													context.Altitude(),
													context.UsesRadius(),
													context.Radius());
	}

	public void onSearchCompleted(SearchResultInfo[] searchResults, boolean success)
	{
		executeCallbacks(WrapResults(searchResults), success);
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

	public void onSuggestionCompleted(SearchResultInfo[] searchResults, boolean success){
		executeSuggestionCallbacks(WrapResults(searchResults), success);
	}

	private void executeSuggestionCallbacks(SearchResult[] results, boolean success)
	{
		for (SearchProviderResultsReadyCallback callback : m_suggestion_callbacks) {
			callback.onQueryCompleted(results, success);
		}
	}

	public String getSuggestionTitleFormatting(){
		return "WRLD places \'%s\'";
	}

	public void getSuggestions(String queryText, Object queryContext){
		SearchProvidersJniMethods.autocompleteSuggestions(m_nativeCallerPointer, queryText);
	}

	public void cancelSuggestions(){
		SearchProvidersJniMethods.cancelSuggestions(m_nativeCallerPointer);
		executeSuggestionCallbacks(new SearchResult[0],false);
	}

	public void addSuggestionsReceivedCallback(SearchProviderResultsReadyCallback resultReadyCallback){
		m_suggestion_callbacks.add(resultReadyCallback);
	}

	public void removeSuggestionsReceivedCallback(SearchProviderResultsReadyCallback resultReadyCallback){
		m_suggestion_callbacks.remove(resultReadyCallback);
	}

	@Override
	public void navigateTo(SearchResult targetResult) {
		for(SearchResultNavigationHandler handler : m_navRequestHandlers) {
			handler.navigateTo(targetResult);
		}
	}

	public void addNavigationRequestCallback(SearchResultNavigationHandler navRequestHandler){
		m_navRequestHandlers.add(navRequestHandler);
	}

	public void removeNavigationRequestCallback(SearchResultNavigationHandler navRequestHandler){
		m_navRequestHandlers.remove(navRequestHandler);
	}

	public ISearchResultViewFactory getSuggestionViewFactory(){
		return m_suggestionResultFactory;
	}
}