// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

package com.eegeo.ui;

import android.animation.Animator;
import android.view.View;
import android.view.ViewPropertyAnimator;

public class ViewAnimator implements IViewAnimator, Animator.AnimatorListener {

    private IAnimatedView m_animatedView;
    private View m_view;

    private float m_yPosActive;
    private float m_yPosInactive;

    private boolean m_viewReady;
    private ViewPropertyAnimator m_animator = null;

    private ViewReadyCallbackAnimation m_animationOnReady;

    public interface ViewReadyCallbackAnimation {
        void invoke();
    }

    public ViewAnimator(IAnimatedView startupButton, View view)
    {
        m_animatedView = startupButton;
        m_view = view;
    }

    public void registerLayoutChangeListener(){
        m_view.addOnLayoutChangeListener(new View.OnLayoutChangeListener() {
            @Override
            public void onLayoutChange(View v, int left, int top, int right,
                                       int bottom, int oldLeft, int oldTop, int oldRight,
                                       int oldBottom) {
            m_view.removeOnLayoutChangeListener(this);
            m_viewReady = true;

            m_animatedView.ViewLayoutChanged();

            if(m_animationOnReady != null){
                m_animationOnReady.invoke();
            }
            }
        });
    }

    public void animateToActive(final long durationInMs)
    {
        if(m_viewReady){
            doAnimateToY(m_yPosActive, durationInMs);
        }
        else{
            m_animationOnReady = new ViewReadyCallbackAnimation() {
                @Override
                public void invoke() {
                    doAnimateToY(m_yPosActive, durationInMs);
                }
            };
        }
    }

    public void animateToInactive(final long durationInMs)
    {
        if(m_viewReady){
            doAnimateToY(m_yPosInactive, durationInMs);
        }
        else{
            m_animationOnReady = new ViewReadyCallbackAnimation() {
                @Override
                public void invoke() {
                    doAnimateToY(m_yPosInactive, durationInMs);
                }
            };
        }
    }

    public void animateToOnScreenState(final float onScreenState)
    {
        if(m_animator != null)
        {
            m_animator.cancel();
            m_animator = null;
        }

        int newYPx = (int) (m_yPosInactive + (int) (((m_yPosActive - m_yPosInactive) * onScreenState) + 0.5f));

        if(m_viewReady) {
            int viewYPx = (int) m_view.getY();

            if (viewYPx != newYPx) {
                m_view.setY(newYPx);
            }
        }
    }

    public void setActivePos(final float y){
        m_yPosActive = y;
    }

    public void setInactivePos(final float y){
        m_yPosInactive = y;
    }

    private void doAnimateToY(float yAsPx, long durationInMs) {

        if(m_animator != null)
        {
            m_animator.cancel();
            m_animator = null;
        }

        m_animator = m_view.animate()
                .y(yAsPx)
                .setDuration(durationInMs);
        m_animator.setListener(this);
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
