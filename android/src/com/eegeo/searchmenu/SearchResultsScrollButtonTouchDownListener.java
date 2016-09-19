// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.searchmenu.SearchMenuResultsListAnimationConstants;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ListView;

public class SearchResultsScrollButtonTouchDownListener implements View.OnTouchListener
{
	private ListView m_searchList = null;
    private final Handler m_handler = new Handler();
	private MainActivity m_activity;
    private float m_scaledDensity;
    float m_screenIndependentPxPerSecond;
    
	public SearchResultsScrollButtonTouchDownListener(ListView view, MainActivity activity) 
	{
		m_searchList = view;
		m_activity = activity;
        DisplayMetrics metrics =  m_activity.getResources().getDisplayMetrics();
        m_scaledDensity = metrics.scaledDensity;
        m_screenIndependentPxPerSecond = (SearchMenuResultsListAnimationConstants.SearchMenuResultsListScrollButtonSpeed * m_scaledDensity);
	}

    final Runnable m_action = new Runnable() 
    {
		@SuppressLint("NewApi")
		@Override public void run() 
		{			
            if(android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT)
            {   
            	m_searchList.scrollListBy((int)(m_screenIndependentPxPerSecond));
            	m_searchList.setVerticalScrollBarEnabled(false);
            }
            else
            {
            	m_searchList.smoothScrollBy((int) m_screenIndependentPxPerSecond, 0);
            }
            m_handler.post(this);
        }
    };
    
	@Override
	public boolean onTouch(View v, MotionEvent event) 
	{
		switch(event.getAction()) 
		{
			case MotionEvent.ACTION_DOWN:
				m_handler.post(m_action);
	            break;
	        case MotionEvent.ACTION_UP:
	        	m_handler.removeCallbacks(m_action);
	            break;
		}
		return false;
	}
}
