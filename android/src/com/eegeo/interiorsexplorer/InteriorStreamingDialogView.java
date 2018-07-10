// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
package com.eegeo.interiorsexplorer;

import android.support.v4.view.ViewCompat;
import android.view.View;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.LinearInterpolator;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class InteriorStreamingDialogView
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;

    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private LinearLayout m_dialogViewContainer = null;
    private ImageView m_streamingDialogSpinner = null;
    private ImageView m_streamingDialogLoaded = null;

    private AlphaAnimation m_fadeIn = fadeIn();
    private AlphaAnimation m_fadeOut = fadeOut();
    private RotateAnimation m_rotate = rotate();


    public InteriorStreamingDialogView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);

        m_view = m_activity.getLayoutInflater().inflate(R.layout.interior_streaming_dialog_layout, m_uiRoot, false);
        m_dialogViewContainer = (LinearLayout)m_view.findViewById(R.id.interior_streaming_dialog_view_container);
        m_streamingDialogSpinner = (ImageView)m_view.findViewById(R.id.streaming_dialog_spinner);
        m_streamingDialogLoaded = (ImageView)m_view.findViewById(R.id.streaming_dialog_loaded);

        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);

        if (!m_activity.getResources().getBoolean(R.bool.isPhone))
        {
            m_dialogViewContainer.getLayoutParams().width = 638;
        }

        ViewCompat.setTranslationZ(m_view, 1.0f);
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void showInteriorStreamingDialogView()
    {
        m_view.startAnimation(m_fadeIn);
        m_view.setVisibility(View.VISIBLE);

        m_streamingDialogSpinner.startAnimation(m_rotate);
        m_streamingDialogSpinner.setVisibility(View.VISIBLE);

        m_streamingDialogLoaded.setVisibility(View.GONE);

        m_view.requestFocus();
    }

    public void hideInteriorStreamingDialogView()
    {
        m_view.startAnimation(m_fadeOut);

        m_streamingDialogSpinner.setVisibility(View.GONE);
        m_rotate.cancel();
        m_rotate.reset();

        m_streamingDialogLoaded.setVisibility(View.VISIBLE);
    }

    private AlphaAnimation fadeIn()
    {
        AlphaAnimation fade = new AlphaAnimation(0.0f, 1.0f);
        fade.setDuration(500);

        return fade;
    }

    private AlphaAnimation fadeOut()
    {
        AlphaAnimation fade = new AlphaAnimation(1.0f, 0.0f);
        fade.setDuration(500);
        fade.setStartOffset(2000);
        fade.setAnimationListener(new Animation.AnimationListener(){
            @Override
            public void onAnimationStart(Animation animation)
            {
            }
            @Override
            public void onAnimationRepeat(Animation animation)
            {
            }
            @Override
            public void onAnimationEnd(Animation animation) {
                m_view.setVisibility(View.GONE);
            }
        });

        return fade;
    }

    private RotateAnimation rotate()
    {
        RotateAnimation rotate = new RotateAnimation(0, 360,
                Animation.RELATIVE_TO_SELF, 0.5f,
                Animation.RELATIVE_TO_SELF, 0.5f);
        rotate.setRepeatCount(Animation.INFINITE);
        rotate.setDuration(2000);
        rotate.setInterpolator(new LinearInterpolator());

        return rotate;
    }
}
