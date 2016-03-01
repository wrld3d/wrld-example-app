package com.eegeo.animation;

import android.animation.TimeInterpolator;
import android.animation.ValueAnimator;
import android.view.animation.AccelerateDecelerateInterpolator;

public class ReversibleValueAnimator extends ValueAnimator
{
	private long m_startDelayMilliseconds = 0;
	
	public static ReversibleValueAnimator ofInt(int... values)
	{
		ReversibleValueAnimator reversibleValueAnimator = new ReversibleValueAnimator();
		reversibleValueAnimator.setIntValues(values);
		
		return reversibleValueAnimator;
	}
	
	public static ReversibleValueAnimator ofFloat(float... values)
	{
		ReversibleValueAnimator reversibleValueAnimator = new ReversibleValueAnimator();
		reversibleValueAnimator.setFloatValues(values);
		
		return reversibleValueAnimator;
	}
	
	private ReversibleValueAnimator()
	{
		super();
		
		setInterpolator(new AccelerateDecelerateInterpolator());
	}
	
	@Override
	public void setInterpolator(TimeInterpolator value)
	{
		super.setInterpolator(new ReversibleTimeInterpolator(value));
	}
	
	public ReversibleTimeInterpolator getReversibleInterpolator()
	{
		return (ReversibleTimeInterpolator)super.getInterpolator();
	}
	
	@Override
	public void setStartDelay(long delayMilliseconds)
	{
		m_startDelayMilliseconds = delayMilliseconds;
	}
	
	@Override
	public void start()
	{
		if(getReversibleInterpolator().getReversed())
		{
			super.setStartDelay(0);
		}
		else
		{
			super.setStartDelay(m_startDelayMilliseconds);
		}
		
		super.start();
	}
}
