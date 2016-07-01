// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.flattenbutton;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.view.View;
import android.widget.RelativeLayout;
import android.widget.ToggleButton;

public class FlattenButtonView implements View.OnClickListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    protected ToggleButton m_view = null;

    private float m_yPosActive;
    private float m_yPosInactive;

    private final long m_stateChangeAnimationTimeMilliseconds = 200;

    public FlattenButtonView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = (ToggleButton)m_activity.getLayoutInflater().inflate(R.layout.flatten_button_layout, uiRoot, false);

        m_view.setOnClickListener(this);
        
        m_view.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{   
		        final float screenHeight = uiRoot.getHeight();
		        final float screenWidth = uiRoot.getWidth();
		        final float viewHeight = m_view.getHeight();
		        final float viewWidth = m_view.getWidth();

		        m_yPosActive = (screenHeight - viewHeight) - m_activity.dipAsPx(8.f);
		        m_yPosInactive = screenHeight + viewHeight;
		                
		        m_view.setX(((screenWidth * 0.5f) - (viewWidth)) - m_activity.dipAsPx(48));
		        m_view.setY(m_yPosInactive);
		        m_view.removeOnLayoutChangeListener(this);
			}
        });
        
        uiRoot.addView(m_view);
    }

    public void destroy()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        uiRoot.removeView(m_view);
        m_view = null;
    }

    public void updateViewStateBasedOnFlattening(final boolean isFlattened)
    {
        m_view.setChecked(isFlattened);
    }

    @Override
    public void onClick(View view)
    {
        FlattenButtonViewJniMethods.OnToggle(m_nativeCallerPointer, ((ToggleButton)m_view).isChecked());
    }

    public void animateToActive()
    {
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
        int viewYPx = (int)m_view.getY();
        int newYPx = (int)(m_yPosInactive + (int)(((m_yPosActive - m_yPosInactive) * onScreenState) + 0.5f));

        if(viewYPx != newYPx)
        {
            m_view.setY(newYPx);
        }
    }
    
    public void setViewEnabled(final boolean enabled)
    {
    	m_view.setEnabled(enabled);
		if(!enabled) 
		{
			m_view.setAlpha(0.5f);
		}
		else
		{
			m_view.setAlpha(1.0f);
		}
    }
}
