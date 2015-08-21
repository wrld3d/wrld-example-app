// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.modalbackground;

import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.ProjectSwallowApp.R;
import com.eegeo.entrypointinfrastructure.MainActivity;

public class ModalBackgroundView
{
    private MainActivity m_activity = null;
    private View m_view = null;

    final float m_stateChangeAnimationTimeSeconds = 0.2f;

    public ModalBackgroundView(MainActivity activity)
    {
        m_activity = activity;

        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.modal_background_layout, uiRoot, false);
        m_view.setClickable(false);

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
}
