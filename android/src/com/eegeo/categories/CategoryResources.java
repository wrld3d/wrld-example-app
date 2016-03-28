// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.categories;

import java.util.Locale;

import android.app.Activity;

public class CategoryResources
{
    private static String getCategoryMatch(String category)
    {
        category = category.toLowerCase(Locale.getDefault());
        if(category.contains("around me"))
        {
        	return "aroundme";
        }
        if(category.contains("caf\u00e9") || category.contains("cafe") || category.contains("coffee"))
        {
            return "coffee";
        }
        if(category.contains("nightlife") || category.contains("night life"))
        {
            return "nightlife";
        }
        if(category.contains("museum") || category.equals("arts"))
        {
            return "arts";
        }
        if(category.contains("park"))
        {
            return "park";
        }
        if(category.contains("bank"))
        {
            return "bank";
        }
        if(category.contains("hotel"))
        {
            return "hotel";
        }
        if(category.contains("restaurant") || category.contains("food"))
        {
            return "food";
        }

        return "misc";
    }
    
    public static int getSearchResultIconForCategory(Activity activity, String category)
    {
        return getSmallIconForCategory(activity, category);
    }

    public static int getSmallIconForCategory(Activity activity, String category)
    {
        String matchedCategory = getCategoryMatch(category);
        return getIconForResourceName(activity, matchedCategory, false);
    }

    public static int getIconForResourceName(Activity activity, String resourceName, boolean isSmallIcon)
    {
    	String iconPrefix = isSmallIcon ? "icon2_" : "icon1_";
        String uri = "drawable/" + iconPrefix + resourceName;
        int imageResource = activity.getResources().getIdentifier(uri, null, activity.getPackageName());
        return imageResource;
    }

}
