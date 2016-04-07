// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.modalbackground;

import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class ModalBackgroundView implements View.OnClickListener
{
    private MainActivity m_activity = null;
    private View m_view = null;
    protected long m_nativeCallerPointer;

    final float m_stateChangeAnimationTimeSeconds = 0.2f;

    public ModalBackgroundView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.modal_background_layout, uiRoot, false);
		m_view.setOnClickListener(this);
      
        m_view.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{ 
				m_view.setClickable(false);
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

    public void animateToFullyInactive()
    {
        m_view.setClickable(false);
    }

    public void animateToFullyActive()
    {
        m_view.setClickable(true);
    }

    public void animateToIntermediateActivityState(final float openState)
    {
        m_view.setClickable(openState > 0.f);
    }
    
    @Override
    public void onClick(View view)
    {
    	ModalBackgroundViewJniMethods.HandleViewTapped(m_nativeCallerPointer);
    }
}
