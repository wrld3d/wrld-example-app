// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.primarymenu;

import java.util.HashMap;
import java.util.List;

import android.view.View;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.menu.MenuItemSelectedListener;
import com.eegeo.menu.MenuListAdapter;
import com.eegeo.menu.MenuView;
import com.eegeo.menu.MenuViewJniMethods;

public class PrimaryMenuView extends MenuView
{
	protected MenuListAdapter m_listAdapter = null;

	public PrimaryMenuView(MainActivity activity, long nativeCallerPointer)
	{
		super(activity, nativeCallerPointer);
		createView();
	}

	protected void createView()
	{
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = m_activity.getLayoutInflater().inflate(R.layout.primary_menu_layout, uiRoot, false);

		m_list = (ListView)m_view.findViewById(R.id.primary_menu_item_list);
		m_dragTabView = m_view.findViewById(R.id.primary_menu_drag_tab_view);
		m_dragTabView.setOnClickListener(this);
		m_dragTabView.setOnTouchListener(this);

		View listContainerView = m_view.findViewById(R.id.primary_menu_view_list_container);
		RelativeLayout.LayoutParams viewLayout = (LayoutParams) listContainerView.getLayoutParams();

		m_mainContainerOffscreenOffsetXPx = -viewLayout.leftMargin;
		int mainContainerWidthPx = viewLayout.width;
		int mainContainerOnScreenWidthPx = mainContainerWidthPx - m_mainContainerOffscreenOffsetXPx;

		RelativeLayout.LayoutParams tabLayout = (LayoutParams) m_dragTabView.getLayoutParams();
		int dragTabWidthPx = tabLayout.width;

		m_totalWidthPx = mainContainerWidthPx + dragTabWidthPx;
		m_offscreenXPx = -m_totalWidthPx;
		m_closedXPx = -(mainContainerOnScreenWidthPx - m_activity.dipAsPx(m_mainContainerVisibleOnScreenWhenClosedDip));
		m_openXPx = -m_mainContainerOffscreenOffsetXPx;

		m_view.setX(m_offscreenXPx);
		uiRoot.addView(m_view);

		m_listAdapter = new MenuListAdapter(m_activity, R.layout.menu_list_item, R.layout.menu_list_subitem, true);
		m_list.setAdapter(m_listAdapter);

		m_menuItemSelectedListener = new MenuItemSelectedListener(
		    m_listAdapter,
		    m_activity,
		    m_nativeCallerPointer
		);

		m_list.setOnItemClickListener(m_menuItemSelectedListener);
	}

	@Override
	protected void handleDragFinish(int xPx, int yPx)
	{
		m_dragInProgress = false;
		final float minimumXValueToClose = startedClosed(m_controlStartPosXPx) ? 0.35f : 0.65f;
		final Boolean close = xPx < (m_totalWidthPx * minimumXValueToClose);
		final int upXPx = close ? m_closedXPx : m_openXPx;
		log("ACTION_UP", "x: " + upXPx);

		animateViewToX(upXPx);
		MenuViewJniMethods.ViewDragCompleted(m_nativeCallerPointer);
	}

	@Override
	protected void handleDragUpdate(int xPx, int yPx)
	{
		float newXPx = m_controlStartPosXPx + (xPx - m_dragStartPosXPx);

		if(newXPx > m_mainContainerOffscreenOffsetXPx)
		{
			newXPx = m_mainContainerOffscreenOffsetXPx;
		}

		if(newXPx < m_closedXPx)
		{
			newXPx = m_closedXPx;
		}

		float normalisedDragState = (newXPx + (-m_closedXPx)) / (Math.abs(m_openXPx - m_closedXPx));
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
