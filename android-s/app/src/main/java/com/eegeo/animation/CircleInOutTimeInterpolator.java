package com.eegeo.animation;

import android.animation.TimeInterpolator;

public class CircleInOutTimeInterpolator implements TimeInterpolator
{
	@Override
	public float getInterpolation(float arg0)
	{
		return (float) (((arg0 *= 2) <= 1 ? 1 - Math.sqrt(1 - arg0 * arg0) : Math.sqrt(1 - (arg0 -= 2) * arg0) + 1) / 2);
	}
}
