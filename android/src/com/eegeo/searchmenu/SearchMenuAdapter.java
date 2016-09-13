// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.eegeo.ProjectSwallowApp.R;
import com.eegeo.categories.CategoryResources;
import com.eegeo.entrypointinfrastructure.MainActivity;

import android.app.Activity;
import android.content.Context;
import android.text.TextUtils.TruncateAt;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.*;

public class SearchMenuAdapter extends BaseAdapter
{
    private int m_itemViewId;
    private List<String> m_nameData;
    private Activity m_context;
    private final String m_defaultIconString = "misc";
    
    private SearchMenuListAnimationHandler m_searchMenuListAnimationHandler = null;
    private SearchMenuListItemAnimationListener m_searchMenuListItemAnimationListener = null;
    
    private HashMap<String, View> m_viewCache;
    
    private boolean m_itemAnimationsEnabled = false;

    public SearchMenuAdapter(Activity context, int itemViewId, SearchMenuListAnimationHandler searchMenuListAnimationHandler, SearchMenuListItemAnimationListener searchMenuListItemAnimationListener)
    {
        m_context = context;
        m_itemViewId = itemViewId;
        m_nameData = new ArrayList<String>();
        
        m_searchMenuListAnimationHandler = searchMenuListAnimationHandler;
        m_searchMenuListItemAnimationListener = searchMenuListItemAnimationListener;
        
        m_viewCache = new HashMap<String, View>();
    }

    public void setData(List<String> nameData)
    {
        m_nameData = nameData;
        notifyDataSetChanged();
    }

    @Override
    public int getCount()
    {
        return m_nameData.size();
    }

    @Override
    public Object getItem(int index)
    {
        return m_nameData.get(index);
    }

    @Override
    public long getItemId(int index)
    {
        return index;
    }

    @Override
    public View getView(int index, View contextView, ViewGroup parent)
    {
    	View itemView;
		
		String key = Integer.toString(index);
		
		if(m_viewCache.containsKey(key))
		{
			itemView = m_viewCache.get(key);
		}
		else
		{
	        LayoutInflater inflater = (LayoutInflater)m_context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	        itemView = inflater.inflate(m_itemViewId, null);
	        
	        if(m_itemAnimationsEnabled)
	        {
		        itemView.setScaleY(0);
		        m_searchMenuListAnimationHandler.animateItemView(itemView, true, m_searchMenuListItemAnimationListener);
	        }
	        
	        m_viewCache.put(key, itemView);
		}
		
		final String json = (String)getItem(index);
        
        try
        {
            JSONObject data = new JSONObject(json);

            TextView nameLabel = (TextView)itemView.findViewById(R.id.menu_list_item_name);

            nameLabel.setText(data.optString("name"));
            nameLabel.setEllipsize(TruncateAt.END);
            nameLabel.setHorizontallyScrolling(false);
            nameLabel.setSingleLine();

            String detailString = data.optString("details");
            TextView detailLabel = (TextView)itemView.findViewById(R.id.menu_list_item_detail);
            detailLabel.setText(detailString);
            
            if(detailString == "")
            {
            	nameLabel.setPadding(0, ((MainActivity) m_context).dipAsPx(7), 0, 0);
            }
            else
            {
            	nameLabel.setPadding(0, 0, 0, 0);
            }
            
            ImageView categoryIcon = (ImageView)itemView.findViewById(R.id.menu_list_item_icon);
            String categoryIconString = data.has("icon") ? data.getString("icon") : m_defaultIconString;
            categoryIcon.setImageResource(CategoryResources.getSmallIconForResourceName(m_context, categoryIconString));
            
        }
        catch(Exception exception)
        {
            Log.e("Eegeo", "SearchMenuAdapter: Failed to read json data object: " + exception.getMessage());
        }

        return itemView;
    }
    
    public void triggerAnimations(boolean isExpanding)
    {
    	int count = getCount();
    	for (int i = 0; i < count; ++i)
		{
			String key = Integer.toString(i);
			if(m_viewCache.containsKey(key))
			{
				View itemView = m_viewCache.get(key);
				
				if(isExpanding)
				{
					itemView.setScaleY(0);
				}
				
				if(m_itemAnimationsEnabled)
				{
					m_searchMenuListAnimationHandler.animateItemView(itemView, isExpanding, m_searchMenuListItemAnimationListener);
				}
			}
		}
    }
    
    public void enableItemAnimations(boolean enable)
    {
    	m_itemAnimationsEnabled = enable;
    }
}
