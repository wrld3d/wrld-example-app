// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.categories;

import java.util.Locale;

import android.app.Activity;

public class CategoryResources
{
    public static int getSearchResultIconForCategory(Activity activity, String category)
    {
        return getSmallIconForCategory(activity, category);
    }

    public static int getSmallIconForCategory(Activity activity, String category)
    {
        return getIconForResourceName(activity, category);
    }

    public static int getIconForResourceName(Activity activity, String resourceName)
    {
    	String iconPrefix = "icon1_";
        String uri = "drawable/" + iconPrefix + resourceName;
        int imageResource = activity.getResources().getIdentifier(uri, null, activity.getPackageName());
        return imageResource;
    }

}
