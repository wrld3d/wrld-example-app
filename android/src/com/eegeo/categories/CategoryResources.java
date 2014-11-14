package com.eegeo.categories;

import java.util.Locale;

import android.app.Activity;

public class CategoryResources
{
	public static int getSearchResultIconForCategory(Activity activity, String category)
	{
		String matchedCategory = getCategoryMatch(category);
		String uri = "drawable/icon2_" + matchedCategory;
		int imageResource = activity.getResources().getIdentifier(uri, null, activity.getPackageName());

		return imageResource;
	}

	private static String getCategoryMatch(String category)
	{
		category = category.toLowerCase(Locale.getDefault());
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

	public static int getSmallIconForCategory(Activity activity, String category)
	{
		String matchedCategory = getCategoryMatch(category);
		return getSmallIconForResourceName(activity, matchedCategory);
	}

	public static int getSmallIconForResourceName(Activity activity, String resourceName)
	{
		String uri = "drawable/icon1_" + resourceName;
		int imageResource = activity.getResources().getIdentifier(uri, null, activity.getPackageName());
		return imageResource;
	}

}
