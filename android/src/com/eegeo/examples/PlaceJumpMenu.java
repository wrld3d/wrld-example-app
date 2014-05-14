package com.eegeo.examples;

import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.Spinner;

import com.eegeo.MainActivity;
import com.eegeo.R;

//this is the java companion type to native ShowJavaPlaceJumpUIExample
//
public class PlaceJumpMenu 
{
	private MainActivity m_activity;
	private View m_view;
    
    public static native void visitLocation(long nativeCallerPointer, String location);
    
	public PlaceJumpMenu(MainActivity activity)
    {
    	m_activity = activity;
    	m_view = null;
    }
    
    public void showVisitMenu(final long nativeCallerPointer)
    {	
    	m_activity.runOnUiThread(new Runnable()
	    {
	        public void run()
	        {
	            try
	            {
	            	final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
	            	m_view = m_activity.getLayoutInflater().inflate(R.layout.ui_menu, uiRoot, false);
	            	
	            	final Spinner spinner = (Spinner)m_view.findViewById(R.id.places);
	            
	            	String items[] = new String[5];
	            	items[0] = "NYC";
	            	items[1] = "London";
	            	items[2] = "SF";
	            	items[3] = "Kyoto";
	            	items[4] = "Melbourne";
	                ArrayAdapter<String> adapter = new ArrayAdapter<String>(m_activity, android.R.layout.simple_spinner_item, items);
	            	spinner.setAdapter(adapter);
	            	
	            	final Button close = (Button)m_view.findViewById(R.id.close);
	            	final Button visit = (Button)m_view.findViewById(R.id.visit);
	            	
	            	close.setOnClickListener(new OnClickListener() {
	                    @Override
	                    public void onClick(View v) {
	                    	close.setOnClickListener(null);
	                    	visit.setOnClickListener(null);
	                    	uiRoot.removeView(m_view);
	                    }
	                });
	            	
	            	visit.setOnClickListener(new OnClickListener() {
	                    @Override
	                    public void onClick(View v) {
	                    	String selection = (String)spinner.getSelectedItem();
	                    	visitLocation(nativeCallerPointer, selection);
	                    }
	                });
	            	
	            	uiRoot.addView(m_view);
	            }
	            catch (Exception e)
	            {
	                Log.v("PlaceJumpMenu", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
	            }                            
	        }
	    });
    }
    
    public void removeVisitMenu()
    {
    	m_activity.runOnUiThread(new Runnable()
	    {
	        public void run()
	        {
	            try
	            {
	            	final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
                	uiRoot.removeView(m_view);
	            }
	            catch (Exception e)
	            {
	                Log.v("PlaceJumpMenu", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
	            }                            
	        }
	    });
    }
}
