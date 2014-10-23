package com.eegeo.searchmenu;

import java.util.ArrayList;
import java.util.List;

import com.eegeo.R;
import com.eegeo.categories.CategoryResources;

import android.app.Activity;
import android.content.Context;
import android.text.TextUtils.TruncateAt;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.RelativeLayout;
import android.widget.TextView;
import org.json.*;

public class SearchMenuAdapter extends BaseAdapter {

	private int m_itemViewId;
	private List<String> m_nameData;
	private Activity m_context;
	
	public SearchMenuAdapter(Activity context, int itemViewId)
	{
		m_context = context;
		m_itemViewId = itemViewId;
		m_nameData = new ArrayList<String>();
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
		final String json = (String)getItem(index);
		
		if(contextView == null)
		{
			LayoutInflater inflater = (LayoutInflater)m_context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			contextView = inflater.inflate(m_itemViewId, null);
		}
		
		try
		{
			JSONObject data = new JSONObject(json);
			
			TextView nameLabel = (TextView)contextView.findViewById(R.id.menu_list_item_name);
			
			nameLabel.setText(data.getString("name"));
			nameLabel.setEllipsize(TruncateAt.END);
			nameLabel.setHorizontallyScrolling(false);
			nameLabel.setSingleLine();
			
			TextView detailLabel = (TextView)contextView.findViewById(R.id.menu_list_item_detail);
			detailLabel.setText(data.getString("details"));
			
			RelativeLayout categoryIcon = (RelativeLayout)contextView.findViewById(R.id.menu_list_item_icon);
			categoryIcon.setBackgroundResource(CategoryResources.getSearchResultIconForCategory(m_context, data.getString("icon")));
		}
		catch(JSONException exception)
		{
			Log.e("Eegeo", "Failed to read json data object: " + exception.getMessage());
		}
			
		
		return contextView;
	}
}
