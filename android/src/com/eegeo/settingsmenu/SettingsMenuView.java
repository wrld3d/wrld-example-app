// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

package com.eegeo.settingsmenu;

import java.util.HashMap;
import java.util.List;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuExpandableListAdapter;
import com.eegeo.menu.MenuExpandableListOnClickListener;
import com.eegeo.menu.MenuExpandableListView;
import com.eegeo.menu.MenuListAnimationHandler;
import com.eegeo.menu.MenuView;
import com.eegeo.mobileexampleapp.R;

import android.view.View;
import android.widget.ExpandableListView;
import android.widget.ImageButton;
import android.widget.RelativeLayout;

public class SettingsMenuView extends MenuView
{
    private MenuExpandableListAdapter m_expandableListAdapter = null;
    private MenuListAnimationHandler m_menuListAnimationHandler = null;
    
    public SettingsMenuView(MainActivity activity, long nativeCallerPointer)
    {
        super(activity, nativeCallerPointer);
        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.settings_menu_layout, uiRoot, false);
        
        m_list = (MenuExpandableListView)m_view.findViewById(R.id.settings_menu_item_list);
        
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
        
        View listContainerView = m_view.findViewById(R.id.settings_menu_list_container);
        m_menuListAnimationHandler = new MenuListAnimationHandler(m_activity, listContainerView);
        
        m_expandableListAdapter = new MenuExpandableListAdapter(m_activity, 
        		m_list,
        		m_menuListAnimationHandler, 
        		R.layout.menu_list_item, 
				R.layout.menu_list_subitem,
				R.layout.menu_list_subitem_with_details);
        m_list.setAdapter(m_expandableListAdapter);

        m_expandableListOnClickListener = new MenuExpandableListOnClickListener(m_activity, m_nativeCallerPointer, this);
        m_list.setOnChildClickListener(m_expandableListOnClickListener);
        m_list.setOnGroupClickListener(m_expandableListOnClickListener);
    }
    
    @Override
    public void animateOffScreen() {
    	
    	super.animateOffScreen();
    	
    	if(m_menuState == MenuState.CLOSED_ON_SCREEN)
    	{
    		((SettingsMenuAnimationHandler)m_menuAnimationHandler).playToClosedOffScreen();
    		
    		m_animating = true;
    		
    		m_menuState = MenuState.OFF_SCREEN;
    		
    		m_list.setEnabled(false);
    	}
    }
    
    @Override
    public void onOffScreenAnimationComplete()
    {
    	super.onOffScreenAnimationComplete();
    	
    	if(!m_menuAnimationHandler.isOffScreen())
    	{
    		animateToIntermediateOnScreenState(0);
    	}
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
                                   HashMap<String, List<String>> groupToChildrenMap)
    {
    	m_expandableListAdapter.setData(groups, groupToChildrenMap);
    }

	@Override
	protected void onMenuChildItemClick(ExpandableListView parent, View view, int groupPosition, int childPosition, long id) {
		m_expandableListAdapter.notifyDataSetChanged();
	}
}
