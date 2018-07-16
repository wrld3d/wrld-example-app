package com.eegeo.searchproviders;

import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;
import android.widget.ImageView;

import com.eegeo.tags.TagResources;
import com.wrld.widgets.search.R;
import com.wrld.widgets.search.model.SearchResult;
import com.wrld.widgets.search.view.ISearchResultViewFactory;
import com.wrld.widgets.search.view.ISearchResultViewHolder;

public class SearchResultViewFactory implements ISearchResultViewFactory
{
    private int      m_layoutId;
    private Activity m_activity;
    private boolean m_navigationEnabled;
    SearchResultNavigationHandler m_navigationHandler;
    private boolean m_showNavButton;

    public SearchResultViewFactory(int layoutId, Activity activity) {
        commonInit(layoutId, activity);
        m_navigationEnabled = false;
        m_showNavButton = false;
    }

    public SearchResultViewFactory(int layoutId, Activity activity, SearchResultNavigationHandler navigationHandler) {
        commonInit(layoutId, activity);
        m_navigationEnabled = true;
        m_showNavButton = true;
        m_navigationHandler = navigationHandler;
    }

    public void showNavButton(boolean enabled) {
        if(m_navigationEnabled) {
            m_showNavButton = enabled;
        }
    }

    private void commonInit(int layoutId, Activity activity){
        m_layoutId = layoutId;
        m_activity = activity;
    }

    @Override
    public View makeSearchResultView(LayoutInflater inflater, ViewGroup parent)
    {
        return inflater.inflate(m_layoutId, parent, false);
    }

    private class SearchResultViewHolder implements ISearchResultViewHolder
    {
        private TextView  m_title;
        private TextView  m_description;
        private ImageView m_icon;

        private View m_divider;
        private View m_separator;

        @Override
        public void initialise(View view)
        {
            m_title       = (TextView)  view.findViewById(R.id.search_result_title);
            m_description = (TextView)  view.findViewById(R.id.search_result_description);
            m_icon        = (ImageView) view.findViewById(R.id.search_result_icon);

            m_divider   = view.findViewById(R.id.search_result_divider);
            m_separator = view.findViewById(R.id.search_result_top_seperator);
        }

        @Override
        public void populate(SearchResult result,
                             String query,
                             boolean firstResultInSet,
                             boolean lastResultInSet)
        {
            String iconName     = (String)result.getProperty("Icon").getValue();
            int    iconResource = TagResources.getSearchResultIconForTag(m_activity, iconName);

            m_title      .setText(result.getTitle());
            m_description.setText((String)result.getProperty("Description").getValue());
            m_icon       .setImageResource(iconResource);

            m_divider  .setVisibility(lastResultInSet  ? View.GONE    : View.VISIBLE);
            m_separator.setVisibility(firstResultInSet ? View.VISIBLE : View.GONE);
        }
    }

    private class SearchResultNavigationViewHolder extends SearchResultViewHolder
    {
        private View m_navButton;
        private SearchResult m_currentResult;

        @Override
        public void initialise(View view)
        {
            super.initialise(view);

            m_navButton = view.findViewById(com.eegeo.mobileexampleapp.R.id.search_result_navigation_button);

            m_navButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    m_navigationHandler.navigateTo(m_currentResult);
                }
            });

        }

        @Override
        public void populate(SearchResult result,
                             String query,
                             boolean firstResultInSet,
                             boolean lastResultInSet)
        {
            m_currentResult = result;

            m_navButton.setVisibility(m_showNavButton ? View.VISIBLE : View.GONE);

            super.populate(result, query, firstResultInSet, lastResultInSet);
        }
    }

    @Override
    public ISearchResultViewHolder makeSearchResultViewHolder() {
        if(m_navigationEnabled) {
            return new SearchResultNavigationViewHolder();
        }
        else{
            return new SearchResultViewHolder();
        }
    }
}
