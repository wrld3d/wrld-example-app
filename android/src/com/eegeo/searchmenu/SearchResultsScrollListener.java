// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import android.hardware.Camera.FaceDetectionListener;
import android.view.View;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.DecelerateInterpolator;
import android.widget.AbsListView;
import android.widget.AbsListView.OnScrollListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;

public class SearchResultsScrollListener implements OnScrollListener
{
	private Button m_searchResultsScrollButton;
	private ImageView m_searchResultsFade;
	private boolean m_searchResultsScrollable;
	private ListView m_searchList;
	
	public SearchResultsScrollListener(Button button, ImageView imageView, boolean scrollable, ListView searchList) 
	{
		m_searchResultsScrollButton = button;
		m_searchResultsFade = imageView;
		m_searchResultsScrollable = scrollable;
		m_searchList = searchList;
	}
	
	public void UpdateScrollable(boolean scrollable)
	{
		m_searchResultsScrollable = scrollable;
	}
	
    private void fadeInButtonAnimation()
    {
		Animation fadeIn = new AlphaAnimation(0, 1);
		fadeIn.setInterpolator(new DecelerateInterpolator());
		fadeIn.setDuration(SearchMenuResultsListAnimationConstants.SearchMenuResultsListScrollButtonAnimationSpeedMilliseconds);

		AnimationSet animation = new AnimationSet(false);
		animation.addAnimation(fadeIn);
		m_searchResultsScrollButton.setAnimation(animation);
    }

	@Override
	public void onScrollStateChanged(AbsListView view, int scrollState) 
	{
		
	}
	@Override
	public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) 
	{	
		m_searchList.setVerticalScrollBarEnabled(true);
		if(totalItemCount == 0)
			return;
	
		View lastChild = (View) view.getChildAt(view.getChildCount() - 1);
		
	    boolean childAlignsWithBottomofView = false;
		if(lastChild.getBottom() - (view.getHeight() + view.getScrollY()) == 0)
		{
				childAlignsWithBottomofView = true;
		}
	    
	    final int lastItem = firstVisibleItem + visibleItemCount;

	    if( childAlignsWithBottomofView && lastItem == totalItemCount)
	    {
	    	m_searchResultsFade.setVisibility(view.INVISIBLE);
			m_searchResultsScrollButton.setVisibility(view.INVISIBLE);
	    }
		else if (m_searchResultsScrollable)
		{
			if (m_searchResultsFade.getVisibility() == View.INVISIBLE)
			{
				fadeInButtonAnimation();
			}
			
			m_searchResultsFade.setVisibility(view.VISIBLE);
			m_searchResultsScrollButton.setVisibility(view.VISIBLE);
		}       
	}
}
