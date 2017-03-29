package com.eegeo.menu;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;

public class MenuListItemAnimationListener extends AnimatorListenerAdapter
{
	private int m_groupPosition;
	private boolean m_didExpand;
	private MenuExpandableListAdapter m_menuExpandableListAdapter;
	
	MenuListItemAnimationListener(int groupPosition, boolean didExpand, MenuExpandableListAdapter menuExpandableListAdapter)
	{
		m_groupPosition = groupPosition;
		m_didExpand = didExpand;
		m_menuExpandableListAdapter = menuExpandableListAdapter;
	}

	@Override
	public void onAnimationCancel(Animator animation)
	{
		onAnimationEnd(animation);
	}

	@Override
	public void onAnimationEnd(Animator animation)
	{	
		boolean didCollapse = !m_didExpand;
		m_menuExpandableListAdapter.onFinishedItemAnimation(m_groupPosition, didCollapse);
	}
}
