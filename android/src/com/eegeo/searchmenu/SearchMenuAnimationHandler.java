// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import android.animation.TimeInterpolator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;

import com.eegeo.animation.BackOutTimeInterpolator;
import com.eegeo.animation.CircleInOutTimeInterpolator;
import com.eegeo.animation.ReversibleAnimatorSet;
import com.eegeo.animation.ReversibleValueAnimator;
import com.eegeo.animation.updatelisteners.ViewAlphaAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewScaleYAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewXAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewYAnimatorUpdateListener;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuAnimationHandler;
import com.eegeo.menu.MenuView;
import com.eegeo.mobileexampleapp.R;

public class SearchMenuAnimationHandler extends MenuAnimationHandler
{
	protected final int m_delayedAnimationsMilliseconds = 200;
	protected final int m_stateChangeAnimationTimeMilliseconds = 300;
	
	private ReversibleAnimatorSet m_searchResultsAnimatorSet;
	private boolean m_showingSearchResults = false;
	
	public SearchMenuAnimationHandler(MainActivity mainActivity, View view, MenuView menuView)
	{
		super(mainActivity, view, menuView);
		
		m_searchResultsAnimatorSet = new ReversibleAnimatorSet();

		View listContainerView = m_view.findViewById(R.id.search_menu_list_container);
		View dragTabView = m_view.findViewById(R.id.search_menu_drag_button_view);
		View titleContainerView = m_view.findViewById(R.id.search_menu_title_bar);
		View editBoxBackgroundView = titleContainerView.findViewById(R.id.search_menu_edit_text_background);
		View editBoxView = titleContainerView.findViewById(R.id.search_menu_view_edit_text_view);
		View clearButtonView = titleContainerView.findViewById(R.id.search_menu_clear_button);
		View searchCountView = m_view.findViewById(R.id.search_menu_result_count_container);
		View anchorArrowView = m_view.findViewById(R.id.search_results_anchor_arrow);
			
        int dragTabWidthPx = dragTabView.getWidth();
        int titleContainerWidthPx = titleContainerView.getWidth();
        int titleBarControlsYStartPx = -dragTabWidthPx / 2;
        int editTextYEndPx = (int)editBoxView.getY();
        int clearButtonHeightPx =  (int)m_mainActivity.getResources().getDimension(R.dimen.search_clear_button_size);
        int clearButtonYEndPx = (dragTabWidthPx - clearButtonHeightPx) / 2;
        int anchorArrowMarginPx = (int)m_mainActivity.getResources().getDimension(R.dimen.search_result_anchor_margin);
		int menuButtonMarginPx = (int)m_mainActivity.getResources().getDimension(R.dimen.menu_button_margin);

        m_view.setX(0.0f);
        titleContainerView.setPivotX(0.0f);
		searchCountView.setVisibility(View.GONE);
	
		addAnimator(m_onScreenAnimatorSet, -(dragTabWidthPx + menuButtonMarginPx), menuButtonMarginPx, false, new ViewXAnimatorUpdateListener(dragTabView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, -menuButtonMarginPx, -menuButtonMarginPx, false, new ViewXAnimatorUpdateListener(titleContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, -titleContainerWidthPx, -titleContainerWidthPx, false, new ViewXAnimatorUpdateListener(listContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, 0.0f, 0.0f, false, new ViewScaleYAnimatorUpdateListener(editBoxBackgroundView), new BackOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, titleBarControlsYStartPx, titleBarControlsYStartPx, false, new ViewYAnimatorUpdateListener(editBoxView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, 0.0f, 0.0f, false, new ViewAlphaAnimatorUpdateListener(editBoxView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, titleBarControlsYStartPx, titleBarControlsYStartPx, false, new ViewYAnimatorUpdateListener(clearButtonView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, 0.0f, 0.0f, false, new ViewAlphaAnimatorUpdateListener(clearButtonView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, -titleContainerWidthPx, -titleContainerWidthPx, false, new ViewXAnimatorUpdateListener(anchorArrowView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, -menuButtonMarginPx * 2, 0, false, new ViewXAnimatorUpdateListener(searchCountView), new CircleInOutTimeInterpolator());
		
		addAnimator(m_openAnimatorSet, menuButtonMarginPx, titleContainerWidthPx, false, new ViewXAnimatorUpdateListener(dragTabView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, -menuButtonMarginPx, 0, false, new ViewXAnimatorUpdateListener(titleContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, -titleContainerWidthPx, 0, false, new ViewXAnimatorUpdateListener(listContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, 0.0f, 1.0f, true, new ViewScaleYAnimatorUpdateListener(editBoxBackgroundView), new BackOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, titleBarControlsYStartPx, editTextYEndPx, true, new ViewYAnimatorUpdateListener(editBoxView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, 0.0f, 1.0f, true, new ViewAlphaAnimatorUpdateListener(editBoxView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, titleBarControlsYStartPx, clearButtonYEndPx, true, new ViewYAnimatorUpdateListener(clearButtonView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, 0.0f, 1.0f, true, new ViewAlphaAnimatorUpdateListener(clearButtonView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, -titleContainerWidthPx, anchorArrowMarginPx, false, new ViewXAnimatorUpdateListener(anchorArrowView), new CircleInOutTimeInterpolator());
		
		addAnimator(m_searchResultsAnimatorSet, menuButtonMarginPx, 0, false, new ViewXAnimatorUpdateListener(searchCountView), new CircleInOutTimeInterpolator());
	}
	
	protected void addAnimator(ReversibleAnimatorSet animatorSet, float startVal, float endVal, boolean useStartDelay, AnimatorUpdateListener updateListener, TimeInterpolator interpolator)
	{
		ReversibleValueAnimator valueAnimator = ReversibleValueAnimator.ofFloat(startVal, endVal);
		
		addAnimator(animatorSet, valueAnimator, useStartDelay, updateListener, interpolator);
	}
	
	protected void addAnimator(ReversibleAnimatorSet animatorSet, int startVal, int endVal, boolean useStartDelay, AnimatorUpdateListener updateListener, TimeInterpolator interpolator)
	{
		ReversibleValueAnimator valueAnimator = ReversibleValueAnimator.ofInt(startVal, endVal);
		
		addAnimator(animatorSet, valueAnimator, useStartDelay, updateListener, interpolator);
	}
	
	protected void addAnimator(ReversibleAnimatorSet animatorSet, ReversibleValueAnimator valueAnimator, boolean useStartDelay, AnimatorUpdateListener updateListener, TimeInterpolator interpolator)
	{
		if(useStartDelay)
		{
			valueAnimator.setStartDelay(m_delayedAnimationsMilliseconds);
			valueAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds - m_delayedAnimationsMilliseconds);
		}
		else
		{
			valueAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		}
		
		valueAnimator.addUpdateListener(updateListener);
		valueAnimator.setInterpolator(interpolator);
		
		animatorSet.addAnimator(valueAnimator);
	}
	
	public void showSearchResultsView()
	{
		if(!m_showingSearchResults) 
		{
			View searchCountView = m_view.findViewById(R.id.search_menu_result_count_container);
			searchCountView.setVisibility(View.VISIBLE);
			
			if(!isOffScreen())
			{
				m_searchResultsAnimatorSet.start(null, false);
			}
			
			m_showingSearchResults = true;
		}
	}
	
	public void hideSearchResultsView()
	{
		if(m_showingSearchResults)
		{
			m_searchResultsAnimatorSet.setCurrentPlayTime(0);
			View searchCountView = m_view.findViewById(R.id.search_menu_result_count_container);
			searchCountView.setVisibility(View.GONE);
			m_showingSearchResults = false;
		}
	}
}
