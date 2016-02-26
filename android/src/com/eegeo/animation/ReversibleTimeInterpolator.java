package com.eegeo.animation;

import android.animation.TimeInterpolator;

public class ReversibleTimeInterpolator implements TimeInterpolator
{
	private TimeInterpolator m_timeInterpolator;
	
	private boolean m_reversed;
	
	public ReversibleTimeInterpolator(TimeInterpolator timeInterpolator)
	{
		m_timeInterpolator = timeInterpolator;
	}
	
	public void SetReversed(boolean reversed)
	{
		m_reversed = reversed;
	}
	
	public boolean getReversed()
	{
		return m_reversed;
	}
	
	@Override
	public float getInterpolation(float value)
	{
		if(m_reversed)
		{
			value = 1.0f - value;
		}
		
		return m_timeInterpolator.getInterpolation(value);
	}
}
