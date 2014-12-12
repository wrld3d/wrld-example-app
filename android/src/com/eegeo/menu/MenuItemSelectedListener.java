package com.eegeo.menu;

import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

import com.eegeo.mobileexampleapp.INativeMessageRunner;

public class MenuItemSelectedListener implements OnItemClickListener
{
	private final INativeMessageRunner m_nativeMessageRunner;
	private final long m_nativeCallerPointer;
	private MenuListAdapter m_adapter;
	private final MenuView m_menuView;

	public MenuItemSelectedListener(
	    MenuListAdapter adapter,
	    MenuView menuView,
	    INativeMessageRunner nativeMessageRunner,
	    long nativeCallerPointer)
	{
		m_adapter = adapter;
		m_menuView = menuView;
		m_nativeMessageRunner = nativeMessageRunner;
		m_nativeCallerPointer = nativeCallerPointer;
	}

	@Override
	public void onItemClick (AdapterView<?> parent, View itemClicked, int position, long id)
	{
		if(m_adapter.isAnimating() || m_menuView.isAnimating() || m_menuView.isDragging())
		{
			return;
		}

		final String selection = (String)parent.getAdapter().getItem(position);
		final int index = position;

		MenuViewJniMethods.SelectedItem(m_nativeCallerPointer, selection, index);
	}
}





