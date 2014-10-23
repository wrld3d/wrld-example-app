//Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.searchmenu;

import java.util.HashMap;
import java.util.List;

import android.view.View;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

import com.eegeo.MainActivity;
import com.eegeo.R;
import com.eegeo.categories.CategoryResources;
import com.eegeo.menu.MenuView;
import com.eegeo.menu.MenuViewJniMethods;

public class SearchMenuView extends MenuView
{
	protected View m_closeButtonView = null;
	protected View m_progressSpinner = null;
	protected TextView m_numResultsText = null;
	
	private int m_screenHeightPx;
	private int m_mainContainerOffscreenOffsetYPx;
	private int m_mainContainerOnScreenHeightPx;
	protected int m_totalHeightPx;

	protected int m_dragStartPosYPx;
	protected int m_controlStartPosYPx;
	
	private SearchMenuAdapter m_listAdapter = null;
	
	private ImageView m_headerCategoryImage;
	private TextView m_headerText;
	
	public SearchMenuView(MainActivity activity, long nativeCallerPointer)
	{
		super(activity, nativeCallerPointer);
	}

	@Override
	protected void createView() 
	{	
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = m_activity.getLayoutInflater().inflate(R.layout.search_menu_layout, uiRoot, false);
		RelativeLayout.LayoutParams rootViewLayout = (LayoutParams) m_view.getLayoutParams();
		
		m_list = (ListView)m_view.findViewById(R.id.search_menu_item_list);
		m_dragTabView = m_view.findViewById(R.id.search_menu_drag_tab_view);
		m_dragTabView.setOnClickListener(this);
		m_dragTabView.setOnTouchListener(this);
		
		m_closeButtonView = m_view.findViewById(R.id.search_menu_close_button);
		m_closeButtonView.setOnClickListener(new SearchMenuCloseButtonClickedHandler(m_activity, m_nativeCallerPointer));
		
		m_progressSpinner = m_view.findViewById(R.id.search_menu_spinner);
		m_progressSpinner.setVisibility(View.GONE);

		m_numResultsText = (TextView) m_view.findViewById(R.id.search_menu_num_results_text);
		m_numResultsText.setVisibility(View.GONE);
		
		m_screenHeightPx = uiRoot.getHeight();

		View listContainerView = m_view.findViewById(R.id.search_menu_view_list_container);
		RelativeLayout.LayoutParams viewLayout = (LayoutParams) listContainerView.getLayoutParams();
		
		RelativeLayout.LayoutParams tabLayout = (LayoutParams) m_dragTabView.getLayoutParams();
		int dragTabHeightPx = tabLayout.height;

		m_mainContainerOffscreenOffsetYPx = -rootViewLayout.topMargin;
	    int mainContainerHeightPx = viewLayout.height;
	    m_mainContainerOnScreenHeightPx = mainContainerHeightPx - m_mainContainerOffscreenOffsetYPx;
		
		m_totalHeightPx = mainContainerHeightPx + dragTabHeightPx;
		m_offscreenYPx = m_screenHeightPx;
		m_closedYPx = m_screenHeightPx - m_activity.dipAsPx(m_mainContainerVisibleOnScreenWhenClosedDip) - dragTabHeightPx - m_mainContainerOffscreenOffsetYPx;
		m_openYPx = m_screenHeightPx- m_mainContainerOnScreenHeightPx - dragTabHeightPx;

	    m_view.setY(m_offscreenYPx);
		uiRoot.addView(m_view);
		
		m_listAdapter = new SearchMenuAdapter(m_activity, R.layout.search_menu_list_item);
		m_list.setAdapter(m_listAdapter);
		
		m_headerCategoryImage = (ImageView)m_view.findViewById(R.id.search_menu_header_category_icon);
		m_headerText = (TextView)m_view.findViewById(R.id.search_menu_header_text);
		
		m_menuItemSelectedListener = new SearchMenuItemSelectedListener(m_activity, m_nativeCallerPointer);
		m_list.setOnItemClickListener(m_menuItemSelectedListener);
	}

	public void updateHeader(final String searchText, final boolean pendingQueryResult, final int numResults)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
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
				
				m_headerCategoryImage.setImageResource(CategoryResources.getSmallIconForCategory(m_activity, searchText));
				m_headerText.setText(searchText);
			}
		});
	}
	
	@Override
	public void animateToClosedOnScreen()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				int viewYPx = viewYPx();
				final boolean shouldRunAnimationBasedOnCurrentViewLocation = (!m_dragInProgress && viewYPx != m_closedYPx);
				
				m_activity.runOnNativeThread(new Runnable()
				{
					public void run()
					{ 
					    if(shouldRunAnimationBasedOnCurrentViewLocation || (m_animating && m_animationEndPos.y != m_closedYPx)) 
					    {
					    	int newYPx = m_closedYPx;
					    	log("animateToClosedOnScreen", "y: " + newYPx);
							animateViewToY(newYPx);
					    }
					}
				});
			}
		});	
	}

	@Override
	public void animateToOpenOnScreen()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				int viewYPx = viewYPx();
				final boolean shouldRunAnimationBasedOnCurrentViewLocation = (!m_dragInProgress && viewYPx != m_openYPx);
				
				m_activity.runOnNativeThread(new Runnable()
				{
					public void run()
					{ 
					    if(shouldRunAnimationBasedOnCurrentViewLocation || (m_animating && m_animationEndPos.y != m_openYPx)) 
					    {
					    	int newYPx = m_openYPx;
					    	log("animateToOpenOnScreen", "y: " + newYPx);
							animateViewToY(newYPx);
					    }
					}
				});
			}
		});	
	}

	@Override
	public void animateOffScreen()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				int viewYPx = viewYPx();
				final boolean shouldRunAnimationBasedOnCurrentViewLocation = (!m_dragInProgress && viewYPx != m_offscreenYPx);
				
				m_activity.runOnNativeThread(new Runnable()
				{
					public void run()
					{ 
					    if(shouldRunAnimationBasedOnCurrentViewLocation || (m_animating && m_animationEndPos.y != m_offscreenYPx)) 
					    {
					    	int newYPx = m_offscreenYPx;
					    	log("animateOffScreen", "y: " + newYPx);
							animateViewToY(newYPx);
					    }
					}
				});
			}
		});	
	}
	
	@Override
	public void animateToIntermediateOnScreenState(final float onScreenState)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{   
				int viewYPx = viewYPx();
			    int newYPx = m_offscreenYPx - (int)((Math.abs(m_closedYPx - m_offscreenYPx) * onScreenState) + 0.5f);
			 
			    if(!m_dragInProgress && viewYPx != newYPx) 
			    {
			    	log("animateToIntermediateOnScreenState", "y: " + newYPx + ", t: " + onScreenState);
				    m_view.setY(newYPx);
			    }
			}
		});
	}

	@Override
	public void animateToIntermediateOpenState(final float openState)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{   
				int viewYPx = viewYPx();
			    int newYPx = m_closedYPx + (int)(((m_openYPx - m_closedYPx) * openState) + 0.5f);
			 
			    if(!m_dragInProgress && viewYPx != newYPx) 
			    {
			    	log("animateToIntermediateOpenState", "y: " + newYPx);
				    m_view.setY(newYPx);
			    }
			}
		});
	}

	@Override
	protected void handleDragStart(int xPx, int yPx)
	{
		super.handleDragStart(xPx, yPx);
		m_dragInProgress = true;
	    m_dragStartPosYPx = yPx;
	    m_controlStartPosYPx = viewYPx();
	}

	@Override
	protected void handleDragFinish(int xPx, int yPx)
	{
		m_dragInProgress = false;
	
	    final float yRatioForStateChange = startedClosed(m_controlStartPosXPx) ? 0.35f : 0.65f;
	    final float threshold = (m_screenHeightPx - (m_mainContainerOnScreenHeightPx * yRatioForStateChange));
	    final boolean open = yPx < threshold;
	    final int upYPx = (open ? m_openYPx : m_closedYPx);

		log("ACTION_UP", "y: " + upYPx);
	    m_activity.runOnNativeThread(new Runnable()
		{
			public void run()
			{
				animateViewToY(upYPx);
				MenuViewJniMethods.ViewDragCompleted(m_nativeCallerPointer);
			}
		});
	}
	
	@Override
	protected void handleDragUpdate(int xPx, int yPx) 
	{
	    float newYPx = m_controlStartPosYPx + (yPx - m_dragStartPosYPx);
	    
	    if(newYPx < (m_screenHeightPx - m_totalHeightPx))
	    {
	    	newYPx = (m_screenHeightPx - m_totalHeightPx);
	    }
	    
	    if(newYPx > m_closedYPx)
	    {
	    	newYPx = m_closedYPx;
	    }
	    
	    float normalisedDragState = Math.abs(newYPx - m_closedYPx) / (Math.abs(m_openYPx - m_closedYPx));
	    final float clampedNormalisedDragState = clamp(normalisedDragState, 0.f, 1.f);
	    
	    m_activity.runOnNativeThread(new Runnable()
		{
			public void run()
			{
				MenuViewJniMethods.ViewDragInProgress(m_nativeCallerPointer, clampedNormalisedDragState);
			}
		});
	    
	    m_view.setY(newYPx);
	    log("ACTION_MOVE", "y: " + newYPx+ ", clamp: " + clampedNormalisedDragState);
	}

	@Override
	protected Boolean startedClosed(int controlStartPosYDip)
	{
		int deltaClosed = Math.abs(controlStartPosYDip - m_closedYPx);
		int deltaOpen = Math.abs(controlStartPosYDip - m_openYPx);
		return deltaClosed < deltaOpen;
	}

	@Override
	protected boolean isClosed()
	{
		return viewYPx() == m_closedYPx; 
	}

	@Override
	protected boolean isOpen()
	{
		return viewYPx() == m_openYPx;
	}

	@Override
	protected void refreshListData(List<String> groups,
			List<Boolean> groupsExpandable,
			HashMap<String, List<String>> groupToChildrenMap) 
	{
		m_listAdapter.setData(groupToChildrenMap.get("Search"));
	}
}

