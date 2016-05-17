package com.eegeo.animation;

import android.animation.TimeInterpolator;

public class BackOutTimeInterpolator implements TimeInterpolator
{
	private final float overShoot = 2.55f;
	
	@Override
	public float getInterpolation(float arg0)
	{
		return --arg0 * arg0 * ((overShoot + 1) * arg0 + overShoot) + 1;
	}
}
