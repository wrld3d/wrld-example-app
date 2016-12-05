// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import java.util.ArrayList;
import java.util.List;

import com.eegeo.ProjectSwallowApp.R;
import com.eegeo.tags.TagResources;
import com.eegeo.entrypointinfrastructure.MainActivity;

import android.app.Activity;
import android.content.Context;
import android.text.TextUtils.TruncateAt;
import android.util.Log;
import android.util.SparseArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.*;

public class SearchMenuAdapter extends BaseAdapter
{
    public enum ScaleDirection
    {
        ScaleUp,
        ScaleDown
    }

    private int m_itemViewId;
    private List<String> m_nameData;
    private Activity m_context;
    private final String m_defaultIconString = "misc";
    private SparseArray<View> m_viewCache = new SparseArray<View>();

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
        View itemView = m_viewCache.get(index, null);
		final String json = (String)getItem(index);

        if (null == itemView)
        {
            itemView = cacheNewView(index);
        }

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

            ImageView tagIcon = (ImageView)itemView.findViewById(R.id.menu_list_item_icon);
            String tagIconString = data.has("icon") ? data.getString("icon") : m_defaultIconString;
            tagIcon.setImageResource(TagResources.getSearchResultIconForTag(m_context, tagIconString));
            
        }
        catch(Exception exception)
        {
            Log.e("Eegeo", "SearchMenuAdapter: Failed to read json data object: " + exception.getMessage());
        }

        return itemView;
    }

    public void animateItemScales(final int itemLoId, final int itemHiId, final long delay, final ScaleDirection scaleDir)
    {
        final float startScale = scaleDir == ScaleDirection.ScaleUp ? 0f : 1f;
        final float endScale = scaleDir == ScaleDirection.ScaleUp ? 1f : 0f;
        for (int i = itemLoId; i < itemHiId; ++i)
        {
            View v = m_viewCache.get(i, null);
            if (v == null)
            {
                v = cacheNewView(i);
            }
            v.setScaleY(startScale);
            v.animate().setStartDelay(delay).scaleY(endScale);
        }
    }

    private View cacheNewView(final int id)
    {
        LayoutInflater inflater = (LayoutInflater)m_context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        final View itemView = inflater.inflate(m_itemViewId, null);
        itemView.setPivotY(0f);
        m_viewCache.put(id, itemView);
        return itemView;
    }
}
