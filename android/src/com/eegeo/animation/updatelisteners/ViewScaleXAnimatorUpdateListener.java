package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;

public class ViewScaleXAnimatorUpdateListener implements AnimatorUpdateListener
{
	private View m_view;
	
	public ViewScaleXAnimatorUpdateListener(View view)
	{
		m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator arg0)
	{
		m_view.setScaleX((Float)arg0.getAnimatedValue());
	}

}
