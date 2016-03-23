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
	
	public MenuExpandableListOnClickListener(MainActivity mainActivity, long nativeCallerPointer)
	{
		m_mainActivity = mainActivity;
		m_nativeCallerPointer = nativeCallerPointer;
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
		return true;
	}
}