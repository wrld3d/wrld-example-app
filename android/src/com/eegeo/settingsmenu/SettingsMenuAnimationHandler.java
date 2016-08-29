// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.settingsmenu;

import android.animation.TimeInterpolator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.animation.CircleInOutTimeInterpolator;
import com.eegeo.animation.ReversibleAnimatorSet;
import com.eegeo.animation.ReversibleValueAnimator;
import com.eegeo.animation.updatelisteners.ViewAlphaAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewScaleXAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewXAnimatorUpdateListener;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuAnimationHandler;
import com.eegeo.menu.MenuOffScreenAnimatorListener;
import com.eegeo.menu.MenuView;
import com.eegeo.mobileexampleapp.R;

public class SettingsMenuAnimationHandler extends MenuAnimationHandler
{
	protected final int m_stateChangeAnimationTimeMilliseconds = 300;
	
	private ReversibleAnimatorSet m_closedToOffScreenAnimatorSet;
	
	public SettingsMenuAnimationHandler(MainActivity mainActivity, View view, MenuView menuView)
	{
		super(mainActivity, view, menuView);
		
		m_closedToOffScreenAnimatorSet = new ReversibleAnimatorSet();
		
		View dragTabView = m_view.findViewById(R.id.settings_menu_drag_button_view);
		View titleContainerView = m_view.findViewById(R.id.settings_menu_title_container);
		View listItemContainerView = m_view.findViewById(R.id.settings_menu_list_container);
		View settingsMenuTitleView = m_view.findViewById(R.id.settings_menu_title);
		View settingsMenuSeparatorView = m_view.findViewById(R.id.settings_menu_title_separator);
		
		final RelativeLayout uiRoot = (RelativeLayout)m_mainActivity.findViewById(R.id.ui_container);
		
		int screenWidthPx = uiRoot.getWidth();
		
		int menuButtonMarginPx = (int) m_mainActivity.getResources().getDimension(R.dimen.menu_button_margin);
		
		int titleContainerWidthPx = titleContainerView.getWidth();
        int dragTabWidthPx = dragTabView.getWidth();
        
        titleContainerView.setPivotX(0.0f);
        titleContainerView.setX(dragTabWidthPx);
        
        settingsMenuTitleView.setX(dragTabWidthPx);
        
        addAnimator(m_onScreenAnimatorSet, screenWidthPx + (dragTabWidthPx + menuButtonMarginPx), screenWidthPx - (dragTabWidthPx + menuButtonMarginPx), new ViewXAnimatorUpdateListener(m_view), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, 0.0f, 0.0f, new ViewScaleXAnimatorUpdateListener(titleContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, 0, dragTabWidthPx + menuButtonMarginPx, new ViewXAnimatorUpdateListener(listItemContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, 0.0f, 0.0f, new ViewAlphaAnimatorUpdateListener(settingsMenuTitleView), new CircleInOutTimeInterpolator());
		addAnimator(m_onScreenAnimatorSet, 0, dragTabWidthPx + menuButtonMarginPx, new ViewXAnimatorUpdateListener(settingsMenuSeparatorView), new CircleInOutTimeInterpolator());
		
		addAnimator(m_openAnimatorSet, screenWidthPx - (dragTabWidthPx + menuButtonMarginPx), screenWidthPx - (dragTabWidthPx + titleContainerWidthPx), new ViewXAnimatorUpdateListener(m_view), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, 0.0f, 1.0f, new ViewScaleXAnimatorUpdateListener(titleContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, dragTabWidthPx + menuButtonMarginPx, dragTabWidthPx, new ViewXAnimatorUpdateListener(listItemContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, 0.0f, 1.0f, new ViewAlphaAnimatorUpdateListener(settingsMenuTitleView), new CircleInOutTimeInterpolator());
		addAnimator(m_openAnimatorSet, dragTabWidthPx + menuButtonMarginPx, dragTabWidthPx, new ViewXAnimatorUpdateListener(settingsMenuSeparatorView), new CircleInOutTimeInterpolator());
	
		addAnimator(m_closedToOffScreenAnimatorSet, screenWidthPx - (dragTabWidthPx + titleContainerWidthPx), screenWidthPx, new ViewXAnimatorUpdateListener(m_view), new CircleInOutTimeInterpolator());
		addAnimator(m_closedToOffScreenAnimatorSet, 1.0f, 0.0f, new ViewScaleXAnimatorUpdateListener(titleContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_closedToOffScreenAnimatorSet, dragTabWidthPx, dragTabWidthPx + menuButtonMarginPx, new ViewXAnimatorUpdateListener(listItemContainerView), new CircleInOutTimeInterpolator());
		addAnimator(m_closedToOffScreenAnimatorSet, 1.0f, 0.0f, new ViewAlphaAnimatorUpdateListener(settingsMenuTitleView), new CircleInOutTimeInterpolator());
		addAnimator(m_closedToOffScreenAnimatorSet, dragTabWidthPx, dragTabWidthPx + menuButtonMarginPx, new ViewXAnimatorUpdateListener(settingsMenuSeparatorView), new CircleInOutTimeInterpolator());
	}
	
	protected void addAnimator(ReversibleAnimatorSet animatorSet, float startVal, float endVal, AnimatorUpdateListener updateListener, TimeInterpolator interpolator)
	{
		ReversibleValueAnimator valueAnimator = ReversibleValueAnimator.ofFloat(startVal, endVal);
		
		addAnimator(animatorSet, valueAnimator, updateListener, interpolator);
	}
	
	protected void addAnimator(ReversibleAnimatorSet animatorSet, int startVal, int endVal, AnimatorUpdateListener updateListener, TimeInterpolator interpolator)
	{
		ReversibleValueAnimator valueAnimator = ReversibleValueAnimator.ofInt(startVal, endVal);
		
		addAnimator(animatorSet, valueAnimator, updateListener, interpolator);
	}
	
	protected void addAnimator(ReversibleAnimatorSet animatorSet, ReversibleValueAnimator valueAnimator, AnimatorUpdateListener updateListener, TimeInterpolator interpolator)
	{
		valueAnimator.setDuration(m_stateChangeAnimationTimeMilliseconds);
		
		valueAnimator.addUpdateListener(updateListener);
		valueAnimator.setInterpolator(interpolator);
		
		animatorSet.addAnimator(valueAnimator);
	}
	
	public void playToClosedOffScreen()
	{
		m_closedToOffScreenAnimatorSet.start(new MenuOffScreenAnimatorListener(m_menuView), false);
	}
}
