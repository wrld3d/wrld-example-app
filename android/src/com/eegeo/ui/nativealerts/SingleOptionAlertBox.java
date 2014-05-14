package com.eegeo.ui.nativealerts;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.util.Log;

public class SingleOptionAlertBox
{
	private static AlertDialog m_inputBox = null;
	
	public native static void callback(int ptr);
	
	public static void close()
	{
		if(m_inputBox!=null)
		{
			m_inputBox.dismiss();
			m_inputBox = null;
		}
	}
	
	public static void popUpBox(
			final Activity a,
			final String title,
			final String message,
			final int ptr)
    {
    	a.runOnUiThread(new Runnable()
    	{
    		public void run()
    		{
    	    	try
    	    	{
    	    		AlertDialog.Builder builder = new AlertDialog.Builder(a);
    	    		builder.setTitle(title);
    	    		builder.setMessage(message);
    	    		
    	    		// Set up the buttons
    	    		builder.setPositiveButton("OK", new DialogInterface.OnClickListener() { 
    	    		    @Override
    	    		    public void onClick(DialogInterface dialog, int which) {
    	    		    	callback(ptr);
    	    		    	m_inputBox = null;
    	    		    }
    	    		});

    	    		m_inputBox = builder.show();
    	    	}
    	    	catch (Exception e)
    	    	{
    	        	Log.v("InputBox", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
    	    	}    			
    		}
    	});
    }
}
