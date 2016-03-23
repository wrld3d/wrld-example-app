package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;
import android.widget.LinearLayout;

public class LinearLayoutViewHeightAnimatorUpdateListener implements AnimatorUpdateListener
{
	private View m_view;
	
	public LinearLayoutViewHeightAnimatorUpdateListener(View view)
	{
		m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator animation)
	{
		LinearLayout.LayoutParams params = (LinearLayout.LayoutParams)m_view.getLayoutParams();
    	params.height = (Integer) animation.getAnimatedValue();
    
    	m_view.setLayoutParams(params);
	}
}
