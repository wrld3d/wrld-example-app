// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

package com.eegeo.ui;

public interface IViewAnimator {
    void registerLayoutChangeListener();
    void setActivePos(final float y);
    void setInactivePos(final float y);
    void animateToActive(final long durationInMs);
    void animateToInactive(final long durationInMs);
    void animateToOnScreenState(final float onScreenState);
}
