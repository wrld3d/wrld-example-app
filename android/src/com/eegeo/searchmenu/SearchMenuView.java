// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import android.text.Editable;
import android.text.TextWatcher;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnFocusChangeListener;
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
import com.eegeo.mobileexampleapp.R;

public class SearchMenuView extends MenuView implements TextView.OnEditorActionListener, OnFocusChangeListener, TextWatcher
{
    protected View m_closeButtonView = null;
    protected View m_progressSpinner = null;

    protected int m_totalHeightPx;

    protected int m_dragStartPosYPx;
    protected int m_controlStartPosYPx;

    private ListView m_searchList = null;
    private SearchMenuAdapter m_searchListAdapter = null;
    private MenuListAdapter m_listAdapter = null;
    private OnItemClickListener m_searchMenuItemSelectedListener = null;
    
    private EditText m_editText;
    private int m_disabledTextColor;
    private int m_enabledTextColor;
    
    private TextView m_searchCountText;
    
    private boolean m_isCategory;
    
    private ArrayList<String> m_pendingResults = null;
    private int m_resultsCount = 0;
    
    private SearchMenuAnimationHandler m_searchMenuAnimationHandler = null;
    	
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
        
        View dragButtonView = m_view.findViewById(R.id.search_menu_drag_button_view);
        dragButtonView.setOnClickListener(this);
        
        m_closeButtonView = m_view.findViewById(R.id.search_menu_clear_button);
        m_closeButtonView.setOnClickListener(new SearchMenuCloseButtonClickedHandler(m_nativeCallerPointer, this));
        m_closeButtonView.setVisibility(View.GONE);

        m_progressSpinner = m_view.findViewById(R.id.search_menu_spinner);
        m_progressSpinner.setVisibility(View.GONE);
        
        m_editText = (EditText)m_view.findViewById(R.id.search_menu_view_edit_text_view);
        m_editText.setImeActionLabel("Search", KeyEvent.KEYCODE_ENTER);
        m_editText.setOnEditorActionListener(this);
        m_editText.addTextChangedListener(this);
        m_editText.setOnFocusChangeListener(this);
        m_editText.clearFocus();
        m_disabledTextColor = m_activity.getResources().getColor(R.color.text_field_disabled);
        m_enabledTextColor = m_activity.getResources().getColor(R.color.text_field_enabled);
        m_editText.setTextColor(m_enabledTextColor);
        
        m_searchCountText = (TextView)m_view.findViewById(R.id.search_menu_result_count);
        m_searchCountText.setText("");
        
        final MenuView scopedMenuView = this;

        m_view.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{
		        m_menuAnimationHandler = m_searchMenuAnimationHandler = new SearchMenuAnimationHandler(m_activity, m_view, scopedMenuView);
		        
		        m_menuAnimationHandler.setToIntermediateOnScreenState(0.0f);
		        
		        m_view.removeOnLayoutChangeListener(this);
			}
		});
        
        uiRoot.addView(m_view);
        
        m_listAdapter = new MenuListAdapter(
        		m_activity, 
        		R.layout.menu_list_item, 
        		R.layout.menu_list_subitem);
        
        m_list.setAdapter(m_listAdapter);
        
        m_menuItemSelectedListener = new MenuItemSelectedListener(
                m_listAdapter,
                this,
                m_nativeCallerPointer
            );
        m_list.setOnItemClickListener(m_menuItemSelectedListener);
        
        m_searchListAdapter = new SearchMenuAdapter(m_activity, R.layout.search_menu_list_item);
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
    	updateClearButtonVisibility();
        if (actionId == EditorInfo.IME_ACTION_DONE ||
        	actionId == KeyEvent.KEYCODE_ENTER)
        {
            final String queryText = m_editText.getText().toString();
            m_activity.dismissKeyboard(m_editText.getWindowToken());
            
            m_editText.clearFocus();
            if(queryText.length() > 0)
            {
                SearchMenuViewJniMethods.PerformSearchQuery(m_nativeCallerPointer, queryText);
            }

            return true;
        }

        return false;
    }
    
    @Override
    public void afterTextChanged(Editable s)
    {
    	
    }

    @Override
    public void beforeTextChanged(CharSequence s, int start, int count, int after)
    {
        
    }

    @Override
    public void onTextChanged(CharSequence s, int start, int before, int count)
    {
    	updateClearButtonVisibility();
    } 
    
    public void removeSearchKeyboard()
    {
        m_activity.dismissKeyboard(m_editText.getWindowToken());
    }

    public void disableEditText()
    {
    	m_closeButtonView.setVisibility(View.GONE);
    	m_progressSpinner.setVisibility(View.VISIBLE);
        m_editText.setEnabled(false);
        m_editText.setTextColor(m_disabledTextColor);
    }

    public void enableEditText()
    {
    	m_closeButtonView.setVisibility(View.VISIBLE);
    	m_progressSpinner.setVisibility(View.GONE);
        m_editText.setEnabled(true);
        m_editText.setTextColor(m_enabledTextColor);
    }
    
    public void setEditText(String searchText, boolean isCategory)
    {
    	setEditTextInternal(searchText, isCategory);
    	m_editText.clearFocus();
    }
    
    private void setEditTextInternal(String searchText, boolean isCategory)
    {
    	m_editText.setText(searchText);
    	m_isCategory = isCategory;
    	updateClearButtonVisibility();
    }
    
    private void updateClearButtonVisibility()
    {
    	m_closeButtonView.setVisibility(View.VISIBLE);
    }
    
    public void setSearchResultCount(final int searchResultCount)
    {
    	if(searchResultCount == 0)
    	{
    		m_searchCountText.setText("");
    		m_searchMenuAnimationHandler.hideSearchResultsView();
    	}
    	else
    	{
    		Integer searchResultCountWrapp = searchResultCount;
    		m_searchCountText.setText(searchResultCountWrapp.toString());
    		m_searchMenuAnimationHandler.showSearchResultsView();
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
        
        if(m_menuAnimationHandler.isOffScreen())
        {
        	m_pendingResults = searchResultList;
        }
        else
        {
        	updateResults(searchResultList);
        }
    }
    
    private void updateResults(ArrayList<String> searchResults)
    {
        m_resultsCount = searchResults.size();
    	updateSearchMenuHeight(m_resultsCount);
    	m_searchListAdapter.setData(searchResults);
    	m_pendingResults = null;
    }
    
    private void updateSearchMenuHeight(int resultCount)
    {   
        final RelativeLayout mainSearchSubview = (RelativeLayout)m_view.findViewById(R.id.search_menu_view);

        final View topBar = (View)m_view.findViewById(R.id.search_menu_title_bar);
        final View menuListContainer = (View)m_view.findViewById(R.id.search_menu_options_list_view);
        
        final float viewHeight = mainSearchSubview.getHeight();
        final float occupiedHeight = topBar.getHeight() + menuListContainer.getHeight();    
        final float availableHeight = viewHeight - occupiedHeight;
        
    	final float cellHeight = m_activity.getResources().getDimension(R.dimen.search_menu_result_cell_height);
    	final float fullHeight = cellHeight * resultCount;

    	final int height = (int)Math.min(fullHeight, availableHeight);
    	
    	ViewGroup.LayoutParams params = m_searchList.getLayoutParams();
    	params.height = height; 
    	m_searchList.setLayoutParams(params);
    }

	@Override
	public void onFocusChange(View v, boolean hasFocus) 
	{
		if(hasFocus && m_isCategory)
		{
			setEditTextInternal("", false);
		}
	}

    private boolean hasPendingResults() { return m_pendingResults != null; }

	@Override
	public void onOpenOnScreenAnimationStart() 
	{
		super.onOpenOnScreenAnimationStart();
		
        m_list.setVisibility(View.VISIBLE);
        m_searchList.setVisibility(View.VISIBLE);
        
		if(hasPendingResults())
		{
        	updateResults(m_pendingResults);
		}
		
    	updateSearchMenuHeight(m_resultsCount);
	}

	@Override
	public void onClosedOnScreenAnimationComplete()
	{
		super.onClosedOnScreenAnimationComplete();
		
        m_list.setVisibility(View.GONE);
        m_searchList.setVisibility(View.GONE);
	}
}

