// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchproviders;

public class SearchProvidersJniMethods
{
    public static native void search(long nativeCallerPointer, String searchQuery);
    public static native void autocompleteSuggestions(long nativeCallerPointer, String searchQuery);
    public static native void searchWithContext(long nativeCallerPointer, String searchQuery,
                                                boolean clearPreviousResults,
                                                boolean isTag, String tagText,
                                                boolean tryInterior,
                                                boolean usesLocation,
                                                double latitude, double longitude, double altitude,
                                                boolean usesRadius,
                                                float radius);
    public static native void cancel(long nativeCallerPointer);
    public static native void cancelSuggestions(long nativeCallerPointer);

}
