// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.EditorInfo;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuItemSelectedListener;
import com.eegeo.menu.MenuListAdapter;
import com.eegeo.menu.MenuView;
import com.eegeo.menu.MenuViewJniMethods;
import com.eegeo.mobileexampleapp.R;

public class SearchMenuView extends MenuView implements TextView.OnEditorActionListener
{
    protected View m_closeButtonView = null;
    protected View m_progressSpinner = null;
    protected TextView m_numResultsText = null;

    protected int m_totalHeightPx;

    protected int m_dragStartPosYPx;
    protected int m_controlStartPosYPx;

    private ListView m_searchList = null;
    private SearchMenuAdapter m_searchListAdapter = null;
    private OnItemClickListener m_searchMenuItemSelectedListener = null;
    
    private MenuListAdapter m_listAdapter = null;

    private EditText m_editText;
    
    private TextView m_searchCountText;
    
    private boolean m_isCategory;

    public SearchMenuView(MainActivity activity, long nativeCallerPointer)
    {
        super(activity, nativeCallerPointer);
        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_menu_layout, uiRoot, false);

        m_list = (ListView)m_view.findViewById(R.id.search_menu_options_list_view);
        m_searchList = (ListView)m_view.findViewById(R.id.search_menu_item_list);
        m_dragTabView = m_view.findViewById(R.id.search_menu_drag_tab_container_view);
        View dragTabInteractiveView = m_view.findViewById(R.id.search_menu_drag_tab_view);
        dragTabInteractiveView.setOnClickListener(this);
        dragTabInteractiveView.setOnTouchListener(this);

        m_closeButtonView = m_view.findViewById(R.id.search_menu_close_button);
        m_closeButtonView.setOnClickListener(new SearchMenuCloseButtonClickedHandler(m_nativeCallerPointer));

        m_progressSpinner = m_view.findViewById(R.id.search_menu_spinner);
        m_progressSpinner.setVisibility(View.GONE);

        m_numResultsText = (TextView) m_view.findViewById(R.id.search_menu_num_results_text);
        m_numResultsText.setVisibility(View.GONE);
        
        m_editText = (EditText)m_view.findViewById(R.id.search_menu_view_edit_text_view);
        m_editText.setImeActionLabel("Search", KeyEvent.KEYCODE_ENTER);
        m_editText.setOnEditorActionListener(this);
        
        m_searchCountText = (TextView)m_view.findViewById(R.id.search_menu_result_count);
        m_searchCountText.setText("");

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
        
        m_searchListAdapter = new SearchMenuAdapter(m_activity, R.layout.search_result_menu_list_item);
        m_searchList.setAdapter(m_searchListAdapter);
        
        m_searchMenuItemSelectedListener = new SearchMenuItemSelectedListener(m_nativeCallerPointer, this);
        m_searchList.setOnItemClickListener(m_searchMenuItemSelectedListener);
        
        ViewGroup vg = (ViewGroup)m_view;
        m_activity.recursiveDisableSplitMotionEvents(vg);
        
        m_isCategory = false;
    }
    
    @Override
    public boolean onEditorAction(TextView view, int actionId, KeyEvent event)
    {
        if (actionId == EditorInfo.IME_ACTION_DONE)
        {
            final String queryText = m_editText.getText().toString();
            m_activity.dismissKeyboard(m_editText.getWindowToken());

            if(queryText.length() > 0)
            {
                SearchMenuViewJniMethods.PerformSearchQuery(m_nativeCallerPointer, queryText);
            }

            return true;
        }

        return false;
    }
    
    public void removeSearchKeyboard()
    {
        m_activity.dismissKeyboard(m_editText.getWindowToken());
    }

    public void disableEditText()
    {
        m_editText.setEnabled(false);
    }

    public void enableEditText()
    {
        m_editText.setEnabled(true);
    }
    
    public void setEditText(String searchText, boolean isCategory)
    {
    	m_editText.setText(searchText);
    	
    	m_isCategory = isCategory;
    }
    
    public void setSearchResultCount(final int searchResultCount)
    {
    	if(searchResultCount == 0)
    	{
    		m_searchCountText.setText("");
    	}
    	else
    	{
    		Integer searchResultCountWrapp = searchResultCount;
    		m_searchCountText.setText(searchResultCountWrapp.toString());
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
    	m_listAdapter.setData(groups, groupsExpandable, groupToChildrenMap);
    }
    
    public void setSearchSection(final int resultCount,
    							 final String[] searchResults)
    {
    	ArrayList<String> searchResultList = new ArrayList<String>();
        for(int i = 0; i < resultCount; i++)
        {
        	searchResultList.add(searchResults[i]);
        }
        
    	m_searchListAdapter.setData(searchResultList);
    }
}

