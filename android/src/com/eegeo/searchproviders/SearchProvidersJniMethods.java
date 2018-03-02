// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

public class SearchProvidersJniMethods
{
    public static native void search(long nativeCallerPointer, String searchQuery);
    public static native void cancel(long nativeCallerPointer);
}
