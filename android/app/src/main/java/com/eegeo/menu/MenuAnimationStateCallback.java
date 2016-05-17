// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

package com.eegeo.menu;

public interface MenuAnimationStateCallback
{
	public void onOffScreenAnimationComplete();

	public void onClosedOnScreenAnimationComplete();

	public void onOpenOnScreenAnimationComplete();
	
	public void onOpenOnScreenAnimationStart();
}
