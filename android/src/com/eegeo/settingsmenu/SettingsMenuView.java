// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

package com.eegeo.settingsmenu;

import java.util.HashMap;
import java.util.List;

import android.view.View;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuItemSelectedListener;
import com.eegeo.menu.MenuListAdapter;
import com.eegeo.menu.MenuView;
import com.eegeo.menu.MenuViewJniMethods;
import com.eegeo.mobileexampleapp.R;

public class SettingsMenuView extends MenuView
{
	private int m_screenWidthPx;
    private int m_mainContainerOnScreenWidthPx;
    
    protected MenuListAdapter m_listAdapter = null;

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
        m_dragTabView = m_view.findViewById(R.id.settings_menu_drag_tab_view);
        
        m_dragButtonView = (ImageButton)m_view.findViewById(R.id.settings_menu_drag_button_view);
        m_dragButtonView.setOnClickListener(this);
        m_dragButtonView.setOnTouchListener(this);

        m_screenWidthPx = uiRoot.getWidth();

        View listContainerView = m_view.findViewById(R.id.settings_menu_view_list_container);
        RelativeLayout.LayoutParams viewLayout = (LayoutParams) listContainerView.getLayoutParams();

        RelativeLayout.LayoutParams tabLayout = (LayoutParams) m_dragTabView.getLayoutParams();
        int dragTabWidthPx = tabLayout.width;

        m_mainContainerOffscreenOffsetXPx = -tabLayout.rightMargin;
        int mainContainerWidthPx = viewLayout.width;
        m_mainContainerOnScreenWidthPx = mainContainerWidthPx - m_mainContainerOffscreenOffsetXPx;

        m_totalWidthPx = mainContainerWidthPx + dragTabWidthPx;
        m_offscreenXPx = m_screenWidthPx - (m_view.getPaddingRight());
        m_closedXPx = m_screenWidthPx - m_activity.dipAsPx(m_mainContainerVisibleOnScreenWhenClosedDip) - dragTabWidthPx;
        m_openXPx = m_screenWidthPx - m_mainContainerOnScreenWidthPx - dragTabWidthPx - (m_view.getPaddingRight());

        m_view.setX(m_offscreenXPx);
        uiRoot.addView(m_view);

        m_listAdapter = new MenuListAdapter(
        		m_activity, 
        		R.layout.menu_list_item, 
        		R.layout.menu_list_subitem, 
        		false,
        		R.drawable.menu_header_item_selected_states, 
        		R.drawable.menu_sub_item_selected_states);
        
        m_list.setAdapter(m_listAdapter);

        m_menuItemSelectedListener = new MenuItemSelectedListener(
            m_listAdapter,
            this,
            m_activity,
            m_nativeCallerPointer
        );

        m_list.setOnItemClickListener(m_menuItemSelectedListener);
    }

    @Override
    protected void handleDragFinish(int xPx, int yPx)
    {
        m_dragInProgress = false;

        final float xRatioForStateChange = startedClosed(m_controlStartPosXPx) ? 0.35f : 0.65f;
        final float threshold = (m_screenWidthPx - (m_mainContainerOnScreenWidthPx * xRatioForStateChange));
        final boolean open = xPx < threshold;
        final int upXPx = (open ? m_openXPx : m_closedXPx);
        log("ACTION_UP", "x: " + upXPx);

        animateViewToX(upXPx);
        MenuViewJniMethods.ViewDragCompleted(m_nativeCallerPointer);
    }

    @Override
    protected void handleDragUpdate(int xPx, int yPx)
    {
        float newXPx = m_controlStartPosXPx + (xPx - m_dragStartPosXPx);

        if(newXPx < (m_screenWidthPx - m_totalWidthPx))
        {
            newXPx = m_screenWidthPx - m_totalWidthPx;
        }

        if(newXPx > m_closedXPx)
        {
            newXPx = m_closedXPx;
        }

        float normalisedDragState = Math.abs(newXPx + (-m_closedXPx)) / (Math.abs(m_openXPx - m_closedXPx));
        final float clampedNormalisedDragState = clamp(normalisedDragState, 0.f, 1.f);

        MenuViewJniMethods.ViewDragInProgress(m_nativeCallerPointer, clampedNormalisedDragState);

        m_view.setX(newXPx);
        log("ACTION_MOVE", "x: " + newXPx+ ", clamp: " + clampedNormalisedDragState);
    }

    @Override
    protected void refreshListData(List<String> groups,
                                   List<Boolean> groupsExpandable,
                                   HashMap<String, List<String>> groupToChildrenMap)
    {
        m_listAdapter.setData(groups, groupsExpandable, groupToChildrenMap);
    }
}
