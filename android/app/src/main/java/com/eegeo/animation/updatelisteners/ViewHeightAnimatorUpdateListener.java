package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;
import android.view.ViewGroup;

public class ViewHeightAnimatorUpdateListener<T extends ViewGroup.LayoutParams> implements AnimatorUpdateListener
{
	private View m_view;
	
	public ViewHeightAnimatorUpdateListener(View view)
	{
		m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator animation)
	{
		T layoutParams = (T)m_view.getLayoutParams();
		layoutParams.height = (Integer) animation.getAnimatedValue();
    
    	m_view.setLayoutParams(layoutParams);
	}
}
