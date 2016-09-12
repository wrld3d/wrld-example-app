package com.eegeo.searchmenu;

import com.eegeo.animation.ReversibleAnimatorSet;
import com.eegeo.animation.ReversibleValueAnimator;
import com.eegeo.animation.updatelisteners.ViewScaleYAnimatorUpdateListener;
import com.eegeo.menu.MenuListAnimationConstants;

import android.animation.AnimatorListenerAdapter;
import android.view.View;

public class SearchMenuListAnimationHandler extends AnimatorListenerAdapter
{
	public void animateItemView(View view, boolean isExpanding, SearchMenuListItemAnimationListener searchMenuListItemAnimationListener)
	{
		final float startScale = isExpanding ? 0.0f : 1.0f;
		final float endScale = 1.0f - startScale;
		
		ReversibleValueAnimator viewScaleAnimator = ReversibleValueAnimator.ofFloat(startScale, endScale);
		viewScaleAnimator.addUpdateListener(new ViewScaleYAnimatorUpdateListener(view));
		
		if(isExpanding)
		{
			viewScaleAnimator.setStartDelay(MenuListAnimationConstants.MenuItemExpandAnimationDelayMilliseconds);
		}
		
		viewScaleAnimator.setDuration(MenuListAnimationConstants.MenuItemScaleAnimationSpeedMilliseconds);
		
		ReversibleAnimatorSet reversibleAnimatorSet = new ReversibleAnimatorSet();
		reversibleAnimatorSet.addAnimator(viewScaleAnimator);
		reversibleAnimatorSet.start(searchMenuListItemAnimationListener, false);
	}
}