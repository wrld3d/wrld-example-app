package com.eegeo.menu;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.ExpandableListView;

public class MenuExpandableListView extends ExpandableListView {

	public MenuExpandableListView(Context context) 
	{
		super(context);
	}

	public MenuExpandableListView(Context context, AttributeSet attrs) 
	{
		super(context, attrs);
	}
	
	public MenuExpandableListView(Context context, AttributeSet attrs, int defStyleRes) 
	{
		super(context, attrs, defStyleRes);
	}
	
	
	public boolean canInteract()
	{
		MenuExpandableListAdapter adapter = (MenuExpandableListAdapter)getExpandableListAdapter();
		return !adapter.isAnimating();
	}
	
	@Override
	public boolean expandGroup(int groupPos)
	{
		MenuExpandableListAdapter adapter = (MenuExpandableListAdapter)getExpandableListAdapter();
		
		boolean didExpand = adapter.tryAnimateGroupExpand(groupPos);
		
		if (didExpand)
		{
			super.expandGroup(groupPos);	
		}
		else
		{
			clearChoices();
			adapter.notifyDataSetChanged();
		}
		
		return didExpand;
	}
	
	@Override
	public boolean collapseGroup(int groupPos)
	{
		MenuExpandableListAdapter adapter = (MenuExpandableListAdapter)getExpandableListAdapter();
		boolean didCollapse = adapter.tryAnimateGroupCollapse(groupPos);
		return didCollapse;
	}

	public boolean delayCollapseGroup(int groupPos)
	{
		return super.collapseGroup(groupPos);
	}
	
	public void collapseAllGroups()
	{
		MenuExpandableListAdapter adapter = (MenuExpandableListAdapter)getExpandableListAdapter();
		final int groupCount = adapter.getGroupCount();
		
		for (int i = 0; i < groupCount; ++i)
		{
			if (isGroupExpanded(i))
			{
				adapter.triggerAnimationOnArrowView(i, false);
				delayCollapseGroup(i);
			}
		}
	}
}
