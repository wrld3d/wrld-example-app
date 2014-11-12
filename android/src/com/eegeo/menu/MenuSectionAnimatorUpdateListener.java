package com.eegeo.menu;

import android.animation.ValueAnimator;

public class MenuSectionAnimatorUpdateListener implements ValueAnimator.AnimatorUpdateListener
{
	private MenuListAdapter m_adapter;
	private String m_groupName;

	public MenuSectionAnimatorUpdateListener(MenuListAdapter adapter, String groupName)
	{
		m_adapter = adapter;
		m_groupName = groupName;
	}

	@Override
	public void onAnimationUpdate(ValueAnimator animator)
	{
		int size = (Integer)animator.getAnimatedValue();
		m_adapter.setAnimatedGroupSize(m_groupName, size);
	}

}
