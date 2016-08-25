// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import com.eegeo.searchmenu.SearchMenuResultsListAnimationConstants;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ListView;

public class SearchResultsScrollButtonTouchDownListener implements View.OnTouchListener
{
	private ListView m_searchList = null;
    private final Handler m_handler = new Handler();
    private static  long m_delay = 100L/120L;
    
	public SearchResultsScrollButtonTouchDownListener(ListView view) {
		m_searchList = view;
	}

    final Runnable m_action = new Runnable() {
		@SuppressLint("NewApi")
		@Override public void run() {
            m_handler.postDelayed(this, m_delay);
            if(android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT)
            {   
            	m_searchList.scrollListBy(SearchMenuResultsListAnimationConstants.SearchMenuResultsListScrollButtonSpeed);
            	m_searchList.setVerticalScrollBarEnabled(false);
            }
        }
    };
    
	@Override
	public boolean onTouch(View v, MotionEvent event) {
		switch(event.getAction()) {
			case MotionEvent.ACTION_DOWN:
				m_handler.postDelayed(m_action, m_delay);
	            break;
	        case MotionEvent.ACTION_UP:
	        	m_handler.removeCallbacks(m_action);
	            break;
		}
		return false;
	}
}
