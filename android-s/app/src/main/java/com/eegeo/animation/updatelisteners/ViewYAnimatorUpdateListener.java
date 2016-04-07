package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;

public class ViewYAnimatorUpdateListener implements AnimatorUpdateListener
{
	private View m_view;
	
	public ViewYAnimatorUpdateListener(View view)
	{
	    m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator animator)
	{
		m_view.setY((Integer)animator.getAnimatedValue());
	}
}
