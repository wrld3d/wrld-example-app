// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.eegeo.categories.CategoryResources;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class GeoNamesSearchResultPoiView 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;
    private ToggleButton m_togglePinnedButton = null;
    private TextView m_titleView = null;
    private TextView m_countryView = null;
    private TextView m_countryHeader = null;
    private ImageView m_categoryIcon = null;

    public GeoNamesSearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_geonames_layout, m_uiRoot, false);
       
        m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
        m_togglePinnedButton = (ToggleButton)m_view.findViewById(R.id.search_result_poi_view_toggle_pinned_button);
        m_titleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_title);
        m_countryView = (TextView)m_view.findViewById(R.id.search_result_poi_view_country);
        m_countryHeader = (TextView)m_view.findViewById(R.id.search_result_poi_view_country_header);
        m_categoryIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_category_icon);

        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
        
        m_closeButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
				handleCloseClicked();
			}
        });

        m_togglePinnedButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
				handleTogglePinnedClicked();
			}
        });
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void displayPoiInfo(
    		final String title,
    		final String address,
    		final String phone, 
    		final String url,
    		final String category,
    		final String[] humanReadableCategories,
    		final String imageUrl,
    		final String ratingImageUrl,
    		final String vendor,
    		final String[] reviewSnippet,
    		final boolean isPinned)
    {
        m_titleView.setText(title);

        if(!address.equals(""))
        {
            m_countryHeader.setVisibility(View.VISIBLE);
            m_countryView.setVisibility(View.VISIBLE);
            String addressText = address.replace(", ", "\n");
            m_countryView.setText(addressText);
            m_countryHeader.setText("Country");
        }
        else
        {
        	m_countryHeader.setVisibility(View.GONE);
            m_countryView.setVisibility(View.GONE);
        }
        
        int iconId = CategoryResources.getSmallIconForCategory(m_activity, category);
        m_categoryIcon.setImageResource(iconId);

        m_closeButton.setEnabled(true);
    	m_togglePinnedButton.setChecked(isPinned);
    	
        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();
    }

    public void dismissPoiInfo()
    {
        m_view.setVisibility(View.GONE);
    }

    private void handleCloseClicked()
    {
        m_view.setEnabled(false);

        SearchResultPoiViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }

    private void handleTogglePinnedClicked()
    {
        SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
    }
}
