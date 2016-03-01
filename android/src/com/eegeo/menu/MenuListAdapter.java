// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.menu;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.json.JSONException;
import org.json.JSONObject;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.categories.CategoryResources;

import android.animation.AnimatorSet;
import android.content.Context;
import android.util.Log;
import android.util.SparseArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class MenuListAdapter extends BaseAdapter
{
    private MainActivity m_context;
    private List<String> m_groups;
    private List<Boolean> m_groupsExpandable;
    private HashMap<String, List<String>> m_groupToChildrenMap;
    private SparseArray< SparseArray<View>> m_groupToChildrenViewMap;
    private int m_groupViewId;
    private int m_childViewId;
    private HashMap<String, Float> m_animatedSizesMap;
    private AnimatorSet m_expandContractAnim;
    
    public MenuListAdapter(MainActivity context,
                           final int groupViewId,
                           final int childViewId)
    {
        m_context = context;

        m_groupViewId = groupViewId;
        m_childViewId = childViewId;
        m_animatedSizesMap = new HashMap<String, Float>();

        m_groups = new ArrayList<String>();
        m_groupsExpandable = new ArrayList<Boolean>();
        m_groupToChildrenMap = new HashMap<String, List<String>>();

        m_groupToChildrenViewMap = new SparseArray<SparseArray<View>>();
    }

    public boolean isAnimating()
    {
        return m_expandContractAnim != null && m_expandContractAnim.isRunning();
    }

    public void setData(
        final List<String> groups,
        final List<Boolean> groupsExpandable,
        final HashMap<String, List<String>> groupToChildren)
    {
    	m_groupToChildrenViewMap.clear();
        updateSources(groups, groupsExpandable, groupToChildren);
        forceSetAnimatedSizes();
        notifyDataSetChanged();
    }

    public void updateSources(
        final List<String> groups,
        final List<Boolean> groupsExpandable,
        final HashMap<String, List<String>> groupToChildren)
    {
        m_groups = groups;
        m_groupsExpandable = groupsExpandable;
        m_groupToChildrenMap = groupToChildren;
    }

    private void forceSetAnimatedSizes()
    {
        for(int i = 0; i < m_groups.size(); i++)
        {
            String key = m_groups.get(i);
            m_animatedSizesMap.put(key, (float)m_groupToChildrenMap.get(key).size());
        }
    }

    @Override
    public int getCount()
    {
        int count = 0;
        for(int groupIndex = 0; groupIndex < m_groups.size(); groupIndex++)
        {
            String key = m_groups.get(groupIndex);
            count += Math.round(m_animatedSizesMap.get(key));
        }
        return count;
    }

    @Override
    public Object getItem(int index)
    {
        int count = 0;
        for(int groupIndex = 0; groupIndex < m_groups.size(); groupIndex++)
        {
            String groupName = m_groups.get(groupIndex);
            List<String> children = m_groupToChildrenMap.get(groupName);
            if(children.size() == 0)
            {
                continue;
            }

            for(int childIndex = 0; childIndex < Math.round(m_animatedSizesMap.get(groupName)); childIndex++)
            {
                if(count == index)
                {
                    return children.get(childIndex);
                }

                count++;
            }
        }
        return "";
    }

    @Override
    public long getItemId(int index)
    {
        return index;
    }

    public int getSectionIndex(int index)
    {
        int count = 0;
        for(int groupIndex = 0; groupIndex < m_groups.size(); groupIndex++)
        {
            String groupName = m_groups.get(groupIndex);
            List<String> children = m_groupToChildrenMap.get(groupName);
            for (int childIndex = 0; childIndex < children.size(); ++childIndex)
            {
                if (count == index)
                {
                    return groupIndex;
                }
                count++;
            }
        }
        return -1;
    }

    public int getItemIndex(int index)
    {
        int count = 0;
        for(int groupIndex = 0; groupIndex < m_groups.size(); groupIndex++)
        {
            String groupName = m_groups.get(groupIndex);
            List<String> children = m_groupToChildrenMap.get(groupName);
            for (int childIndex = 0; childIndex < children.size(); ++childIndex)
            {
                if (count == index)
                {
                    return childIndex;
                }
                count++;
            }
        }
        return -1;
    }

    private boolean isHeader(int index)
    {
        int groupIndex = getGroupIndexForViewIndex(index);
        int placeInGroup = getPlaceInGroup(index);

        if(!m_groupsExpandable.get(groupIndex))
        {
            return true;
        }
        return placeInGroup == 0;
    }

    @Override
    public View getView(int index, View reusableView, ViewGroup parent)
    {
        final String json = (String)getItem(index);
        
        final boolean isHeader = isHeader(index);
        final int groupIndex = getGroupIndexForViewIndex(index);
        final String groupName = m_groups.get(groupIndex);
        final int totalGroupSize = m_groupToChildrenMap.get(groupName).size();
        final float animatedGroupSize = m_animatedSizesMap.get(groupName);
        final float animationPercentage = animatedGroupSize / totalGroupSize;
        SparseArray<View> childrenViewMap = m_groupToChildrenViewMap.get(groupIndex);
      
        if(childrenViewMap == null)
        {
        	childrenViewMap = new SparseArray<View>();
        	m_groupToChildrenViewMap.put(groupIndex, childrenViewMap);
        }
        
        final int childId = getPlaceInGroup(index);
        final int viewId = isHeader ? m_groupViewId : m_childViewId;
        View cachedView = childrenViewMap.get(childId);
     
        if(cachedView == null)
        {
        	LayoutInflater inflater = (LayoutInflater)m_context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        	cachedView = inflater.inflate(viewId, null);
        	cachedView.setTag((Integer)viewId);
        	childrenViewMap.put(childId, cachedView);
        }
        else
        {
        	if(isHeader)
        	{
        		ImageView openableArrow = (ImageView)cachedView.findViewById(R.id.menu_list_openable_shape);
        		if(animatedGroupSize > 1)
        		{
        			openableArrow.setRotation(-90 * animationPercentage);
        		}
        		else
        		{
        			openableArrow.setRotation(0);
        		}
        	}
        	else
        	{
        		cachedView.setScaleY(animationPercentage);
        	}
        	
        	return cachedView;
        }

        reusableView = cachedView;

        try
        {
            JSONObject data = new JSONObject(json);

            TextView nameLabel = (TextView)reusableView.findViewById(R.id.menu_list_item_name);
            nameLabel.setText(data.getString("name"));
        	ImageView icon = (ImageView)reusableView.findViewById(R.id.menu_list_item_icon);
            
            if(icon != null)
            {
            	icon.setImageResource(CategoryResources.getSmallIconForResourceName(m_context, data.getString("icon")));
            }
        }
        catch(JSONException e)
        {
            Log.e("Eegeo", "MenuListAdapter: Failed to read json data object: " + e.getMessage());
        }
        
        if(isHeader)
        {
        	ImageView openableArrow = (ImageView)reusableView.findViewById(R.id.menu_list_openable_shape);

            if(m_groupsExpandable.get(groupIndex))
            {
                RelativeLayout.LayoutParams openableArrowParams = new RelativeLayout.LayoutParams(openableArrow.getLayoutParams());
                
                if(m_animatedSizesMap.get(groupName) > 1)
                {
                    openableArrow.setRotation(-90 * animationPercentage);
                }
                
                final int OpenableRightMargin = 18;

                openableArrowParams.addRule(RelativeLayout.CENTER_VERTICAL, RelativeLayout.TRUE);
                openableArrowParams.addRule(RelativeLayout.ALIGN_PARENT_RIGHT, RelativeLayout.TRUE);
                openableArrowParams.addRule(RelativeLayout.ALIGN_PARENT_RIGHT, RelativeLayout.TRUE);
                openableArrowParams.rightMargin = m_context.dipAsPx(OpenableRightMargin);
                
                openableArrow.setLayoutParams(openableArrowParams);
            }
            else
            {
                openableArrow.setVisibility(View.GONE);
            }
        }
        
        return reusableView;
    }

    private int getGroupIndexForViewIndex(int index)
    {
        int count = 0;
        for(int groupIndex = 0; groupIndex < m_groups.size(); groupIndex++)
        {
            String groupName = m_groups.get(groupIndex);
            for(int childIndex = 0; childIndex < Math.round(m_animatedSizesMap.get(groupName)); childIndex++)
            {
                if(count == index)
                {
                    return groupIndex;
                }
                count++;
            }
        }
        return -1;
    }

    public int getPlaceInGroup(int index)
    {
        int count = 0;
        for(int groupIndex = 0; groupIndex < m_groups.size(); groupIndex++)
        {
            String groupName = m_groups.get(groupIndex);
            for(int childIndex = 0; childIndex < Math.round(m_animatedSizesMap.get(groupName)); childIndex++)
            {
                if(count == index)
                {
                    return childIndex;
                }
                count++;
            }
        }
        return 0;
    }

}
