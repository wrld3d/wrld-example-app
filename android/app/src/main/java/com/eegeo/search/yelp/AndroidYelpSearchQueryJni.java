//Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.search.yelp;

public class AndroidYelpSearchQueryJni 
{
	 public static native void SearchQueryComplete(
			 long nativeCallerPointer, 
			 boolean success,
			 String result);

	 public static native void BusinessQueryComplete(
			 long nativeCallerPointer, 
			 boolean success,
			 String result);
}