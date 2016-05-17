//Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.animation.updatelisteners;

import android.animation.ValueAnimator;
import android.view.View;

public class ViewXAnimatorUpdateListener implements ValueAnimator.AnimatorUpdateListener
{ 
	private View m_view;
	
	public ViewXAnimatorUpdateListener(View view)
	{
	    m_view = view;
	}
	
	@Override
	public void onAnimationUpdate(ValueAnimator animator)
	{
		m_view.setX((Integer)animator.getAnimatedValue());
	}
}
