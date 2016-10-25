// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.tags.TagResources;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.TintablePinToggleButton;
import com.eegeo.mobileexampleapp.R;

public class GeoNamesSearchResultPoiView 
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;
    private View m_togglePinnedButton = null;
    private TextView m_titleView = null;
    private TextView m_countryView = null;
    private ImageView m_tagIcon = null;
    private TextView m_dropPinText = null;
    private TintablePinToggleButton m_togglePinnedWrapper;
    
    private static String m_pinTextDefault = "Drop Pin";
    private static String m_pinTextPressed = "Remove Pin";

    public GeoNamesSearchResultPoiView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_geonames_layout, m_uiRoot, false);
       
        m_closeButton = m_view.findViewById(R.id.search_result_poi_view_close_button);
        m_togglePinnedButton = m_view.findViewById(R.id.search_result_poi_view_toggle_pinned_button);
        m_togglePinnedWrapper = new TintablePinToggleButton(m_togglePinnedButton);
        m_titleView = (TextView)m_view.findViewById(R.id.search_result_poi_view_title);
        m_countryView = (TextView)m_view.findViewById(R.id.search_result_poi_view_country);
        m_tagIcon = (ImageView)m_view.findViewById(R.id.search_result_poi_view_tag_icon);
        m_dropPinText = (TextView)m_view.findViewById(R.id.drop_pin_text);

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
    		final String iconKey,
    		final boolean isPinned)
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
        m_togglePinnedWrapper.setPinToggleState(isPinned);
    	
        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();
        
        if(m_togglePinnedWrapper.isPinned())
        {
        	m_dropPinText.setText("Remove Pin");
        }
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
        if(m_togglePinnedWrapper.isPinned())
    	{
    		showRemovePinDialog();
    	}
    	else
    	{
    		SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
            m_togglePinnedWrapper.setPinToggleState(true);
            m_dropPinText.setText(m_pinTextPressed);
    	}
    }
    
    private void showRemovePinDialog()
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);
        builder.setTitle("Remove Pin")
        .setMessage("Are you sure you want to remove this pin?")
        .setPositiveButton("Yes,  delete it", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int id)
            {
        		SearchResultPoiViewJniMethods.TogglePinnedButtonClicked(m_nativeCallerPointer);
                m_togglePinnedWrapper.setPinToggleState(false);
                m_dropPinText.setText(m_pinTextDefault);
            }
        })
        .setNegativeButton("No,  keep it", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
            	m_togglePinnedWrapper.setPinToggleState(true);
            }
        })
        .setOnCancelListener(new DialogInterface.OnCancelListener()
        {
            @Override
            public void onCancel(DialogInterface dialog)
            {
            	m_togglePinnedWrapper.setPinToggleState(true);
            }
        });
        AlertDialog dialog = builder.create();
        dialog.show();
    }
}
