package com.eegeo.menu;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.eegeo.tags.TagResources;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.BaseExpandableListAdapter;
import android.widget.ImageView;
import android.widget.RadioGroup.LayoutParams;
import android.widget.TextView;

public class MenuExpandableListAdapter extends BaseExpandableListAdapter 
{
	private MainActivity m_context;
	
	private List<MenuItemData> m_headerData;
	private HashMap<String, List<MenuItemData>> m_childData;
	
	MenuExpandableListView m_expandableList;
	MenuListAnimationHandler m_menuListAnimationHandler;

	// IH: The off-the-shelf view caching does't play well with animators
	//     Once a view has started animating, it seems to mark it good for reuse.
	//     Workaround by having our own view caches
	private HashMap<String, View> m_headerViewCache;
	private HashMap<String, View> m_childrenViewCache;

	int m_expandedGroupIndex = -1;
	
	private LayoutInflater m_inflater;
	final private int m_groupViewId;
	final private int m_childViewId; 
	final private int m_childViewWithDetailsId;
	
	boolean m_isAnimating = false;
	
	public MenuExpandableListAdapter(MainActivity context, 
									 MenuExpandableListView expandableList, 
									 MenuListAnimationHandler menuListAnimationHandler, 
									 final int groupViewId, 
									 final int childViewId,
									 final int childViewWithDetailsId)
	{
		m_context = context;
		m_expandableList = expandableList;
		m_menuListAnimationHandler = menuListAnimationHandler;
		
		m_headerData = new ArrayList<MenuItemData>();
		m_childData = new HashMap<String, List<MenuItemData>>();
		
		m_inflater = LayoutInflater.from(m_context);
		m_groupViewId = groupViewId;
		m_childViewId = childViewId;
		m_childViewWithDetailsId = childViewWithDetailsId;
		
		m_headerViewCache = new HashMap<String, View>();
		m_childrenViewCache = new HashMap<String, View>();
	}
	
	public boolean isAnimating()
	{
		return m_isAnimating;
	}
	
	public void clearData()
	{
		m_headerData.clear();
		m_childData.clear();
		m_headerViewCache.clear();
		m_childrenViewCache.clear();
	}
	
	public void setData(final List<String> headerData, final HashMap<String, List<String>> childData)
	{
		clearData();
		
		for (String serialisedJson : headerData)
		{
			MenuItemData i = MenuItemData.fromJson(serialisedJson);
			m_headerData.add(i);
		}
		
		for (Map.Entry<String, List<String>> entry : childData.entrySet())
		{
			String key = entry.getKey();

			List<String> values = entry.getValue();
			List<MenuItemData> items = new ArrayList<MenuItemData>();
			
			for (String jsonString : values)
			{
				items.add(MenuItemData.fromJson(jsonString));
			}
			
			m_childData.put(key, items);
		}

		notifyDataSetChanged();
	}
	
	
	@Override
	public Object getChild(int groupPosition, int childPosition) 
	{
		String key = m_headerData.get(groupPosition).getText();
		MenuItemData child = m_childData.get(key).get(childPosition);
		
		return child;
	}

	@Override
	public long getChildId(int groupPosition, int childPosition) 
	{
		return childPosition;
	}
	
	@Override
	public View getChildView(int groupPosition, int childPosition, boolean isLastChild, View convertView, ViewGroup parent) 
	{
		View itemView;
		
		String key = m_headerData.get(groupPosition).getText() + Integer.toString(childPosition);
		
		if (m_childrenViewCache.containsKey(key))
		{
			itemView = m_childrenViewCache.get(key);
		}
		else
		{
			MenuItemData menuItemData = (MenuItemData) getChild(groupPosition, childPosition);
			final int viewToInflate = menuItemData.hasDetails() ? m_childViewWithDetailsId : m_childViewId;
			itemView = inflateView(viewToInflate, menuItemData);
			
			// IH: In order for animator to operate, layout params can't be null. So explicitly assign here.
			//     If this isn't done, layout param setting is deferred until view is rendered, meaning animator 
			//     will attempt to operate on null value
			AbsListView.LayoutParams viewLayoutParams = new AbsListView.LayoutParams(LayoutParams.MATCH_PARENT, 1);
			itemView.setLayoutParams(viewLayoutParams);
			itemView.setScaleY(0.0f);
			
			MenuListItemAnimationListener listener = new MenuListItemAnimationListener(groupPosition, true,  this);
			m_menuListAnimationHandler.animateItemView(itemView, true, listener);
			
			m_childrenViewCache.put(key, itemView);
		}

		jumpToTopOfMenuIfAnimating();
		
		return itemView;
	}

	private void jumpToTopOfMenuIfAnimating() 
	{
		if (m_isAnimating)
		{
			m_expandableList.setSelectedGroup(0);
		}
	}

	@Override
	public int getChildrenCount(int groupPosition) 
	{
		MenuItemData viewModel = (MenuItemData)m_headerData.get(groupPosition);
		String key = viewModel.getText();
		return m_childData.get(key).size();
	}

	@Override
	public Object getGroup(int groupPosition) 
	{
		return m_headerData.get(groupPosition);
	}

	@Override
	public int getGroupCount() 
	{
		return m_headerData.size();
	}

	@Override
	public long getGroupId(int groupPosition) 
	{
		return groupPosition;
	}

	@Override
	public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup parent) 
	{
		View itemView;
		MenuItemData menuItemData = (MenuItemData)getGroup(groupPosition);
		
		String key = m_headerData.get(groupPosition).getText();
		if (m_headerViewCache.containsKey(key))
		{
			itemView = m_headerViewCache.get(key);
		}
		else
		{
			itemView = inflateView(m_groupViewId, menuItemData);		
			m_headerViewCache.put(key, itemView);
		}
		
		List<MenuItemData> children = m_childData.get(menuItemData.getText());
		Boolean isExpandable = children != null && children.size() > 0;
		View arrowView = itemView.findViewById(R.id.menu_list_openable_shape);
		if(arrowView != null)
		{
			arrowView.setVisibility(isExpandable ? View.VISIBLE : View.GONE);
		}
		
		return itemView;
	}


	@Override
	public boolean hasStableIds() 
	{
		return false;
	}

	@Override
	public boolean isChildSelectable(int groupPosition, int childPosition) 
	{
		return true;
	}
	
	@Override
	public void onGroupExpanded(int groupPosition)
	{
		markOtherGroupItemsForCollapse(groupPosition);
		m_expandedGroupIndex = groupPosition;
	}
	
	public boolean tryAnimateGroupExpand(int groupToExpand)
	{
		final int numberOfChildrenInGroup = getChildrenCount(groupToExpand);
		
		if (numberOfChildrenInGroup == 0)
		{
			return false;
		}
		
		m_isAnimating = true;
		
		triggerGroupAnimations(groupToExpand, true);
		
		return true;
	}

	private void markOtherGroupItemsForCollapse(int groupToExpand) 
	{
		if (m_expandedGroupIndex != -1 && m_expandedGroupIndex != groupToExpand)
		{
			triggerGroupAnimations(m_expandedGroupIndex, false);
		}
	}
	
	public boolean tryAnimateGroupCollapse(int groupToCollapse)
	{
		m_expandedGroupIndex = -1;
		
		final int numberOfChildrenInGroup = getChildrenCount(groupToCollapse);
		
		if (numberOfChildrenInGroup == 0)
		{
			return false;
		}
		
		m_isAnimating = true;
		triggerGroupAnimations(groupToCollapse, false);
		
		return true;
	}
	
	public void onFinishedItemAnimation(int groupPosition, boolean didCollapse)
	{
		m_isAnimating = false;
		
		if (didCollapse && m_expandableList.isGroupExpanded(groupPosition))
		{
			m_expandableList.delayCollapseGroup(groupPosition);
		}
	}
	
	private void triggerGroupAnimations(int groupIndex, boolean isExpanding)
	{
		triggerAnimationOnArrowView(groupIndex, isExpanding);
		triggerAnimationsOnChildViews(groupIndex, isExpanding);
	}
	
	private void triggerAnimationsOnChildViews(int groupIndex, boolean isExpanding)
	{
		final int numberOfChildrenInGroup = getChildrenCount(groupIndex);
		String groupKeyPortion =  m_headerData.get(groupIndex).getText();
		
		for (int i = 0; i < numberOfChildrenInGroup; ++i)
		{
			String childKeyPortion = Integer.toString(i);
			String combinedKey = groupKeyPortion + childKeyPortion;
			if (m_childrenViewCache.containsKey(combinedKey))
			{
				MenuListItemAnimationListener listener = new MenuListItemAnimationListener(groupIndex, isExpanding, this);
				m_menuListAnimationHandler.animateItemView(m_childrenViewCache.get(combinedKey), isExpanding, listener);
			}
		}
	}
	
	public void triggerAnimationOnArrowView(int groupIndex, boolean rotateCounterClockwise)
	{
		String groupKeyPortion =  m_headerData.get(groupIndex).getText();
		
		if (m_headerViewCache.containsKey(groupKeyPortion))
		{
			View itemView = m_headerViewCache.get(groupKeyPortion);
			View arrowView = itemView.findViewById(R.id.menu_list_openable_shape);
			m_menuListAnimationHandler.animateHeaderArrow(arrowView, rotateCounterClockwise);
		}
	}
	
	private View inflateView(int viewId, MenuItemData itemData)
	{
		View itemView = (View) m_inflater.inflate(viewId, null);

		TextView itemText = (TextView)itemView.findViewById(R.id.menu_list_item_name);
		itemText.setText(itemData.getText());
		
		if (itemData.hasDetails())
		{
			TextView detailsText = (TextView)itemView.findViewById(R.id.menu_list_item_detail);
			detailsText.setText(itemData.getDetails());
		}
		
		ImageView itemIcon = (ImageView)itemView.findViewById(R.id.menu_list_item_icon);
		if (itemIcon != null)
		{
			itemIcon.setImageResource(TagResources.getIconForResourceName(m_context, itemData.getIcon()));
		}
		
		return itemView;
	}
}