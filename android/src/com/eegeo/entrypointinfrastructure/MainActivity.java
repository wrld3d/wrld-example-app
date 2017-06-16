// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.entrypointinfrastructure;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
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

    public MainActivity()
    {
        m_photoIntentDispatcher = new PhotoIntentDispatcher(this);
        m_runtimePermissionDispatcher = new RuntimePermissionDispatcher(this);
        m_touchEnabled = true;
        m_onPauseListeners = new LinkedList<OnPauseListener>();
        m_backButtonListeners = new ArrayList<IBackButtonListener>();
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
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        m_photoIntentDispatcher.onActivityResult(requestCode, resultCode, data);
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
