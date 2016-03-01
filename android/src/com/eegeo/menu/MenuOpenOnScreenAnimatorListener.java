//Copyright eeGeo Ltd (2012-2016), All Rights Reserved

package com.eegeo.menu;

import android.animation.Animator;
import android.animation.Animator.AnimatorListener;

public class MenuOpenOnScreenAnimatorListener implements AnimatorListener
{
	MenuAnimationStateCallback m_menuAnimationStateCallback;
	
	public MenuOpenOnScreenAnimatorListener(MenuAnimationStateCallback menuAnimationStateCallback)
	{
		m_menuAnimationStateCallback = menuAnimationStateCallback;
	}

	@Override
	public void onAnimationCancel(Animator arg0)
	{		
	}

	@Override
	public void onAnimationEnd(Animator arg0)
	{
		m_menuAnimationStateCallback.onOpenOnScreenAnimationComplete();
	}

	@Override
	public void onAnimationRepeat(Animator arg0)
	{	
	}

	@Override
	public void onAnimationStart(Animator arg0)
	{	
		m_menuAnimationStateCallback.onOpenOnScreenAnimationStart();
	}

}
