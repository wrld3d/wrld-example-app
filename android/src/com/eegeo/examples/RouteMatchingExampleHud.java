package com.eegeo.examples;

import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.RelativeLayout;

import com.eegeo.MainActivity;
import com.eegeo.R;

public class RouteMatchingExampleHud 
{
	private MainActivity m_activity;
	private View m_view;
    
    public static native void ToggleRouteMatching(long nativeCallerPointer);
    
	public RouteMatchingExampleHud(MainActivity activity, long nativeCallerPointer)
    {
    	m_activity = activity;
    	m_view = null;

    	createHud(nativeCallerPointer);
    }
    
    private void createHud(final long nativeCallerPointer)
    {	
    	m_activity.runOnUiThread(new Runnable()
	    {
	        public void run()
	        {
	            try
	            {
	            	final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
	            	m_view = m_activity.getLayoutInflater().inflate(R.layout.route_matching_menu_layout, uiRoot, false);

	            	final Button toggleRouteMatching = (Button)m_view.findViewById(R.id.toggle_match);
	           	
	            	toggleRouteMatching.setOnClickListener(new OnClickListener() {
	                    @Override
	                    public void onClick(View v) {
	                    	ToggleRouteMatching(nativeCallerPointer);
	                    }
	                });
	            	
	            	uiRoot.addView(m_view);
	            }
	            catch (Exception e)
	            {
	                Log.v("RouteMatchingExampleHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
	            }                            
	        }
	    });
    }
    
    public void removeHud()
    {
    	m_activity.runOnUiThread(new Runnable()
	    {
	        public void run()
	        {
	            try
	            {
	            	final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
                	uiRoot.removeView(m_view);
                	m_view = null;
	            }
	            catch (Exception e)
	            {
	                //Log.v("RouteSimulationExampleHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
	            }                            
	        }
	    });
    }
}
