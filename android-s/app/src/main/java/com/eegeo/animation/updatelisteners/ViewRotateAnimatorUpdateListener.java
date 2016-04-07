package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.util.Log;
import android.view.View;

public class ViewRotateAnimatorUpdateListener implements AnimatorUpdateListener
{
	private View m_view;
	
	public ViewRotateAnimatorUpdateListener(View view)
	{
		m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator animation)
	{
		m_view.setRotation((Float) animation.getAnimatedValue());
		m_view.requestLayout();
	}
}
