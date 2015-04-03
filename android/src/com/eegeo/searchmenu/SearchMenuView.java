// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import java.util.HashMap;
import java.util.List;

import android.view.View;
import android.view.animation.AccelerateDecelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.categories.CategoryResources;
import com.eegeo.menu.MenuView;
import com.eegeo.menu.MenuViewJniMethods;

public class SearchMenuView extends MenuView
{
    protected View m_closeButtonView = null;
    protected View m_progressSpinner = null;
    protected TextView m_numResultsText = null;

    protected int m_totalHeightPx;

    protected int m_dragStartPosYPx;
    protected int m_controlStartPosYPx;
    
    private boolean m_inAttractMode = false;

    private SearchMenuAdapter m_listAdapter = null;

    private ImageView m_headerCategoryImage;
    private TextView m_headerText;

    public SearchMenuView(MainActivity activity, long nativeCallerPointer)
    {
        super(activity, nativeCallerPointer);
        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_menu_layout, uiRoot, false);

        m_list = (ListView)m_view.findViewById(R.id.search_menu_item_list);
        m_dragTabView = m_view.findViewById(R.id.search_menu_drag_tab_container_view);
        View dragTabInteractiveView = m_view.findViewById(R.id.search_menu_drag_tab_view);
        dragTabInteractiveView.setOnClickListener(this);
        dragTabInteractiveView.setOnTouchListener(this);

        m_closeButtonView = m_view.findViewById(R.id.search_menu_close_button);
        m_closeButtonView.setOnClickListener(new SearchMenuCloseButtonClickedHandler(m_activity, m_nativeCallerPointer));

        m_progressSpinner = m_view.findViewById(R.id.search_menu_spinner);
        m_progressSpinner.setVisibility(View.GONE);

        m_numResultsText = (TextView) m_view.findViewById(R.id.search_menu_num_results_text);
        m_numResultsText.setVisibility(View.GONE);

        m_view.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{   
		        View listContainerView = m_view.findViewById(R.id.search_menu_view_list_container);
		
		        int dragTabWidthPx = m_dragTabView.getWidth();
		
		        m_mainContainerOffscreenOffsetXPx = -listContainerView.getLeft();
		        int mainContainerWidthPx = listContainerView.getWidth();
		        int mainContainerOnScreenWidthPx = mainContainerWidthPx - m_mainContainerOffscreenOffsetXPx;
		
		        m_totalWidthPx = mainContainerWidthPx + dragTabWidthPx;
		        m_offscreenXPx = -m_totalWidthPx;
		        m_closedXPx = -(mainContainerOnScreenWidthPx - m_activity.dipAsPx(m_mainContainerVisibleOnScreenWhenClosedDip));
		        m_openXPx = -m_mainContainerOffscreenOffsetXPx;
		        m_view.setX(m_offscreenXPx);
		        m_view.removeOnLayoutChangeListener(this);
			}
		});

        uiRoot.addView(m_view);

        m_listAdapter = new SearchMenuAdapter(m_activity, R.layout.search_menu_list_item);
        m_list.setAdapter(m_listAdapter);

        m_headerCategoryImage = (ImageView)m_view.findViewById(R.id.search_menu_header_category_icon);
        m_headerText = (TextView)m_view.findViewById(R.id.search_menu_header_text);

        m_menuItemSelectedListener = new SearchMenuItemSelectedListener(m_nativeCallerPointer, this);
        m_list.setOnItemClickListener(m_menuItemSelectedListener);
    }

    public void updateHeader(final String searchText, final boolean pendingQueryResult, final int numResults)
    {
        if(pendingQueryResult)
        {
            m_progressSpinner.setVisibility(View.VISIBLE);
            m_numResultsText.setVisibility(View.GONE);
        }
        else
        {
            m_numResultsText.setText(String.valueOf(numResults));
            m_numResultsText.setVisibility(View.VISIBLE);
            m_progressSpinner.setVisibility(View.GONE);
        }

        if(m_headerCategoryImage != null)
        {
        	m_headerCategoryImage.setImageResource(CategoryResources.getSmallIconForCategory(m_activity, searchText));
        }
        
        m_headerText.setText(searchText);
    }
    
    public void setAttractMode(boolean attractModeEnabled)
    {
        m_inAttractMode = attractModeEnabled;
        updateAttractMode();
    }
    
    private void updateAttractMode()
    {
    	m_dragTabView.clearAnimation();
    	
        if(m_inAttractMode)
        {	
    		Animation anim = new TranslateAnimation(0, -10.f, 0.f, 0.f);
    		anim.setDuration(300);
    		anim.setInterpolator(new AccelerateDecelerateInterpolator());
    		anim.setRepeatCount(TranslateAnimation.INFINITE);
    		anim.setRepeatMode(TranslateAnimation.REVERSE);
    		
    		m_dragTabView.startAnimation(anim);
        }
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
        updateAttractMode();
    }

    @Override
    protected void handleDragUpdate(int xPx, int yPx)
    {
    	m_dragTabView.clearAnimation();
    	
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
        m_listAdapter.setData(groupToChildrenMap.get("Search"));
    }
}

