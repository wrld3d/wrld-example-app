package com.eegeo.flurry;

import java.util.Map;
import java.util.HashMap;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.flurry.android.FlurryAgent;

public class FlurryWrapper 
{
	public static void begin(MainActivity activity, String apiKey, String appVersion)
	{
		if (apiKey.isEmpty())
			return;
		FlurryAgent.setCaptureUncaughtExceptions(true);
		FlurryAgent.init(activity, apiKey);
		FlurryAgent.setVersionName(appVersion);
	}
	
	public static void setPosition(float latitude, float longitude)
	{
		FlurryAgent.setLocation(latitude, longitude);
	}
	
	public static void setEvent(String eventString)
	{
		FlurryAgent.logEvent(eventString);
	}
	
	public static void setEvent(String eventString, String key1, String value1)
	{
		Map<String, String> parameterMap = new HashMap<String, String>();
		parameterMap.put(key1,  value1);
		
		FlurryAgent.logEvent(eventString, parameterMap);
	}
	
	public static void setEvent(String eventString, String key1, String value1, String key2, String value2)
	{
		Map<String, String> parameterMap = new HashMap<String, String>();
		parameterMap.put(key1,  value1);
		parameterMap.put(key2,  value2);
		
		FlurryAgent.logEvent(eventString, parameterMap);		
	}
	
	public static void setEvent(String eventString, String key1, String value1, String key2, String value2, String key3, String value3)
	{
		Map<String, String> parameterMap = new HashMap<String, String>();
		parameterMap.put(key1,  value1);
		parameterMap.put(key2,  value2);
		parameterMap.put(key3,  value3);
		
		FlurryAgent.logEvent(eventString, parameterMap);		
	}
	
	public static void beginTimedEvent(String eventString)
	{
		boolean isTimed = true;
		FlurryAgent.logEvent(eventString, isTimed);
	}
	
	public static void beginTimedEvent(String eventString, String key1, String value1)
	{
		boolean isTimed = true;
		Map<String, String> parameterMap = new HashMap<String, String>();
		parameterMap.put(key1,  value1);
		
		FlurryAgent.logEvent(eventString, parameterMap, isTimed);
	}
	
	public static void endTimedEvent(String eventString)
	{
		FlurryAgent.endTimedEvent(eventString);
	}
	
	public static void endTimedEvent(String eventString, String key1, String value1)
	{
		Map<String, String> parameterMap = new HashMap<String, String>();
		parameterMap.put(key1,  value1);
		
		FlurryAgent.endTimedEvent(eventString, parameterMap);
	}
}
