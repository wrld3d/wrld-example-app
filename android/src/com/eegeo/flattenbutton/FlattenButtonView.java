// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.flattenbutton;

import com.eegeo.ProjectSwallowApp.R;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.ui.IAnimatedView;
import com.eegeo.ui.IViewAnimator;
import com.eegeo.ui.ViewAnimator;

import android.view.View;
import android.widget.RelativeLayout;
import android.widget.ToggleButton;

public class FlattenButtonView implements View.OnClickListener, IAnimatedView
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    protected ToggleButton m_view = null;
    private IViewAnimator m_viewAnimator;

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

        m_viewAnimator = new ViewAnimator(this, m_view);
        m_viewAnimator.registerLayoutChangeListener();
        
        uiRoot.addView(m_view);
    }

    public void ViewLayoutChanged() {
        final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);

        final float screenWidth = uiRoot.getWidth();
        final float screenHeight = uiRoot.getHeight();

        final float viewWidth = m_view.getWidth();
        final float viewHeight = m_view.getHeight();

        m_viewAnimator.setActivePos((screenHeight - viewHeight) - m_activity.dipAsPx(8.f));
        m_viewAnimator.setInactivePos(screenHeight + viewHeight);

        m_view.setX(((screenWidth * 0.5f) - (viewWidth)) - m_activity.dipAsPx(48));
        m_view.setY(screenHeight + viewHeight);
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
        m_viewAnimator.animateToActive(m_stateChangeAnimationTimeMilliseconds);
    }

    public void animateToInactive()
    {
        m_viewAnimator.animateToInactive(m_stateChangeAnimationTimeMilliseconds);
    }

    public void animateToIntermediateOnScreenState(final float onScreenState)
    {
        m_viewAnimator.animateToOnScreenState(onScreenState);
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
