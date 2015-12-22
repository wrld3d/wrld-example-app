// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.web;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.net.URLDecoder;

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
    
    public static String decodeQuery(String query) 
	{
		String result = "";
		
		try 
		{
			result = URLDecoder.decode(query, "utf-8");
		}
		catch (UnsupportedEncodingException e) 
		{
			result = "";
		}
		
		return result;
	}

}
