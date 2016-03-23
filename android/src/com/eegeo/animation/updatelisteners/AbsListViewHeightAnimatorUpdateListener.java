package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.view.View;
import android.widget.AbsListView;

public class AbsListViewHeightAnimatorUpdateListener implements AnimatorUpdateListener
{
	private View m_view;
	
	public AbsListViewHeightAnimatorUpdateListener(View view)
	{
		m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator animation)
	{
		AbsListView.LayoutParams params = (AbsListView.LayoutParams)m_view.getLayoutParams();
    	params.height = (Integer) animation.getAnimatedValue();
    
    	m_view.setLayoutParams(params);
	}
}
