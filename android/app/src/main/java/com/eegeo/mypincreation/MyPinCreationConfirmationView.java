// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.mypincreation;

import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class MyPinCreationConfirmationView implements View.OnClickListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    protected View m_view = null;
    protected ImageView m_closeButton = null;
    protected ImageView m_confirmButton = null;

    private float m_yPosActive;
    private float m_yPosInactive;
    private boolean m_canProcessButtons;

    private final long m_stateChangeAnimationTimeMilliseconds = 200;

    public MyPinCreationConfirmationView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
        m_canProcessButtons = true;

        createView();
    }

    public void destroy()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        uiRoot.removeView(m_view);
        m_view = null;
    }

    private void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.poi_creation_confirmation_layout, uiRoot, false);

        m_closeButton = (ImageView)m_view.findViewById(R.id.poi_creation_confirmation_close_button);
        m_closeButton.setOnClickListener(this);
        m_confirmButton = (ImageView)m_view.findViewById(R.id.poi_creation_confirmation_ok_button);
        m_confirmButton.setOnClickListener(this);
        m_view.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{   
		        final float screenHeight = uiRoot.getHeight();
		        final float screenWidth = uiRoot.getWidth();
		        final float controlWidth = m_view.getWidth();
		        final float controlHeight = m_view.getHeight();
		        
		        m_yPosActive = screenHeight - controlHeight;
		        m_yPosInactive = screenHeight;
		
		        m_view.setX((screenWidth * 0.5f) - (controlWidth * 0.5f));
		        m_view.setY(m_yPosInactive);
		        m_view.removeOnLayoutChangeListener(this);
			}
        });
        
        uiRoot.addView(m_view);
    }

    public void animateToActive()
    {
    	m_canProcessButtons = true;
        animateViewToY((int)m_yPosActive);
    }

    public void animateToInactive()
    {
        animateViewToY((int)m_yPosInactive);
    }

    protected void animateViewToY(final int yAsPx)
    {
        m_view.animate()
        .y(yAsPx)
        .setDuration(m_stateChangeAnimationTimeMilliseconds);
    }

    public void animateToIntermediateOnScreenState(final float onScreenState)
    {
        int viewXPx = (int)m_view.getX();
        int newXPx = (int)(m_yPosInactive + (int)(((m_yPosActive - m_yPosInactive) * onScreenState) + 0.5f));

        if(viewXPx != newXPx)
        {
            m_view.setY(newXPx);
        }
        
        if(onScreenState == 1.0f)
        {
        	m_canProcessButtons = true;
        }
    }

    @Override
    public void onClick(final View view)
    {
    	if(!m_canProcessButtons)
    	{
    		return;
    	}
    	
        if(view == m_closeButton)
        {
            MyPinCreationJniMethods.ConfirmationCancelButtonPressed(m_nativeCallerPointer);
            
        }
        else if(view == m_confirmButton)
        {
            MyPinCreationJniMethods.ConfirmationOkButtonPressed(m_nativeCallerPointer);
        }
        
        m_canProcessButtons = false;
    }
}
