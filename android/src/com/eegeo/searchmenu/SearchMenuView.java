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
import com.eegeo.menu.MenuListAnimationHandler;
import com.eegeo.menu.MenuView;
import com.eegeo.ProjectSwallowApp.R;

import android.os.Handler;
import android.text.Editable;
import android.text.TextWatcher;
import android.text.TextUtils.TruncateAt;
import android.util.DisplayMetrics;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnFocusChangeListener;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.view.animation.DecelerateInterpolator;
import android.view.inputmethod.EditorInfo;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ExpandableListView;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class SearchMenuView extends MenuView implements TextView.OnEditorActionListener, OnFocusChangeListener, TextWatcher {
    protected View m_closeButtonView = null;
    protected View m_progressSpinner = null;
    protected View m_anchorArrow = null;
    protected View m_searchMenuResultsSeparator = null;

    protected int m_totalHeightPx;

    protected int m_dragStartPosYPx;
    protected int m_controlStartPosYPx;

    private ListView m_searchList = null;
    private SearchMenuAdapter m_searchListAdapter = null;
    
    private OnItemClickListener m_searchMenuItemSelectedListener = null;

    private EditText m_editText;
    private int m_disabledTextColor;
    private int m_enabledTextColor;
    
    private TextView m_searchCountText;
    private Integer m_searchCount;
    
    private boolean m_isTag;
    private boolean m_isFindMenuChildItemClicked;
    
    private ArrayList<String> m_pendingResults = null;
    private int m_resultsCount = 0;

    private SearchMenuAnimationHandler m_searchMenuAnimationHandler = null;
    
    private ImageView m_searchResultsFade;
    private Button m_searchResultsScrollButton;
    private boolean m_searchResultsScrollable;
    private SearchResultsScrollButtonTouchDownListener m_searchResultsScrollButtonTouchDownListener;
    private SearchResultsScrollListener m_searchResultsScrollListener;
    
    private MenuExpandableListAdapter m_expandableListAdapter = null;
    private MenuListAnimationHandler m_menuListAnimationHandler = null;
    
    private float m_scaledDensity;
    private float m_ssgS7EditTextWidth;
    private float m_ssgS7ScaledDensity;
    private float m_ssgS7EditTextPixelWidth;
    private float m_editTextPixelWidth;

    private int  m_visibleItemsCount = 0;
    private int m_groupHeaderSize;
    private int m_menuItemDividerHeightSize;
    private float m_cellHeight;
    private boolean m_initializeOnSearchMenuOpenComplete = false;
    private boolean m_fontScaleInitialized = false;

    public SearchMenuView(MainActivity activity, long nativeCallerPointer)
    {
        super(activity, nativeCallerPointer);
        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_menu_layout, uiRoot, false);

        m_groupHeaderSize = (int)m_activity.getResources().getDimension(R.dimen.menu_item_header_height);
        m_menuItemDividerHeightSize = (int)m_activity.getResources().getDimension(R.dimen.menu_item_divider_height);
        m_cellHeight = m_activity.getResources().getDimension(R.dimen.search_menu_result_cell_height);

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
        m_editText.setEllipsize(TruncateAt.END);

        m_searchCountText = (TextView)m_view.findViewById(R.id.search_menu_result_count);
        m_searchCountText.setText("");
        m_searchCount = new Integer(0);
        
        m_anchorArrow = m_view.findViewById(R.id.search_results_anchor_arrow);
        m_anchorArrow.setVisibility(View.GONE);

        m_searchMenuResultsSeparator = m_view.findViewById(R.id.search_menu_results_separator);
        m_searchMenuResultsSeparator.setVisibility(View.GONE);
        
        m_searchResultsFade = (ImageView)m_view.findViewById(R.id.search_results_fade);
        m_searchResultsScrollButton = (Button)m_view.findViewById(R.id.search_results_scroll_button);
        m_searchResultsScrollable = false;
        
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
        														R.layout.menu_list_subitem,
        														R.layout.menu_list_subitem_with_details);

        m_list.setAdapter(m_expandableListAdapter);
        
        m_expandableListOnClickListener = new MenuExpandableListOnClickListener(m_activity, m_nativeCallerPointer, this);
        m_list.setOnChildClickListener(m_expandableListOnClickListener);
        m_list.setOnGroupClickListener(m_expandableListOnClickListener);

        m_searchListAdapter = new SearchMenuAdapter(m_activity, R.layout.search_menu_list_item);
        m_searchList.setAdapter(m_searchListAdapter);
        
        m_searchMenuItemSelectedListener = new SearchMenuItemSelectedListener(m_nativeCallerPointer, this);
        m_searchList.setOnItemClickListener(m_searchMenuItemSelectedListener);
        
        ViewGroup vg = (ViewGroup)m_view;
        m_activity.recursiveDisableSplitMotionEvents(vg);
        
        m_isTag = false;
        
        m_searchResultsScrollListener = new SearchResultsScrollListener(m_searchResultsScrollButton, m_searchResultsFade, m_searchResultsScrollable, m_searchList);       
        m_searchList.setOnScrollListener(m_searchResultsScrollListener);	
                
        m_searchResultsScrollButtonTouchDownListener = new SearchResultsScrollButtonTouchDownListener(m_searchList, m_activity);
        m_searchResultsScrollButton.setOnTouchListener(m_searchResultsScrollButtonTouchDownListener);
    }
    
    @Override
    public boolean onEditorAction(TextView view, int actionId, KeyEvent event)
    {
        setClearButtonVisible(true);
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
        if(count != 0) {
            setClearButtonVisible(true);
        } else {
            setClearButtonVisible(false);
        }

    	if (s.length() == 0)
    	{
    		scaleHintText();
    	}
    	else
    	{
            m_editText.setTextSize(18.0f);
    	}
    } 
    
    public void scaleHintText()
    {
    	DisplayMetrics metrics =  m_activity.getResources().getDisplayMetrics();
        m_scaledDensity = metrics.scaledDensity;
        m_ssgS7EditTextWidth = 868.0f;
        m_ssgS7ScaledDensity = 4.0f;
        m_ssgS7EditTextPixelWidth = (m_ssgS7EditTextWidth/m_ssgS7ScaledDensity);
        m_editTextPixelWidth = m_editText.getWidth()/m_scaledDensity;
        float textSizeScaleFactor = m_editTextPixelWidth / m_ssgS7EditTextPixelWidth;
        // Work around for text truncating on some devices under the following circumstances. Reducing text size a little to fix. MC
        if (textSizeScaleFactor == 1.0f && m_editText.getWidth() != m_ssgS7EditTextWidth)
        {
        	m_editText.setTextSize(13.70f * textSizeScaleFactor);
        }
        else
        {
        	m_editText.setTextSize(14.0f * textSizeScaleFactor);
        }
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
    
    public void setEditText(String searchText, boolean isTag)
    {
    	setEditTextInternal(searchText, isTag);
    	m_editText.clearFocus();
    }
    
    private void setEditTextInternal(String searchText, boolean isTag)
    {
    	m_editText.setText(searchText);
    	m_isTag = isTag;
        if(!searchText.isEmpty()) {
            setClearButtonVisible(true);
        } else {
            setClearButtonVisible(false);
        }
    }
    
    private void setClearButtonVisible(boolean visible)
    {
        if(visible)
        {
            m_closeButtonView.setVisibility(View.VISIBLE);
        }
        else
        {
            m_closeButtonView.setVisibility(View.INVISIBLE);
        }
    }
    
    public void setSearchResultCount(final int searchResultCount)
    {
    	if(searchResultCount == 0)
    	{
    		m_searchCount = 0;
    		m_searchCountText.setText("");
    		
    		if(m_searchMenuAnimationHandler != null)
    		{
    			m_searchMenuAnimationHandler.hideSearchResultsView();
    		}

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

    public void removeSearchQueryResults()
    {
        setSearchResultCount(0);
    }
    
    public void fadeInButtonAnimation(final long delay)
    {
        m_searchResultsScrollButton.animate()
                .setInterpolator(new DecelerateInterpolator())
                .setDuration(SearchMenuResultsListAnimationConstants.SearchMenuResultsListScrollButtonAnimationSpeedMilliseconds)
                .setStartDelay(delay)
                .alpha(1f);
    }
    
    @Override
    public void animateOffScreen()
    {
    	super.animateOffScreen();    	
    }
    
    @Override
    public void animateToClosedOnScreen()
    {
    	super.animateToClosedOnScreen();
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

    public void removeSearchQueryResults()
    {
        setSearchResultCount(0);
        m_editText.setText("");
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

    private void updateResults(final ArrayList<String> searchResults)
    {
        final int resultsCount = searchResults.size();
        if (resultsCount > 0)
        {
        	m_list.collapseAllGroups();
            updateSearchMenuHeight(resultsCount);
            m_searchListAdapter.setData(searchResults);
            final ViewTreeObserver vto = m_searchList.getViewTreeObserver();
            vto.addOnPreDrawListener(new ViewTreeObserver.OnPreDrawListener() {
                @Override
                public boolean onPreDraw() {
                    vto.removeOnPreDrawListener(this);
                    m_searchListAdapter.animateItemScales(0, m_visibleItemsCount, SearchMenuResultsListAnimationConstants.SearchMenuItemExpandAnimationDelayMilliseconds, SearchMenuAdapter.ScaleDirection.ScaleUp);
                    return true;
                }
            });
            final long delay = SearchMenuResultsListAnimationConstants.SearchMenuItemScaleAnimationSpeedMilliseconds + SearchMenuResultsListAnimationConstants.SearchMenuItemExpandAnimationDelayMilliseconds;
            m_searchResultsScrollButton.setAlpha(0f);
            fadeInButtonAnimation(delay);
            m_pendingResults = null;
        }
        else
        {
            if (resultsCount != m_resultsCount)
            {
                m_searchListAdapter.animateItemScales(0, m_visibleItemsCount, 0, SearchMenuAdapter.ScaleDirection.ScaleDown);
                new Handler().postDelayed(new Runnable()
                {
                    @Override
                    public void run() {
                        updateEmptyResults(resultsCount);
                    }
                }, SearchMenuResultsListAnimationConstants.SearchMenuItemScaleAnimationSpeedMilliseconds);
            }
            m_pendingResults = null;
        }
        m_resultsCount = resultsCount;
    }

    private void initializeOnSearchMenuOpen()
    {
        m_initializeOnSearchMenuOpenComplete = true;

        if (m_searchResultsScrollButton.getX() == 0)
        {
            m_searchResultsScrollButton.setX(m_searchResultsFade.getPaddingLeft()
                    - m_searchResultsScrollButton.getWidth() / 2
                    + (m_searchResultsFade.getWidth() - (m_searchResultsFade.getPaddingLeft() + m_searchResultsFade.getPaddingRight())) / 2);
        }

        if (!m_fontScaleInitialized)
        {
            scaleHintText();
            m_fontScaleInitialized = true;
        }
    }

    private void updateEmptyResults(int numResults)
    {
        updateSearchMenuHeight(numResults);
        m_pendingResults = null;
    }

    private void updateSearchMenuHeight(final int resultCount)
    {   
        final RelativeLayout mainSearchSubview = (RelativeLayout)m_view.findViewById(R.id.search_menu_view);

        final View topBar = (View)m_view.findViewById(R.id.search_menu_title_bar);
        
        final float viewHeight = mainSearchSubview.getHeight();

        final int groupCount = m_expandableListAdapter.getGroupCount();
        final int menuListContainerCollapsedSize = groupCount * m_groupHeaderSize + ((groupCount - 1) * m_menuItemDividerHeightSize);

        final int totalMenuSeparatorSize = 2 * (int)m_activity.getResources().getDimension(R.dimen.menu_section_divider_height);
        
        final float occupiedHeight = topBar.getHeight() + menuListContainerCollapsedSize + totalMenuSeparatorSize;
        final float availableHeight = viewHeight - occupiedHeight;

    	final float fullHeight = m_cellHeight * resultCount;

        m_visibleItemsCount = (int) Math.min(Math.ceil(availableHeight / m_cellHeight), resultCount);

    	final float listDividerHeight = m_searchList.getDividerHeight();
    	final int height = (int)Math.min(Math.max(fullHeight - listDividerHeight, 0), availableHeight);

    	final ViewGroup.LayoutParams params = m_searchList.getLayoutParams();
    	final int oldHeight = params.height;
        params.height = height;
        m_searchList.setSelection(0);

    	ReversibleValueAnimator menuHeightAnimator = ReversibleValueAnimator.ofInt(oldHeight, height);
    	menuHeightAnimator.addUpdateListener(new ViewHeightAnimatorUpdateListener<LinearLayout.LayoutParams>(m_searchList));
    	menuHeightAnimator.setDuration(SearchMenuResultsListAnimationConstants.SearchMenuListTotalAnimationSpeedMilliseconds);
    	menuHeightAnimator.start();

    	if(fullHeight > availableHeight + m_cellHeight)
    	{
    		m_searchResultsFade.setVisibility(View.VISIBLE);
    		m_searchResultsScrollButton.setVisibility(View.VISIBLE);
    		m_searchResultsScrollable = true;

    		if(resultCount > 0 && oldHeight == 0)
    		{
    			fadeInButtonAnimation(0);
    		}
    	}
    	else
    	{
    		m_searchResultsFade.setVisibility(View.INVISIBLE);
    		m_searchResultsScrollButton.setVisibility(View.INVISIBLE);
    		m_searchResultsScrollable = false;
    	}

    	m_searchResultsScrollListener.UpdateScrollable(m_searchResultsScrollable);

        if (!m_initializeOnSearchMenuOpenComplete)
        {
            initializeOnSearchMenuOpen();
        }
    }

	@Override
	public void onFocusChange(View v, boolean hasFocus) 
	{
		if(hasFocus && m_isTag)
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
        if(m_isFindMenuChildItemClicked)
        {
        	m_list.collapseAllGroups();
        }
        m_isFindMenuChildItemClicked = false;
	}

	@Override
	protected void onMenuChildItemClick(ExpandableListView parent, View view, int groupPosition, int childPosition, long id) {
		m_isFindMenuChildItemClicked = groupPosition == 0 ? true : false;
	}
}
