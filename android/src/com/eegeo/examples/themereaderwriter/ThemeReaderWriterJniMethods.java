package com.eegeo.examples.themereaderwriter;

public class ThemeReaderWriterJniMethods 
{
	public static native void SetCurrentTheme(long nativeCallerPointer, String location);
	public static native void ReadCurrentThemeName(long nativeCallerPointer);
}
