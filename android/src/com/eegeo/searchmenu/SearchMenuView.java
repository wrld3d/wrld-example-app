// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.eegeo.animation.ReversibleValueAnimator;
import com.eegeo.animation.updatelisteners.ViewHeightAnimatorUpdateListener;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuExpandableListAdapter;
import com.eegeo.menu.MenuExpandableListOnClickListener;
import com.eegeo.menu.MenuExpandableListView;
import com.eegeo.menu.MenuListAnimationConstants;
import com.eegeo.menu.MenuListAnimationHandler;
import com.eegeo.menu.MenuView;
import com.eegeo.mobileexampleapp.R;

import android.text.Editable;
import android.text.TextWatcher;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnFocusChangeListener;
import android.view.ViewGroup;
import android.view.inputmethod.EditorInfo;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class SearchMenuView extends MenuView implements TextView.OnEditorActionListener, OnFocusChangeListener, TextWatcher
{
    protected View m_closeButtonView = null;
    protected View m_progressSpinner = null;
    protected View m_anchorArrow = null;
    protected View m_searchMenuResultsSeparator = null;

    protected int m_totalHeightPx;

    protected int m_dragStartPosYPx;
    protected int m_controlStartPosYPx;

    private ListView m_searchList = null;
    private SearchMenuAdapter m_searchListAdapter = null;
    
    private MenuExpandableListAdapter m_expandableListAdapter = null;
    
    private OnItemClickListener m_searchMenuItemSelectedListener = null;
    
    private EditText m_editText;
    private int m_disabledTextColor;
    private int m_enabledTextColor;
    
    private TextView m_searchCountText;
    private Integer m_searchCount;
    
    private boolean m_isCategory;
    
    private ArrayList<String> m_pendingResults = null;
    private int m_resultsCount = 0;
    
    private SearchMenuAnimationHandler m_searchMenuAnimationHandler = null;
    private MenuListAnimationHandler m_menuListAnimationHandler = null;
    	
    public SearchMenuView(MainActivity activity, long nativeCallerPointer)
    {
        super(activity, nativeCallerPointer);
        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_menu_layout, uiRoot, false);

        m_list = (MenuExpandableListView)m_view.findViewById(R.id.search_menu_options_list_view);
        m_searchList = (ListView)m_view.findViewById(R.id.search_menu_item_list);
        
        View dragButtonView = m_view.findViewById(R.id.search_menu_drag_button_view);
        dragButtonView.setOnClickListener(this);
        
        m_closeButtonView = m_view.findViewById(R.id.search_menu_clear_button);
        m_closeButtonView.setOnClickListener(new SearchMenuCloseButtonClickedHandler(m_nativeCallerPointer, this));
        m_closeButtonView.setVisibility(View.INVISIBLE);

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
        m_searchCount = new Integer(0);
        
        m_anchorArrow = m_view.findViewById(R.id.search_results_anchor_arrow);
        m_anchorArrow.setVisibility(View.GONE);
        
        m_searchMenuResultsSeparator = m_view.findViewById(R.id.search_menu_results_separator);
        m_searchMenuResultsSeparator.setVisibility(View.GONE);
        
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
        
        View listContainerView = m_view.findViewById(R.id.search_menu_list_container);
        m_menuListAnimationHandler = new MenuListAnimationHandler(m_activity, listContainerView);
        
        m_expandableListAdapter = new MenuExpandableListAdapter(m_activity,
        														m_list, 
        														m_menuListAnimationHandler, 
        														R.layout.menu_list_item, 
        														R.layout.menu_list_subitem);

        m_list.setAdapter(m_expandableListAdapter);
        
        m_expandableListOnClickListener = new MenuExpandableListOnClickListener(m_activity, m_nativeCallerPointer);
        m_list.setOnChildClickListener(m_expandableListOnClickListener);
        m_list.setOnGroupClickListener(m_expandableListOnClickListener);
        
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

    public void setSearchInProgress()
    {
    	m_closeButtonView.setVisibility(View.INVISIBLE);
    	m_progressSpinner.setVisibility(View.VISIBLE);
    }

    public void setSearchEnded()
    {
    	m_closeButtonView.setVisibility(View.VISIBLE);
    	m_progressSpinner.setVisibility(View.GONE);
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
    		m_searchCount = 0;
    		m_searchCountText.setText("");
    		m_searchMenuAnimationHandler.hideSearchResultsView();
    		m_closeButtonView.setVisibility(View.INVISIBLE);
    		m_anchorArrow.setVisibility(View.GONE);
    		m_searchMenuResultsSeparator.setVisibility(View.GONE);
 
    	}
    	else
    	{
    		m_searchCount = searchResultCount;
    		m_searchCountText.setText(m_searchCount.toString());
    		m_searchMenuAnimationHandler.showSearchResultsView();
    		m_closeButtonView.setVisibility(View.VISIBLE);
    		m_anchorArrow.setVisibility(View.VISIBLE);
    		m_searchMenuResultsSeparator.setVisibility(View.VISIBLE);
    	}
    }
    
    @Override
    public void animateOffScreen()
    {
    	super.animateOffScreen();
    	
    	m_searchMenuAnimationHandler.hideSearchResultsView();
    }
    
    @Override
    public void animateToClosedOnScreen()
    {
    	super.animateToClosedOnScreen();

		if(m_searchCount > 0)
		{
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
                                   HashMap<String, List<String>> groupToChildrenMap)
    {   
    	m_expandableListAdapter.setData(groups, groupToChildrenMap);
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
        
        if (m_resultsCount > 0)
        {
        	m_list.collapseAllGroups();
        }
        
    	updateSearchMenuHeight(m_resultsCount);
    	m_searchListAdapter.setData(searchResults);
    	m_pendingResults = null;
    }
    
    private void updateSearchMenuHeight(int resultCount)
    {   
        final RelativeLayout mainSearchSubview = (RelativeLayout)m_view.findViewById(R.id.search_menu_view);

        final View topBar = (View)m_view.findViewById(R.id.search_menu_title_bar);
        
        final float viewHeight = mainSearchSubview.getHeight();
        
        final int groupCount = m_expandableListAdapter.getGroupCount();
        final int groupHeaderSize = (int)m_activity.getResources().getDimension(R.dimen.menu_item_header_height);
        final int menuItemDividerHeightSize = (int)m_activity.getResources().getDimension(R.dimen.menu_item_divider_height);
        final int menuListContainerCollapsedSize = groupCount * groupHeaderSize + ((groupCount - 1) * menuItemDividerHeightSize);
        
        final int totalMenuSeparatorSize = 2 * (int)m_activity.getResources().getDimension(R.dimen.menu_section_divider_height);
        
        final float occupiedHeight = topBar.getHeight() + menuListContainerCollapsedSize + totalMenuSeparatorSize;
        final float availableHeight = viewHeight - occupiedHeight;
        
    	final float cellHeight = m_activity.getResources().getDimension(R.dimen.search_menu_result_cell_height);
    	final float fullHeight = cellHeight * resultCount;

    	final int height = (int)Math.min(fullHeight, availableHeight);
    	
    	ViewGroup.LayoutParams params = m_searchList.getLayoutParams();
    	int oldHeight = params.height;

    	ReversibleValueAnimator menuHeightAnimator = ReversibleValueAnimator.ofInt(oldHeight, height);
    	menuHeightAnimator.addUpdateListener(new ViewHeightAnimatorUpdateListener<LinearLayout.LayoutParams>(m_searchList));
    	menuHeightAnimator.setDuration(MenuListAnimationConstants.MenuListTotalAnimationSpeedMilliseconds);
    	menuHeightAnimator.start();
    	m_searchList.setSelection(0);
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

