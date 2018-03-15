// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

public class SearchProvidersJniMethods
{
    public static native void search(long nativeCallerPointer, String searchQuery);
    public static native void autocompleteSuggestions(long nativeCallerPointer, String searchQuery);
    public static native void searchWithContext(long nativeCallerPointer, String searchQuery,
                                                boolean isTag, boolean tryInterior, boolean shouldZoomToBuildingsView,
                                                boolean usesLocationAndRadius,
                                                double latitude, double longitude, double altitude,
                                                float radius);
    public static native void cancel(long nativeCallerPointer);

}
