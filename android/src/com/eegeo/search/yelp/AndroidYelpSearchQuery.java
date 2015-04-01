//Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.search.yelp;

import java.util.Locale;

import org.scribe.builder.ServiceBuilder;
import org.scribe.model.OAuthRequest;
import org.scribe.model.Response;
import org.scribe.model.Token;
import org.scribe.model.Verb;
import org.scribe.oauth.OAuthService;

import com.eegeo.entrypointinfrastructure.MainActivity;

import android.os.AsyncTask;

public class AndroidYelpSearchQuery 
{
	private static final String API_HOST = "api.yelp.com";
	private static final String SEARCH_PATH = "/v2/search";
	private static final String BUSINESS_PATH = "/v2/business/";
	private static final int SEARCH_LIMIT = 20;
	private static final float MAX_RADIUS_METRES = 40000.f;
	  
	private MainActivity m_mainActivity;
    private long m_nativeCallerPointer;
    private OAuthService m_service;
    private Token m_accessToken;
    private PerformRequestTask m_performRequestTask;
    
    public AndroidYelpSearchQuery(
    		MainActivity activity,
    		String yelpConsumerKey,
    		String yelpConsumerSecret,
    		String yelpOAuthToken,
    		String yelpOAuthTokenSecret,
    		long nativeCallerPointer)
    {
    	m_mainActivity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
        
        m_service = new ServiceBuilder()
        	.provider(TwoStepOAuth.class)
        	.apiKey(yelpConsumerKey)
        	.apiSecret(yelpConsumerSecret).build();
        
        m_accessToken = new Token(yelpOAuthToken, yelpOAuthTokenSecret);
    }

    public void dispatch(
    		String searchQueryInput,
    		boolean isCategory,
    		double latitudeDegrees,
    		double longitudeDegrees,
    		float radius)
    {
        m_performRequestTask = new PerformRequestTask(false);
        
        String searchLocationStr = String.format(Locale.getDefault(), "%f,%f", latitudeDegrees, longitudeDegrees);
        int radiusFilter = (int)(radius > MAX_RADIUS_METRES || !isCategory ? MAX_RADIUS_METRES : radius);
        String radiusFilterStr = Integer.toString(radiusFilter);
        String categoryFilterStr = "";
        String searchQueryStr = "";
        
        if(isCategory)
        {
            categoryFilterStr = searchQueryInput;
        }
        else
        {
            searchQueryStr = searchQueryInput;
        }
        
    	OAuthRequest request = new OAuthRequest(Verb.GET, "http://" + API_HOST + SEARCH_PATH);
        request.addQuerystringParameter("term", searchQueryStr);
        request.addQuerystringParameter("category_filter", categoryFilterStr);
        request.addQuerystringParameter("ll", searchLocationStr);
        request.addQuerystringParameter("radius_filter", radiusFilterStr);
        request.addQuerystringParameter("limit", String.valueOf(SEARCH_LIMIT));
        m_performRequestTask.execute(request);
    }

    public void dispatchBusinessQuery(String searchQueryInput)
    {
        m_performRequestTask = new PerformRequestTask(true);
    	OAuthRequest request = new OAuthRequest(Verb.GET, "http://" + API_HOST + BUSINESS_PATH + searchQueryInput);
        m_performRequestTask.execute(request);
    }
    
    public void cancel()
    {
    	m_performRequestTask.cancel(true);
    }
    
    private void handleQueryResponse(boolean success, boolean isBusiness, String searchResponseJSON)
    {
    	if(isBusiness)
    	{
    		AndroidYelpSearchQueryJni.BusinessQueryComplete(m_nativeCallerPointer, success, searchResponseJSON);	
    	}
    	else
    	{
    		AndroidYelpSearchQueryJni.SearchQueryComplete(m_nativeCallerPointer, success, searchResponseJSON);
    	}
    }
    
    private class PerformRequestTask extends AsyncTask<OAuthRequest, Void, String> 
    {
    	boolean m_isBusiness;
    	boolean m_success;
    	
    	public PerformRequestTask(boolean isBusiness)
    	{
    		m_success = true;
    		m_isBusiness = isBusiness;
    	}
    	
    	@Override
    	protected String doInBackground(OAuthRequest... requests) 
    	{
    		try
    		{
	    		OAuthRequest request = requests[0];
	            m_service.signRequest(m_accessToken, request);
	            Response response = request.send();
	            return response.getBody();
    		}
    		catch(Exception e)
    		{
    			m_success = false;
	            return "";
    		}
    	}
    	
    	@Override
    	protected void onPostExecute(final String searchResponseJSON) 
    	{
    		m_mainActivity.runOnNativeThread(new Runnable() {
				public void run() {
		    		handleQueryResponse(m_success, m_isBusiness, searchResponseJSON);
				}
    		});
    	}

    	@Override
    	protected void onCancelled(final String searchResponseJSON) 
    	{
    		m_mainActivity.runOnNativeThread(new Runnable() {
				public void run() {
		    		handleQueryResponse(false, m_isBusiness, "");
				}
    		});
    	}
    }
}

