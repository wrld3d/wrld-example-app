package com.eegeo.examples.examplecontroller;

public class ExampleControllerJniMethods 
{
	public static native void ActivatePrevious(long nativeCallerPointer);
	public static native void ActivateNext(long nativeCallerPointer);
	public static native void SelectExample(long nativeCallerPointer, String selectedExample);
}
