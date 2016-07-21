package com.eegeo.menu;

import com.eegeo.entrypointinfrastructure.MainActivity;

import android.view.View;
import android.widget.ExpandableListView;
import android.widget.ExpandableListView.OnChildClickListener;
import android.widget.ExpandableListView.OnGroupClickListener;

public class MenuExpandableListOnClickListener implements OnGroupClickListener, OnChildClickListener
{
	private final long m_nativeCallerPointer;
	private MainActivity m_mainActivity;
	private MenuView m_menuView;
	
	public MenuExpandableListOnClickListener(MainActivity mainActivity, long nativeCallerPointer, MenuView menuView)
	{
		m_mainActivity = mainActivity;
		m_nativeCallerPointer = nativeCallerPointer;
		m_menuView = menuView;
	}
	
	@Override
	public boolean onGroupClick(ExpandableListView parent, View view, int groupPosition, long id) 
	{
		MenuExpandableListView expandableListView = (MenuExpandableListView) parent;

		if (!expandableListView.canInteract())
		{
			return true;
		}

		if (expandableListView.isGroupExpanded(groupPosition))
		{
			expandableListView.collapseGroup(groupPosition);
		} 
		else 
		{
			expandableListView.expandGroup(groupPosition);
		}
		
		MenuViewJniMethods.SelectedItem(m_nativeCallerPointer, groupPosition, 0);
		
		return true;
	}

	@Override
	public boolean onChildClick(ExpandableListView parent, View view, int groupPosition, int childPosition, long id) 
	{
		MenuViewJniMethods.SelectedItem(m_nativeCallerPointer, groupPosition, childPosition + 1);
		m_menuView.onMenuChildItemClick(parent, view, groupPosition, childPosition, id);
		return true;
	}
}