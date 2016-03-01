// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

package com.eegeo.settingsmenu;

import java.util.HashMap;
import java.util.List;

import android.view.View;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.RelativeLayout;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuItemSelectedListener;
import com.eegeo.menu.MenuListAdapter;
import com.eegeo.menu.MenuView;
import com.eegeo.mobileexampleapp.R;

public class SettingsMenuView extends MenuView
{
    private MenuListAdapter m_listAdapter = null;
    
    public SettingsMenuView(MainActivity activity, long nativeCallerPointer)
    {
        super(activity, nativeCallerPointer);
        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.settings_menu_layout, uiRoot, false);
        
        m_list = (ListView)m_view.findViewById(R.id.settings_menu_item_list);
        
        ImageButton dragButtonView = (ImageButton)m_view.findViewById(R.id.settings_menu_drag_button_view);
        dragButtonView.setOnClickListener(this);
        
        final MenuView scopedMenuView = this;

        m_view.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{
		        m_menuAnimationHandler = new SettingsMenuAnimationHandler(m_activity, m_view, scopedMenuView);
		        
		        m_menuAnimationHandler.setToIntermediateOnScreenState(0.0f);
		        
		        m_view.removeOnLayoutChangeListener(this);
			}
		});
        
        uiRoot.addView(m_view);

        m_listAdapter = new MenuListAdapter(
        		m_activity, 
        		R.layout.settings_menu_item, 
        		R.layout.menu_list_subitem);
        
        m_list.setAdapter(m_listAdapter);

        m_menuItemSelectedListener = new MenuItemSelectedListener(
            m_listAdapter,
            this,
            m_nativeCallerPointer
        );

        m_list.setOnItemClickListener(m_menuItemSelectedListener);
    }

    @Override
    protected void handleDragFinish(int xPx, int yPx)
    {
        
    }

    @Override
    protected void handleDragUpdate(int xPx, int yPx)
    {
        
    }

    @Override
    protected void refreshListData(List<String> groups,
                                   List<Boolean> groupsExpandable,
                                   HashMap<String, List<String>> groupToChildrenMap)
    {
        m_listAdapter.setData(groups, groupsExpandable, groupToChildrenMap);
    }
}
