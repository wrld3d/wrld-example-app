package com.eegeo.web;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

public class UrlEncoder 
{
	public static String encodeQuery(String query) 
	{
		String result = "";
		
		try 
		{
			result = URLEncoder.encode(query, "utf-8");
		}
		catch (UnsupportedEncodingException e) 
		{
			result = "";
		}
		
		return result;
	}
}
