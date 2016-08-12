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
    private final Handler mHandler = new Handler();
    
	public SearchResultsScrollButtonTouchDownListener(ListView view) {
		m_searchList = view;
	}

    final Runnable mAction = new Runnable() {
		@SuppressLint("NewApi")
		@Override public void run() {
            mHandler.postDelayed(this, 0);
            if(android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT)
            {
            	m_searchList.scrollListBy(SearchMenuResultsListAnimationConstants.SearchMenuResultsListScrollButtonSpeed);
            }
        }
    };
    
	@Override
	public boolean onTouch(View v, MotionEvent event) {
		switch(event.getAction()) {
			case MotionEvent.ACTION_DOWN:
	            mHandler.postDelayed(mAction, 0);
	            break;
	        case MotionEvent.ACTION_UP:
	            mHandler.removeCallbacks(mAction);
	            break;
		}
		return false;
	}
}
