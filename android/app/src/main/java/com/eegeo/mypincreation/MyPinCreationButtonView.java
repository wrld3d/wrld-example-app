// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.mypincreation;

import android.animation.Animator;
import android.animation.Animator.AnimatorListener;
import android.view.View;
import android.view.ViewPropertyAnimator;
import android.widget.Button;
import android.widget.RelativeLayout;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class MyPinCreationButtonView implements View.OnClickListener, AnimatorListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    protected Button m_view = null;

    private ViewPropertyAnimator m_animator = null;
    private float m_yPosActive;
    private float m_yPosInactive;

    private final long stateChangeAnimationTimeMilliseconds = 200;

    public MyPinCreationButtonView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

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
        m_view = (Button)m_activity.getLayoutInflater().inflate(R.layout.poi_creation_button_layout, uiRoot, false);

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

		        m_yPosActive = (screenHeight - viewHeight) - m_activity.dipAsPx(8.f);
		        m_yPosInactive = screenHeight + viewHeight;
		                
		        m_view.setX((screenWidth * 0.5f) + m_activity.dipAsPx(48));
		        m_view.setY(m_yPosInactive);
		        m_view.removeOnLayoutChangeListener(this);
			}
        });
        
        uiRoot.addView(m_view);
    }

    @Override
    public void onClick(View view)
    {
        MyPinCreationJniMethods.StartButtonPressed(m_nativeCallerPointer);
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
        if(m_animator != null)
        {
            m_animator.cancel();
            m_animator = null;
        }

        m_animator = m_view.animate()
                     .y(yAsPx)
                     .setDuration(stateChangeAnimationTimeMilliseconds);
        m_animator.setListener(this);
    }

    public void animateToIntermediateOnScreenState(final float onScreenState)
    {
        if(m_animator != null)
        {
            m_animator.cancel();
            m_animator = null;
        }

        int viewYPx = (int)m_view.getY();
        int newYPx = (int)(m_yPosInactive + (int)(((m_yPosActive - m_yPosInactive) * onScreenState) + 0.5f));

        if(viewYPx != newYPx)
        {
            m_view.setY(newYPx);
        }
    }

    @Override
    public void onAnimationCancel(Animator arg0)
    {
        m_animator = null;
    }

    @Override
    public void onAnimationEnd(Animator arg0)
    {
        m_animator = null;
    }

    @Override
    public void onAnimationRepeat(Animator arg0)
    {
    }

    @Override
    public void onAnimationStart(Animator arg0)
    {
    }
}

