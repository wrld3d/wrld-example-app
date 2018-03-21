// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchmenu;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.ProjectSwallowApp.R;
import com.eegeo.searchproviders.MyTestSearchProvider;
import com.eegeo.searchproviders.QueryContext;

import android.app.SearchManager;
import android.app.SearchableInfo;
import android.content.Context;
import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.tags.TagResources;
import com.eegeo.ui.IAnimatedView;
import com.eegeo.ui.IViewAnimator;
import com.eegeo.ui.ViewAnimator;
import com.wrld.widgets.searchbox.WrldSearchWidget;
import com.wrld.widgets.searchbox.model.MenuChild;
import com.wrld.widgets.searchbox.model.MenuGroup;
import com.wrld.widgets.searchbox.model.MenuOption;
import com.wrld.widgets.searchbox.model.OnMenuOptionSelectedCallback;
import com.wrld.widgets.searchbox.model.SearchQuery;
import com.wrld.widgets.searchbox.model.SearchProviderQueryResult;
import com.wrld.widgets.searchbox.model.SearchQueryModelListener;
import com.wrld.widgets.searchbox.model.SearchResult;
import com.wrld.widgets.searchbox.model.SearchResultsListener;
import com.wrld.widgets.searchbox.view.MenuViewListener;
import com.wrld.widgets.searchbox.view.SearchResultsViewListener;


import org.json.JSONObject;

import java.util.Arrays;
import java.util.List;

public class SearchWidgetView implements OnMenuOptionSelectedCallback,
                                        SearchResultsListener,
                                        IAnimatedView,
                                        SearchResultsViewListener,
                                        View.OnFocusChangeListener,
                                        MenuViewListener,
                                        SearchQueryModelListener
{
    protected MainActivity m_activity;
    protected MyTestSearchProvider m_searchProvider;
    protected long m_nativeCallerPointer;
    protected View m_view;
    private IViewAnimator m_viewAnimator;
    protected WrldSearchWidget m_searchWidget;

    private boolean m_searchResultsAreVisible = false;
    private boolean m_menuIsOpen = false;
    private boolean m_searchTextboxIsInFocus = false;
    private boolean m_hasSearchResults = false;
    private boolean m_searchInProgress = false;

    private final long m_stateChangeAnimationTimeMilliseconds = 200;

    public SearchWidgetView(MainActivity activity, long nativeCallerPointer,
                            MyTestSearchProvider searchProvider) {
        m_activity = activity;
        m_searchProvider = searchProvider;
        m_nativeCallerPointer = nativeCallerPointer;

        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_widget_view_layout, uiRoot, false);
        uiRoot.addView(m_view);

        m_viewAnimator = new ViewAnimator(this, m_view);
        m_viewAnimator.registerLayoutChangeListener();

        m_searchWidget = (WrldSearchWidget) m_activity.getFragmentManager().findFragmentById(R.id.search_widget);
        m_searchWidget.addSearchProvider(m_searchProvider);
        m_searchWidget.addSuggestionProvider(m_searchProvider);

        m_searchWidget.getSearchResultsModel().addResultListener(this);

        m_searchWidget.getMenuViewObserver().addMenuListener(this);
        m_searchWidget.getSearchViewFocusObserver().addListener(this);
        m_searchWidget.getSearchResultsViewObserver().addListener(this);
        m_searchWidget.getSearchQueryModel().addListener(this);


        SearchManager searchManager = (SearchManager) m_activity.getSystemService(Context.SEARCH_SERVICE);
        SearchableInfo searchableInfo = searchManager.getSearchableInfo(m_activity.getComponentName());
        m_searchWidget.setSearchableInfo(searchableInfo);

    }

    public void onSearchResultsRecieved(SearchQuery searchQuery, List<SearchProviderQueryResult> list) {
        if (!list.isEmpty())
        {
            setHasSearchResults(true);
        }
    }

    public void onSearchResultsCleared() {
        setHasSearchResults(false);

        SearchWidgetViewJniMethods.OnSearchResultsCleared(m_nativeCallerPointer);
    }

    public void onSearchResultsSelected(SearchResult searchResult) {
        SearchWidgetResult widgetResult = (SearchWidgetResult) searchResult;

        SearchWidgetViewJniMethods.OnSearchResultSelected(
                m_nativeCallerPointer,
                widgetResult.getIndex());
    }

    public void onSearchPerformed(String queryText,
                                  boolean clearPreviousResults,
                                  boolean isTag, String tagText,
                                  boolean tryInterior, boolean shouldZoomToBuildingsView,
                                  boolean usesLocation,
                                  double latitude, double longitude, double altitude,
                                  boolean usesRadius,
                                  float radius)
    {
        QueryContext context =
            usesLocation ?
                new QueryContext(clearPreviousResults,
                                 isTag, tagText, tryInterior, shouldZoomToBuildingsView,
                                 latitude, longitude, altitude, radius) :
            usesRadius ?
                new QueryContext(clearPreviousResults,
                                 isTag, tagText, tryInterior, shouldZoomToBuildingsView,
                                 radius) :
                new QueryContext(clearPreviousResults,
                        isTag, tagText, tryInterior, shouldZoomToBuildingsView);

        m_searchWidget.doSearch(queryText, context);
    }

    public boolean onMenuOptionSelected(final String text, final Object context) {
        MenuIndexPath indexPath = (MenuIndexPath) context;

        //TODO replace this line with clear when the api point is exposed
        m_searchWidget.showSearchResults();
        //m_searchWidget.getSearchResultsModel().clear();

        SearchWidgetViewJniMethods.SelectedItem(m_nativeCallerPointer, text, indexPath.m_section, indexPath.m_item);
        return true;
    }

    public void populateData(
            final long nativeCallerPointer,
            final String[] optionNames,
            final int[] optionSizes,
            final String[] childJsons) {

        m_searchWidget.clearMenu();

        MenuGroup menuGroup = new MenuGroup("Show me the closest...");

        List<String> options = Arrays.asList(optionNames);
        int childIndex = 1;

        int[] groupSizes = {5, 2, 1, 2};
        int numberOfGroups = 4;
        int groupIndex = 0;
        int maxOptionIndexForGroup = groupSizes[0];

        for (int optionIndex = 0; optionIndex < options.size(); optionIndex++) {
            if (optionIndex == maxOptionIndexForGroup && groupIndex < numberOfGroups - 1) {
                groupIndex++;
                maxOptionIndexForGroup += groupSizes[groupIndex];
                m_searchWidget.addMenuGroup(menuGroup);
                menuGroup = new MenuGroup();
            }

            int sizeWithoutHeader = optionSizes[optionIndex] - 1;

            String optionName = getFromJson(optionNames[optionIndex], "name");
            MenuIndexPath optionIndexPath = new MenuIndexPath(optionIndex, 0);
            MenuOption menuOption = new MenuOption(optionName, optionIndexPath, this);

            menuGroup.addOption(menuOption);

            for (int i = 1; i < sizeWithoutHeader; ++i) {
                MenuIndexPath indexPath = new MenuIndexPath(optionIndex, i);
                String childJson = childJsons[childIndex];
                String name = getFromJson(childJson, "name");
                String iconName = getFromJson(childJson, "icon");
                int iconNumber = TagResources.getIconForResourceName(m_activity, iconName);
                MenuChild child = new MenuChild(name, iconNumber, indexPath, this);
                menuOption.addChild(child);
                childIndex++;
            }

            childIndex++;
        }

        m_searchWidget.addMenuGroup(menuGroup);

    }

    private String getFromJson(String jsonString, String tag) {
        try {
            JSONObject json = new JSONObject(jsonString);
            String name = json.getString(tag);
            return name;
        } catch (Exception e) {
            Log.e("SearchWidgetView", String.format("Unable to parse %s from group JSON: %s", tag, e.toString()));
            return null;
        }
    }

    public void ViewLayoutChanged() {
        final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);

        final float viewHeight = m_view.getHeight();

        float y = m_view.getY();

        float inactiveY = -viewHeight;

        m_viewAnimator.setActivePos(y);
        m_viewAnimator.setInactivePos(inactiveY);

        m_view.setY(inactiveY);
    }

    public void animateToClosedOnScreen() {
        m_viewAnimator.animateToActive(m_stateChangeAnimationTimeMilliseconds);
    }

    public void animateToOpenOnScreen() {
        m_viewAnimator.animateToActive(m_stateChangeAnimationTimeMilliseconds);
    }

    public void animateOffScreen() {
        m_searchWidget.hideSearchResults();
        m_searchWidget.closeMenu();
        m_viewAnimator.animateToInactive(m_stateChangeAnimationTimeMilliseconds);
    }

    public void animateToIntermediateOnScreenState(final float onScreenState) {
        m_searchWidget.hideSearchResults();
        m_searchWidget.closeMenu();
        m_viewAnimator.animateToOnScreenState(onScreenState);
    }

    public void animateToIntermediateOpenState(final float openState) {
        m_viewAnimator.animateToOnScreenState(openState);
    }

    private void pushControlsOfScreenIfNeeded(){

        boolean hasVisibleSearchResults = m_searchResultsAreVisible && (m_hasSearchResults || m_searchInProgress);

        boolean shouldTakeFocus = m_searchTextboxIsInFocus ||hasVisibleSearchResults || m_menuIsOpen;

        if( shouldTakeFocus )
        {
            SearchWidgetViewJniMethods.ViewPushesControlsOffscreen(m_nativeCallerPointer);
        }
        else
        {
            SearchWidgetViewJniMethods.ViewAllowsControlsOnscreen(m_nativeCallerPointer);
        }
    }

    private void setHasSearchResults(boolean hasResults){
        m_hasSearchResults = hasResults;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onFocusChange(View view, boolean inFocus) {
        m_searchTextboxIsInFocus = inFocus;
        pushControlsOfScreenIfNeeded();
    }

    //SearchResultViewListener:

    @Override
    public void onSearchResultsShown() {
        m_searchResultsAreVisible = true;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onSearchResultsHidden() {
        m_searchResultsAreVisible = false;
        pushControlsOfScreenIfNeeded();
    }

    //MenuViewListener:

    @Override
    public void onClosed() {
        m_menuIsOpen = false;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onOpened() {
        m_menuIsOpen = true;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onChildSelected(MenuChild menuChild) {

    }

    @Override
    public void onOptionExpanded(MenuOption menuOption) {

    }

    @Override
    public void onOptionCollapsed(MenuOption menuOption) {

    }

    @Override
    public void onOptionSelected(MenuOption menuOption) {

    }

    //SearchQueryModelListener:
    @Override
    public void onSearchQueryStarted(SearchQuery query)
    {
        m_searchInProgress = true;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onSearchQueryCompleted(SearchQuery query, List<SearchProviderQueryResult> results)
    {

        m_searchInProgress = false;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onSearchQueryCancelled(SearchQuery query)
    {
        m_searchInProgress = false;
        pushControlsOfScreenIfNeeded();
    }
}