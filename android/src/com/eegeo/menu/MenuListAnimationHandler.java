package com.eegeo.menu;

import com.eegeo.animation.ReversibleAnimatorSet;
import com.eegeo.animation.ReversibleValueAnimator;
import com.eegeo.animation.updatelisteners.ViewHeightAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewRotateAnimatorUpdateListener;
import com.eegeo.animation.updatelisteners.ViewScaleYAnimatorUpdateListener;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.animation.AnimatorListenerAdapter;
import android.view.View;
import android.widget.AbsListView;


public class MenuListAnimationHandler extends AnimatorListenerAdapter
{
	protected MainActivity m_mainActivity = null;
	protected View m_listContainerView = null;
	
	protected ReversibleAnimatorSet m_itemAnimatorSet;
	
	public MenuListAnimationHandler(MainActivity mainActivity, View listContainerView)
	{
		m_mainActivity = mainActivity;
		
		m_listContainerView = listContainerView;
	
		m_itemAnimatorSet = new ReversibleAnimatorSet();
	}
	
	public void animateHeaderArrow(View view, boolean rotateCounterClockwise)
	{
		final float startValue = rotateCounterClockwise ? 0.0f : -90.0f;
		final float endValue = rotateCounterClockwise ? -90.f : 0.0f;
		
		ReversibleValueAnimator arrowRotationAnimator = ReversibleValueAnimator.ofFloat(startValue, endValue);
		arrowRotationAnimator.addUpdateListener(new ViewRotateAnimatorUpdateListener(view));
		arrowRotationAnimator.setDuration(MenuListAnimationConstants.MenuListTotalAnimationSpeedMilliseconds);
		arrowRotationAnimator.start();
	}
	
	public void animateItemView(View view, boolean isExpanding, MenuListItemAnimationListener listener)
	{
		view.setPivotY(0);
		
		final int onePixel = m_mainActivity.dipAsPx(1);
        final int itemSize =  (int)m_mainActivity.getResources().getDimension(R.dimen.menu_subitem_height);
				
		final int startSize = isExpanding ? onePixel : itemSize;
		final int finalSize = isExpanding ? itemSize : onePixel;

		ReversibleValueAnimator expandCollapseAnimator = ReversibleValueAnimator.ofInt(startSize, finalSize);	
		expandCollapseAnimator.addUpdateListener(new ViewHeightAnimatorUpdateListener<AbsListView.LayoutParams>(view));
		expandCollapseAnimator.setDuration(MenuListAnimationConstants.MenuListTotalAnimationSpeedMilliseconds);

		final float startScale = isExpanding ? 0.0f : 1.0f;
		final float endScale = 1.0f - startScale;
		
		ReversibleValueAnimator viewScaleAnimator = ReversibleValueAnimator.ofFloat(startScale, endScale);
		viewScaleAnimator.addUpdateListener(new ViewScaleYAnimatorUpdateListener(view));
		
		if (isExpanding)
		{
			viewScaleAnimator.setStartDelay(MenuListAnimationConstants.MenuItemExpandAnimationDelayMilliseconds);
		}
		
		viewScaleAnimator.setDuration(MenuListAnimationConstants.MenuItemScaleAnimationSpeedMilliseconds);
		
		ReversibleAnimatorSet reversibleAnimatorSet = new ReversibleAnimatorSet();
		reversibleAnimatorSet.addAnimator(expandCollapseAnimator);
		reversibleAnimatorSet.addAnimator(viewScaleAnimator);
		reversibleAnimatorSet.start(listener, false);
	}
}
