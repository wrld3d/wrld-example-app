package com.eegeo.options;

import java.util.Timer;
import java.util.TimerTask;

import android.os.SystemClock;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.mobileexampleapp.R;
import com.eegeo.entrypointinfrastructure.MainActivity;

public class OptionsCacheClearSubView 
{
    private MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private Runnable m_confirmationCallback = null;
    private boolean m_isDisplayed = false;
    private View m_confirmButton = null;
	private View m_cancelButton = null;
	private View m_closeButton = null;
	private View m_container_confirm = null;
	private View m_container_progress = null;
	private View m_spinner = null;
	private TextView m_content = null;
    private Timer m_timer = new Timer();
    private long m_cacheClearDialogMinimumEndTimeMilliseconds;
    private boolean m_returnToOptions = true;

    private enum Containers
	{
		CONFIRMATION, PROGRESS, DONE
	}

    public OptionsCacheClearSubView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
        m_uiRoot = (RelativeLayout)activity.findViewById(R.id.ui_container);
        m_view = activity.getLayoutInflater().inflate(R.layout.cache_clear_ceremony_layout, m_uiRoot, false);
        m_uiRoot.addView(m_view);
        
        m_confirmButton = m_view.findViewById(R.id.cache_clear_ceremony_confirm_button);
		m_cancelButton = m_view.findViewById(R.id.cache_clear_ceremony_cancel_button);
		m_closeButton = m_view.findViewById(R.id.cache_clear_ceremony_close_button);
		m_container_confirm = m_view.findViewById(R.id.cache_clear_ceremony_view_container);
		m_container_progress = m_view.findViewById(R.id.cache_clear_ceremony_progress_container);
		m_spinner = m_view.findViewById(R.id.cache_clear_ceremony_progress_spinner);
        m_content = (TextView) m_view.findViewById(R.id.cache_clear_ceremony_progress_message);

        m_confirmButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
		        handleConfirmClicked();
			}
		});

        View.OnClickListener closeListener = new View.OnClickListener() {
            public void onClick(View arg0) {
                resetState();
                m_uiRoot.removeView(m_view);
                if (!m_returnToOptions)
                {
                    OptionsViewJniMethods.CloseButtonSelected(m_nativeCallerPointer);
                }
            }
        };

		m_cancelButton.setOnClickListener(closeListener);
		m_closeButton.setOnClickListener(closeListener);

		setContainer(Containers.CONFIRMATION);

        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
        
        resetState();
    }

	private void resetState()
	{
		m_isDisplayed = false;
		m_confirmationCallback = null;

		m_view.setVisibility(View.GONE);
	}

    public void displayWarning(Runnable confirmationCallback)
    {
    	assert(confirmationCallback != null);
    	assert(m_confirmationCallback == null);
    	assert(!m_isDisplayed);
    	
    	m_isDisplayed = true;
    	m_confirmationCallback = confirmationCallback;

        m_view.setVisibility(View.VISIBLE);
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
    	setContainer(Containers.DONE);
	}

    private void setContainer(Containers container)
    {
        switch (container)
        {
            case CONFIRMATION:
                m_closeButton.setVisibility(View.INVISIBLE);
                m_container_confirm.setVisibility(View.VISIBLE);
                m_container_progress.setVisibility(View.INVISIBLE);

                m_returnToOptions = true;
                break;

            case PROGRESS:
                m_closeButton.setVisibility(View.INVISIBLE);
                m_container_confirm.setVisibility(View.INVISIBLE);
                m_container_progress.setVisibility(View.VISIBLE);

                m_spinner.setVisibility(View.VISIBLE);
                m_content.setText(R.string.cache_clear_working);
                break;

            case DONE:

                m_closeButton.setVisibility(View.VISIBLE);
                m_container_confirm.setVisibility(View.INVISIBLE);
                m_container_progress.setVisibility(View.VISIBLE);

                m_returnToOptions = false;
                m_spinner.setVisibility(View.INVISIBLE);
                m_content.setText(R.string.cache_clear_done);
                break;
        }
    }

    private void handleConfirmClicked()
    {
    	assert(m_isDisplayed);

		setContainer(Containers.PROGRESS);

        final long minimumAsyncDelayMilliseconds = 3000;
        m_cacheClearDialogMinimumEndTimeMilliseconds = SystemClock.elapsedRealtime() + minimumAsyncDelayMilliseconds;

        m_confirmationCallback.run();
    }
}
