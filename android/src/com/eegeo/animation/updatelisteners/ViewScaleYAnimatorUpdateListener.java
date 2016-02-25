package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;

public class ViewScaleYAnimatorUpdateListener implements AnimatorUpdateListener
{
	private View m_view;
	
	public ViewScaleYAnimatorUpdateListener(View view)
	{
		m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator arg0)
	{
		m_view.setScaleY((Float)arg0.getAnimatedValue());
	}

}
