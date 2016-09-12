package com.eegeo.searchmenu;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;

public class SearchMenuListItemAnimationListener extends AnimatorListenerAdapter
{
	private SearchMenuView m_searchMenuView = null;
	
	SearchMenuListItemAnimationListener(SearchMenuView searchMenuView)
	{
		m_searchMenuView = searchMenuView;
	}
	
	@Override
	public void onAnimationEnd(Animator animation)
	{	
		m_searchMenuView.onFinishedItemAnimation();
	}
}