package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;

public class ViewAlphaAnimatorUpdateListener implements AnimatorUpdateListener
{
	private View m_view;
	
	public ViewAlphaAnimatorUpdateListener(View view)
	{
		m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator animation)
	{
		m_view.setAlpha((Float) animation.getAnimatedValue());
	}
}
