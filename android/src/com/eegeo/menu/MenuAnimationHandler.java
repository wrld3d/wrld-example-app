// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.menu;

import android.view.View;

import com.eegeo.animation.ReversibleAnimatorSet;
import com.eegeo.entrypointinfrastructure.MainActivity;

public abstract class MenuAnimationHandler
{
	protected MainActivity m_mainActivity = null;
	protected View m_view;
	protected MenuView m_menuView;
	
	protected ReversibleAnimatorSet m_onScreenAnimatorSet = null;
	protected ReversibleAnimatorSet m_openAnimatorSet = null;
	
	final private float m_lowEndThreshold = 0.01f;
	final private float m_highEndThreshold = 0.99f;
	
	public MenuAnimationHandler(MainActivity mainActivity, View view, MenuView menuView)
	{
		m_mainActivity = mainActivity;
		m_view = view;
		m_menuView = menuView;
		
		m_onScreenAnimatorSet = new ReversibleAnimatorSet();
		m_openAnimatorSet = new ReversibleAnimatorSet();
	}
	
	public void playToOffScreen()
	{
		boolean isReversed = true;
		m_onScreenAnimatorSet.start(new MenuOffScreenAnimatorListener(m_menuView), isReversed);
	}
	
	public void playToClosedOnScreen()
	{
		if(getOpenOnScreenState() > m_highEndThreshold)
		{
			boolean isReversed = true;
			m_openAnimatorSet.start(new MenuClosedOnScreenAnimatorListener(m_menuView), isReversed);
		}
		else
		{
			boolean isReversed = false;
			m_onScreenAnimatorSet.start(new MenuClosedOnScreenAnimatorListener(m_menuView), isReversed);
		}
	}
	
	public void playToOpenOnScreen()
	{
		boolean isReversed = false;
		m_openAnimatorSet.start(new MenuOpenOnScreenAnimatorListener(m_menuView), isReversed);
	}
	
	public void setToIntermediateOnScreenState(float onScreenState)
	{
		m_onScreenAnimatorSet.setCurrentPlayTime((long)(onScreenState * m_onScreenAnimatorSet.getDurationMilliseconds()));
	}
	
	public void setToIntermediateOpenState(float openState)
	{
		m_openAnimatorSet.setCurrentPlayTime((long)(openState * m_openAnimatorSet.getDurationMilliseconds()));
	}
	
	public float getOnScreenState()
	{
		return m_onScreenAnimatorSet.getAnimatedFraction();
	}
	
	public float getOpenOnScreenState()
	{
		return m_openAnimatorSet.getAnimatedFraction();
	}
	
	public boolean isOffScreen()
	{
		return getOnScreenState() <= m_lowEndThreshold;
	}
	
	public boolean isClosedOnScreen()
	{
		return getOnScreenState() > m_highEndThreshold && getOpenOnScreenState() < m_lowEndThreshold;
	}
	
	public boolean isOpenOnScreen()
	{
		return getOpenOnScreenState() > m_highEndThreshold;
	}
	
	public void cancelAnimation()
	{
		m_onScreenAnimatorSet.cancel();
		m_openAnimatorSet.cancel();
	}
}
