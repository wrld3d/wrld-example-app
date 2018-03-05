package com.eegeo.searchproviders;

import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.ImageView;

import com.eegeo.tags.TagResources;
import com.wrld.widgets.R;
import com.wrld.widgets.searchbox.model.SearchResult;
import com.wrld.widgets.searchbox.view.ISearchResultViewFactory;
import com.wrld.widgets.searchbox.view.ISearchResultViewHolder;

public class SearchResultViewFactory implements ISearchResultViewFactory
{
    private int      m_layoutId;
    private Activity m_activity;

    public SearchResultViewFactory(int layoutId, Activity activity)
    {
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
        private View m_shadow;

        @Override
        public void initialise(View view)
        {
            m_title       = (TextView)  view.findViewById(R.id.search_result_title);
            m_description = (TextView)  view.findViewById(R.id.search_result_description);
            m_icon        = (ImageView) view.findViewById(R.id.search_result_icon);

            m_divider   = view.findViewById(R.id.search_result_divider);
            m_separator = view.findViewById(R.id.search_result_top_seperator);
            m_shadow    = view.findViewById(R.id.search_result_shadow);
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
            m_shadow   .setVisibility(firstResultInSet ? View.VISIBLE : View.GONE);
        }
    }

    @Override
    public ISearchResultViewHolder makeSearchResultViewHolder() {
        return new SearchResultViewHolder();
    }
}
