// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.entrypointinfrastructure;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.speech.RecognizerIntent;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.RelativeLayout;

import com.eegeo.helpers.IBackButtonListener;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.photos.PhotoIntentDispatcher;
import com.eegeo.runtimepermissions.RuntimePermissionDispatcher;
import com.eegeo.view.OnPauseListener;

public abstract class MainActivity extends Activity implements SurfaceHolder.Callback, INativeMessageRunner
{
    private PhotoIntentDispatcher m_photoIntentDispatcher;
    private RuntimePermissionDispatcher m_runtimePermissionDispatcher;
    private boolean m_touchEnabled;
    private LinkedList<OnPauseListener> m_onPauseListeners;
    private List<IBackButtonListener> m_backButtonListeners;

    private String tag = "VOICE_CONTROL_TEST";

    private static final int REQ_CODE_SPEECH_INPUT = 100;

    public MainActivity()
    {
        m_photoIntentDispatcher = new PhotoIntentDispatcher(this);
        m_runtimePermissionDispatcher = new RuntimePermissionDispatcher(this);
        m_touchEnabled = true;
        m_onPauseListeners = new LinkedList<OnPauseListener>();
        m_backButtonListeners = new ArrayList<IBackButtonListener>();
    }

    @Override
    public void onStart()
    {
        super.onStart();

        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT, "asking for voice authorisation");
        startActivityForResult(intent, REQ_CODE_SPEECH_INPUT);
    }

    public PhotoIntentDispatcher getPhotoIntentDispatcher()
    {
        return m_photoIntentDispatcher;
    }
    
    public RuntimePermissionDispatcher getRuntimePermissionDispatcher()
    {
        return m_runtimePermissionDispatcher;
    }

    // http://developer.android.com/guide/practices/screens_support.html#dips-pels
    // and http://stackoverflow.com/a/9904844
    public int pxAsDip(float px)
    {
        float density = getResources().getDisplayMetrics().density;
        int dip = (int)((px / density) + 0.5f);
        return dip;
    }

    public int dipAsPx(float dip)
    {
        float density = getResources().getDisplayMetrics().density;
        int px = (int)((dip * density) + 0.5f);
        return px;
    }

    public void dismissKeyboard(IBinder binder)
    {
        InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.hideSoftInputFromWindow(binder, 0);
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
    }
    
    public void recursiveDisableSplitMotionEvents(ViewGroup group)
    {
    	group.setMotionEventSplittingEnabled(false);
    	
    	for(int i = 0; i < group.getChildCount(); i++) 
    	{
    		View child = group.getChildAt(i);
    	
    		if(child instanceof ViewGroup) 
    		{
    			recursiveDisableSplitMotionEvents((ViewGroup)child);
    		}
    	}
    }
    
    public void setTouchExclusivity()
    {
    	final RelativeLayout uiRoot = (RelativeLayout)this.findViewById(R.id.ui_container);
    	recursiveDisableSplitMotionEvents((ViewGroup) uiRoot.getParent());
    }
    
    public void setTouchEnabled(final boolean touchEnabled)
    {
    	m_touchEnabled = touchEnabled;
    }

    public void addOnPauseListener(final OnPauseListener l)
    {
        m_onPauseListeners.add(l);
    }

    public void deleteOnPauseListener(final OnPauseListener l)
    {
        m_onPauseListeners.remove(l);
    }

    public void addBackButtonPressedListener(IBackButtonListener listener)
    {
        if (!m_backButtonListeners.contains(listener))
        {
            m_backButtonListeners.add(listener);
        }
    }

    public void removeBackButtonPressedListener(IBackButtonListener listener)
    {
        if (m_backButtonListeners.contains(listener))
        {
            m_backButtonListeners.remove(listener);
        }
    }

    public boolean checkLocalBackButtonListeners() {
        for (IBackButtonListener listener : m_backButtonListeners)
        {
            if (listener.onBackButtonPressed())
            {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent event)
    {
    	if(m_touchEnabled)
    	{
    		return super.dispatchTouchEvent(event);
    	}
    	return m_touchEnabled;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        switch (requestCode) {
            case PhotoIntentDispatcher.REQUEST_IMAGE_CAPTURE: case PhotoIntentDispatcher.SELECT_PHOTO_FROM_GALLERY: {
                m_photoIntentDispatcher.onActivityResult(requestCode, resultCode, data);
                break;
            }
            case REQ_CODE_SPEECH_INPUT: {
                if (resultCode == RESULT_OK && null != data) {

                    ArrayList<String> result = data
                            .getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                    Log.v(tag, "Recorded words: \""+result.get(0)+"\"");
                }
                break;
            }
        }
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        for (OnPauseListener l : m_onPauseListeners)
        {
            l.notifyOnPause();
        }
    }
    
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
    {
       m_runtimePermissionDispatcher.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    public abstract void dispatchRevealUiMessageToUiThreadFromNativeThread(final long nativeCallerPointer);

    public abstract void dispatchUiCreatedMessageToNativeThreadFromUiThread(final long nativeCallerPointer);

    public abstract void onScreenshotsCompleted();
}
