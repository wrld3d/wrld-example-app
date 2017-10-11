// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.mypincreation;

import android.animation.Animator;
import android.animation.Animator.AnimatorListener;
import android.view.View;
import android.view.ViewPropertyAnimator;
import android.widget.Button;
import android.widget.RelativeLayout;

import com.eegeo.ProjectSwallowApp.R;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.ui.IAnimatedView;
import com.eegeo.ui.IViewAnimator;
import com.eegeo.ui.ViewAnimator;

public class MyPinCreationButtonView implements View.OnClickListener, IAnimatedView
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    protected Button m_view = null;

    private final long stateChangeAnimationTimeMilliseconds = 200;
    private IViewAnimator m_viewAnimator;

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

        m_viewAnimator = new ViewAnimator(this, m_view);
        m_viewAnimator.registerLayoutChangeListener();
        
        uiRoot.addView(m_view);
    }

    public void ViewLayoutChanged() {
        final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);

        final float screenWidth = uiRoot.getWidth();
        final float screenHeight = uiRoot.getHeight();

        final float viewHeight = m_view.getHeight();

        m_viewAnimator.setActivePos((screenHeight - viewHeight) - m_activity.dipAsPx(8.f));
        m_viewAnimator.setInactivePos(screenHeight + viewHeight);

        m_view.setX((screenWidth * 0.5f) + m_activity.dipAsPx(48));
        m_view.setY(screenHeight + viewHeight);
    }

    @Override
    public void onClick(View view)
    {
        MyPinCreationJniMethods.StartButtonPressed(m_nativeCallerPointer);
    }

    public void animateToActive()
    {
        m_viewAnimator.animateToActive(stateChangeAnimationTimeMilliseconds);
    }

    public void animateToInactive()
    {
        m_viewAnimator.animateToInactive(stateChangeAnimationTimeMilliseconds);
    }

    public void animateToIntermediateOnScreenState(final float onScreenState)
    {
        m_viewAnimator.animateToOnScreenState(onScreenState);
    }
}

