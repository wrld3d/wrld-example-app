// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.tags.TagResources;
import com.eegeo.ProjectSwallowApp.R;
import com.eegeo.entrypointinfrastructure.MainActivity;

public class GeoNamesSearchResultPoiView 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;
    private TextView m_titleView = null;
    private TextView m_countryView = null;
    private ImageView m_tagIcon = null;

    public GeoNamesSearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_geonames_layout, m_uiRoot, false);
       
        m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
        m_titleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_title);
        m_countryView = (TextView)m_view.findViewById(R.id.search_result_poi_view_country);
        m_tagIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_tag_icon);

        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
        
        m_closeButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
				handleCloseClicked();
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
    		final String iconKey)
    {
        m_titleView.setText(title);

        if(!address.equals(""))
        {
            m_countryView.setVisibility(View.VISIBLE);
            String addressText = address.replace(", ", "\n");
            m_countryView.setText(addressText);
        }
        else
        {
            m_countryView.setVisibility(View.GONE);
        }
        
        int iconId = TagResources.getSmallIconForTag(m_activity, iconKey);
        m_tagIcon.setImageResource(iconId);

        m_closeButton.setEnabled(true);
    	
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
}
