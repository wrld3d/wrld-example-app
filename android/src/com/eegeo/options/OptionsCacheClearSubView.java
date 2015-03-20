package com.eegeo.options;

import java.util.Timer;
import java.util.TimerTask;

import android.os.SystemClock;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class OptionsCacheClearSubView 
{
	private MainActivity m_activity = null;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private Runnable m_confirmationCallback = null;
    private boolean m_isDisplayed = false;
    private View m_confirmButton = null;
    private View m_closeButton = null;
    private ProgressBar m_spinner = null;
    private TextView m_title = null;
    private TextView m_content = null;
    private Timer m_timer = new Timer();
    private long m_cacheClearDialogMinimumEndTimeMilliseconds;
    
    public OptionsCacheClearSubView(MainActivity activity)
    {
    	m_activity = activity;
        m_uiRoot = (RelativeLayout)activity.findViewById(R.id.ui_container);
        m_view = activity.getLayoutInflater().inflate(R.layout.cache_clear_ceremony_layout, m_uiRoot, false);
        m_uiRoot.addView(m_view);
        
        m_confirmButton = m_view.findViewById(R.id.cache_clear_ceremony_confirm_button);
        m_closeButton = m_view.findViewById(R.id.cache_clear_ceremony_close_button);
        m_spinner = (ProgressBar) m_view.findViewById(R.id.cache_clear_ceremony_view_spinner);
        m_title = (TextView) m_view.findViewById(R.id.cache_clear_ceremony_view_title);
        m_content = (TextView) m_view.findViewById(R.id.cache_clear_ceremony_view_message);

        m_confirmButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
		        handleConfirmClicked();
			}
		});

        m_closeButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
		        resetState();
		        m_uiRoot.removeView(m_view);
			}
		});
        
        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
        
        resetState();
    }
    
    public void displayWarning(Runnable confirmationCallback)
    {
    	assert(confirmationCallback != null);
    	assert(m_confirmationCallback == null);
    	assert(!m_isDisplayed);
    	
    	m_isDisplayed = true;
    	m_confirmationCallback = confirmationCallback;

        m_view.setVisibility(View.VISIBLE);

        m_title.setText("Warning");
        m_content.setText("Are you sure you want to remove all stored data?");
    }
    
    public void concludeCeremony()
    {
    	assert(m_isDisplayed);

        final long nowMilliseconds = SystemClock.elapsedRealtime();
        final long remainingIntervalUntilEndTimeMilliseconds = m_cacheClearDialogMinimumEndTimeMilliseconds - nowMilliseconds;
        
        if(remainingIntervalUntilEndTimeMilliseconds <= 0)
        {
        	closeAsyncCacheClearDialog();
        }
        else
        {
        	m_timer.schedule(new TimerTask(){
        		public void run (){
        			m_activity.runOnUiThread(new Runnable(){
        				public void run (){
        		        	closeAsyncCacheClearDialog();
        				}
        			});
        		}
        	}, remainingIntervalUntilEndTimeMilliseconds);
        }
    }
    
    private void closeAsyncCacheClearDialog()
    {
        m_content.setText("Map data deleted from device");
        m_closeButton.setVisibility(View.VISIBLE);
        m_spinner.setVisibility(View.INVISIBLE);
    }
    
    private void resetState()
    {   
        m_isDisplayed = false;
        m_confirmationCallback = null;
        m_spinner.setVisibility(View.INVISIBLE);
        m_confirmButton.setVisibility(View.VISIBLE);
        m_closeButton.setVisibility(View.VISIBLE);
        m_view.setVisibility(View.GONE);
    }
    
    private void handleConfirmClicked()
    {
    	assert(m_isDisplayed);
    	
        m_confirmButton.setVisibility(View.GONE);
        m_closeButton.setVisibility(View.GONE);
        m_spinner.setVisibility(View.VISIBLE);
        m_title.setText("Remove Stored Data");
        m_content.setText("Please wait, this may take a while...");

        final long minimumAsyncDelayMilliseconds = 3000;
        m_cacheClearDialogMinimumEndTimeMilliseconds = SystemClock.elapsedRealtime() + minimumAsyncDelayMilliseconds;

        m_confirmationCallback.run();
    }
}
