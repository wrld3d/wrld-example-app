package com.eegeo.examples.routesimulation;

public class RouteSimulationJniMethods 
{
	public static native void ToggleFollowCamera(long nativeCallerPointer);
	public static native void ChangeFollowDirection(long nativeCallerPointer);
	public static native void IncreaseSpeedFollowed(long nativeCallerPointer);
	public static native void DecreaseSpeedFollowed(long nativeCallerPointer);
	public static native void ToggleDirectFollow(long nativeCallerPointer);
	public static native void ToggleSideOfRoadToDriveOn(long nativeCallerPointer);	
}
