// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import android.annotation.SuppressLint;
import android.view.View;
import android.view.View.OnScrollChangeListener;
import android.widget.ImageView;

import android.widget.ScrollView;

@SuppressLint("NewApi")
public class SearchResultsPoiViewScrollListener implements  OnScrollChangeListener
{
	private ImageView m_footerFade;
	private ScrollView m_searchList;
	
	public SearchResultsPoiViewScrollListener(ImageView imageView, boolean scrollable, ScrollView searchList) 
	{
		m_footerFade = imageView;
		m_searchList = searchList;
	}
	
	@Override
	public void onScrollChange(View arg0, int arg1, int arg2, int arg3, int arg4) {
		View view = (View) m_searchList.getChildAt(m_searchList.getChildCount()-1);

	    int scrollDistanceFromBottom = (view.getBottom()-(m_searchList.getHeight() + m_searchList.getScrollY()));

	    if( scrollDistanceFromBottom == 0 )
	    {
	    	m_footerFade.setVisibility(View.INVISIBLE);
	    }
	    else
	    {
	    	m_footerFade.setVisibility(View.VISIBLE);
	    }
	}
}