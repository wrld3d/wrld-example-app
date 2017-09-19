// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
package com.eegeo.interiorsexplorer;

import java.util.ArrayList;
import java.util.List;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.BackwardsCompatibleListView;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.view.OnPauseListener;

import android.graphics.Color;
import android.graphics.Rect;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.BounceInterpolator;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class InteriorsExplorerView implements OnPauseListener, View.OnClickListener, View.OnTouchListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_uiRootView = null;
    private View m_topPanel = null;
    private View m_rightPanel = null;
    
    private ImageView m_backButton = null;
    private TextView m_floorNameView = null;
    
    private RelativeLayout m_floorButton = null;
    private TextView m_floorButtonText = null;
    private Boolean m_draggingFloorButton;

    private final long m_stateChangeAnimationTimeMilliseconds = 200;
    private final long m_stateChangeAnimationDelayMilliseconds = m_stateChangeAnimationTimeMilliseconds * 5;
    private final long m_initialJumpThersholdPx = 5;
    
    private float m_topYPosActive;
    private float m_topYPosInactive;

    private RelativeLayout m_floorListContainer;
    private BackwardsCompatibleListView m_floorList;
    private int m_maxFloorsViewableCount;
    private RelativeLayout m_floorLayout;
    private ImageView m_floorUpArrow;
    private ImageView m_floorDownArrow;
    
    private boolean m_isScrolling = false;
    private float m_scrollYCoordinate;
    private Handler m_scrollHandler;
    private Runnable m_scrollingRunnable;
    
    private float m_leftXPosActiveBackButton;
    private float m_leftXPosActiveFloorListContainer;
    private float m_leftXPosInactive;
    
    private InteriorsFloorListAdapter m_floorListAdapter = null;
    private float m_previousYCoordinate;
    private boolean m_isButtonInitialJumpRemoved = false;
    
    private InteriorsExplorerTutorialView m_tutorialView = null;
    
    private boolean m_canProcessButtons;
    private boolean m_isOnScreen = false;
    
    // TODO: Replace these with refs to UX iteration color scheme.
    private final int TextColorNormal = Color.parseColor("#1256B0");
    private final int TextColorDown = Color.parseColor("#CDFC0D");
    private final float ListItemHeight;

    private class PropogateToViewTouchListener implements View.OnTouchListener {
        private View m_target;

        public PropogateToViewTouchListener(View target)
        {
            m_target = target;
        }

        @Override
        public boolean onTouch(View view, MotionEvent event)
        {
            return m_target.onTouchEvent(event);
        }
    }

    public InteriorsExplorerView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        // TODO: Move to Dimens values resource when integrated with Search UX changes.
        ListItemHeight = m_activity.dipAsPx(50.0f);
        
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_uiRootView = m_activity.getLayoutInflater().inflate(R.layout.interiors_explorer_layout, uiRoot, false);

        
        m_topPanel = m_uiRootView.findViewById(R.id.top_panel);
        m_rightPanel = m_uiRootView.findViewById(R.id.right_panel);
        
        m_backButton = (ImageView)m_uiRootView.findViewById(R.id.back_button);
        m_backButton.setOnClickListener(this);
        
        m_floorNameView = (TextView)m_uiRootView.findViewById(R.id.floor_name);
        
        m_floorListContainer = (RelativeLayout)m_uiRootView.findViewById(R.id.interiors_floor_list_container);
        m_floorList = (BackwardsCompatibleListView)m_uiRootView.findViewById(R.id.interiors_floor_item_list);
        m_floorList.setOnTouchListener(new PropogateToViewTouchListener(m_activity.findViewById(R.id.surface)));
        m_floorList.setItemHeight(ListItemHeight);
        
        m_floorListAdapter = new InteriorsFloorListAdapter(m_activity, R.layout.interiors_floor_list_item);
        m_floorList.setAdapter(m_floorListAdapter);
        m_floorLayout = (RelativeLayout) m_uiRootView.findViewById(R.id.interiors_floor_layout);
        m_floorUpArrow = (ImageView) m_uiRootView.findViewById(R.id.interiors_elevator_up_arrow);
        m_floorDownArrow = (ImageView) m_uiRootView.findViewById(R.id.interiors_elevator_down_arrow);
        
        m_floorButton = (RelativeLayout)m_uiRootView.findViewById(R.id.interiors_floor_list_button);
        m_floorButtonText = (TextView)m_uiRootView.findViewById(R.id.interiors_floor_list_button_text);
        m_floorButtonText.setTextColor(TextColorNormal);
        m_draggingFloorButton = false;

        m_floorButton.setOnTouchListener(this);
        
        m_uiRootView.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{				
		    	final float screenWidth = uiRoot.getWidth();
		    	
		    	float controlWidth = m_topPanel.getWidth();
		    	float controlHeight = m_topPanel.getHeight();
		    	
		    	m_topYPosActive = m_activity.dipAsPx(20);
		    	m_topYPosInactive = -controlHeight;
		    	
		    	m_topPanel.setX((screenWidth * 0.5f) - (controlWidth * 0.5f));
		    	m_topPanel.setY(m_topYPosInactive);
		    	
		    	controlWidth = m_floorListContainer.getWidth();
		    	controlHeight = m_floorListContainer.getHeight();
		    	int menuButtonMarginPx = (int) m_activity.getResources().getDimension(R.dimen.menu_button_margin);
		    	
		    	m_leftXPosActiveBackButton = screenWidth - (menuButtonMarginPx + m_backButton.getWidth());
		    	m_leftXPosActiveFloorListContainer = screenWidth - (menuButtonMarginPx + controlWidth - (controlWidth - m_backButton.getWidth()) / 2.0f);
		    	m_leftXPosInactive = screenWidth;
		    	
		    	m_floorListContainer.setX(m_leftXPosInactive);
		    	m_backButton.setX(m_leftXPosInactive);
		    	
		    	int screenHeight = uiRoot.getHeight();
		    	
		    	RelativeLayout.LayoutParams rightPanelLayoutParams = (RelativeLayout.LayoutParams) m_rightPanel.getLayoutParams();
		    	int rightPanelMarginTop = rightPanelLayoutParams.topMargin;
		    	int rightPanelMarginBottom = rightPanelLayoutParams.bottomMargin;
		    	
		    	RelativeLayout.LayoutParams floorListContainerLayoutParams = (RelativeLayout.LayoutParams) m_floorListContainer.getLayoutParams();
		    	int floorListMarginTop = floorListContainerLayoutParams.topMargin;
		    	
		    	int maxFloorContainerHeight = screenHeight - rightPanelMarginTop - m_backButton.getHeight() - floorListMarginTop - rightPanelMarginBottom;
		    	
		    	m_maxFloorsViewableCount = (int) Math.floor(maxFloorContainerHeight / ListItemHeight);
		    	
		    	m_uiRootView.removeOnLayoutChangeListener(this);
			}
        });
        uiRoot.addView(m_uiRootView);
        
        m_tutorialView = new InteriorsExplorerTutorialView(m_activity);
        
        hideFloorLabels();

        m_activity.addOnPauseListener(this);
        
        m_scrollHandler = new Handler();
        m_scrollingRunnable = new Runnable()
		{
			@Override
			public void run()
			{
				scrollingUpdate();
				m_scrollHandler.postDelayed(m_scrollingRunnable, 1);
			}
		};
    }

    private int getListViewHeight(ListView list) 
    {
        return list.getCount() * (int)ListItemHeight;
   }
    
    private int getListViewHeight(int listCount)
    {
    	return listCount * (int)ListItemHeight;
    }

    public void destroy()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        uiRoot.removeView(m_uiRootView);
        m_uiRootView = null;
        
        m_scrollHandler.removeCallbacks(m_scrollingRunnable);
        m_activity.deleteOnPauseListener(this);
    }
    
    public void playShakeSliderAnim()
    {
    	if(!m_isOnScreen)
    	{
    		return;
    	}
    	
    	final long offset = m_floorListContainer.getWidth() / 3;
    	
    	Animation moveLeft = new TranslateAnimation(0, -offset, 0, 0);
    	moveLeft.setDuration(100);
    	
    	Animation bounceRight = new TranslateAnimation(0, offset, 0, 0);
    	bounceRight.setDuration(1000);
    	bounceRight.setInterpolator(new BounceInterpolator());
    	
    	AnimationSet set = new AnimationSet(false);
    	
    	set.addAnimation(moveLeft);
    	set.addAnimation(bounceRight);
    	
    	 m_floorListContainer.startAnimation(set);
    }
    
    public void updateFloors(String[] floorShortNames, int currentlySelectedFloorIndex)
    {
    	List<String> temp = new ArrayList<String>();
    	for(int i = floorShortNames.length - 1; i >= 0; --i)
    	{
    		temp.add(floorShortNames[i]);
    	}
    	
    	m_floorListAdapter.setData(temp);
    	float controlHeight = getListViewHeight(Math.min(m_floorList.getCount(), m_maxFloorsViewableCount));
    	RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams)m_floorListContainer.getLayoutParams();
    	layoutParams.height = (int)controlHeight;
    	m_floorListContainer.setLayoutParams(layoutParams);
    	
    	refreshFloorIndicator(currentlySelectedFloorIndex);
    	moveButtonToFloorIndex(currentlySelectedFloorIndex, false);
    	
    	boolean floorSelectionEnabled = floorShortNames.length > 1;
    	m_floorListContainer.setVisibility(floorSelectionEnabled ? View.VISIBLE : View.GONE);
    	
    	int floorListWidth = m_floorList.getWidth();
    	int floorArrowHeight = m_floorUpArrow.getHeight();
    	m_floorList.setClipBounds(new Rect(-floorListWidth / 2, floorArrowHeight, floorListWidth, (int) controlHeight - floorArrowHeight));
    	
    	m_floorUpArrow.setY(m_floorList.getY());
    	m_floorDownArrow.setY(m_floorList.getY() + controlHeight - m_floorDownArrow.getHeight());
    }
    
    private void setArrowState(boolean showUp, boolean showDown)
    {
    	m_floorUpArrow.setVisibility(showUp ? View.VISIBLE : View.INVISIBLE);
    	m_floorDownArrow.setVisibility(showDown ? View.VISIBLE : View.INVISIBLE);
    }
    
    private void moveButtonToFloorIndex(int floorIndex, Boolean shouldAnimate)
    {
    	int floorCount = m_floorListAdapter.getCount();
    	int halfMaxFloorsViewableCount = (int) Math.ceil(m_maxFloorsViewableCount / 2.0f);
    	
    	int startFloorIndex = floorCount - floorIndex;
    	
    	if(floorCount - startFloorIndex >= halfMaxFloorsViewableCount)
    	{
    		startFloorIndex = Math.max(startFloorIndex - halfMaxFloorsViewableCount, 0);
    	}
    	
    	int screenFloorIndex = floorCount - 1 - floorIndex;
    	
    	if(floorCount > m_maxFloorsViewableCount)
    	{
    		startFloorIndex = Math.min(startFloorIndex, floorCount - m_maxFloorsViewableCount);
    		
    		screenFloorIndex = floorCount - 1 - floorIndex - startFloorIndex;
    	}
    	
    	float topY = (m_floorList.getY()) + (ListItemHeight*0.5f) - m_floorButton.getWidth()*0.5f;
    	float newY = topY + screenFloorIndex * ListItemHeight;
    	newY = Math.max(0.0f, Math.min(getListViewHeight(m_floorList), newY));
    	
    	if(shouldAnimate)
    	{
    		m_floorButton.animate()
    		.y(newY)
    		.setDuration(m_stateChangeAnimationTimeMilliseconds)
    		.start();
    		
    		m_floorList.smoothScrollToPositionFromTop(startFloorIndex, 0);
    	}
    	else
    	{
    		m_floorButton.setY(newY);
    		
			m_floorList.smoothScrollToPositionFromTop(startFloorIndex, 0, 0);
    	}
    	
    	if(floorCount > m_maxFloorsViewableCount)
    	{
    		setArrowState(floorCount - floorIndex > halfMaxFloorsViewableCount, floorCount - startFloorIndex > m_maxFloorsViewableCount);
    	}
    	else
    	{
    		setArrowState(false, false);
    	}
    }
    
    public void setFloorName(String name)
    {
    	m_floorNameView.setText(name);
    }
    
    public void setSelectedFloorIndex(int index)
    {
    	refreshFloorIndicator(index);
    	
    	if(!m_draggingFloorButton)
    	{
    		moveButtonToFloorIndex(index, true);
    	}
    }
    
    public void addTutorialDialogs(boolean showExitDialog, boolean showChangeFloorDialog)
    {
    	m_tutorialView.show(showExitDialog, showChangeFloorDialog);
    }
    
    public void removeTutorialDialogs()
    {
    	m_tutorialView.hide();
    }
    
    public boolean getCanShowChangeFloorTutorialDialog()
    {
    	return m_floorListAdapter.getCount() > 1;
    }
    
    public void setTouchEnabled(boolean enabled)
    {
    	m_canProcessButtons = enabled;
    }
    
    @Override
    public boolean onTouch(View view, MotionEvent event)
    {
    	if(view == m_floorButton)
		{
		    if(event.getAction() == MotionEvent.ACTION_DOWN)
		    {
		    	startDraggingButton(event.getRawY());
		    }
		    else if(event.getAction() == MotionEvent.ACTION_MOVE)
		    {
		    	updateDraggingButton(event.getRawY());
		    }
		    else if(event.getAction() == MotionEvent.ACTION_UP)
		    {
		    	endDraggingButton();
		    }
            return true;
		}
        return false;
	}
    
    private void startDraggingButton(float initialYCoordinate)
    {
    	showFloorLabels();
		m_floorButton.getBackground().setState(new int[] {android.R.attr.state_pressed});
		m_previousYCoordinate = initialYCoordinate;
		m_draggingFloorButton = true;
		m_isButtonInitialJumpRemoved = false;
		
		startScrollingUpdate();
    }
    
    private void updateDraggingButton(float yCoordinate)
    {
    	m_scrollYCoordinate = yCoordinate;
		
    	if(!m_isButtonInitialJumpRemoved) 
    	{
    		detectAndRemoveInitialJump(m_scrollYCoordinate);
    	}
    }

    private void endDraggingButton()
    {
    	endScrollingUpdate();
    	
    	hideFloorLabels();
		m_draggingFloorButton = false;
		m_floorButton.getBackground().setState(new int[] {});

		View firstVisibleChild = m_floorList.getChildAt(0);
		float topY = (m_floorList.getFirstVisiblePosition() * ListItemHeight) - firstVisibleChild.getTop();
		
		float dragParameter = 1.0f - ((topY + m_floorButton.getY()) / (getListViewHeight(m_floorList.getCount() - 1)));
		int floorCount = m_floorListAdapter.getCount()-1;
		int selectedFloor = Math.round(dragParameter * floorCount);
		moveButtonToFloorIndex(selectedFloor, true);

		InteriorsExplorerViewJniMethods.OnFloorSelected(m_nativeCallerPointer, selectedFloor);
    }
    
    private float getScrollSpeed(float t)
    {
    	final float maxScrollSpeed = 22;
    	
    	t = Math.max(-1, Math.min(1, t));
    	return t * Math.abs(t) * maxScrollSpeed;
    }
    
    /**
     * This function will remove the starting jump on slider if detected
     * @param yCoordinate
     */
    private void detectAndRemoveInitialJump(float yCoordinate)
    {
    	float y = yCoordinate;
    	float deltaY = y - m_previousYCoordinate; 
    	if(Math.abs(deltaY) > m_initialJumpThersholdPx)
    	{
    		m_previousYCoordinate += deltaY;
    		m_isButtonInitialJumpRemoved = true;
    	}
    }

    @Override
    public void onClick(View view)
    {
        if(!m_canProcessButtons)
        {
        	return;
        }
        
    	if(view == m_backButton)
        {
    		InteriorsExplorerViewJniMethods.OnDismissedClicked(m_nativeCallerPointer);
        }
    }

    public void animateToActive()
    {
    	m_isOnScreen = true;
    	
    	animateViewToY((int)m_topYPosActive);
        animateViewToX((int)m_leftXPosActiveBackButton, (int) m_leftXPosActiveFloorListContainer, m_isOnScreen);
        
        final Handler handler = new Handler();
        handler.postDelayed(new Runnable()
        {
        	@Override
        	public void run()
        	{
        		int[] rootViewPosition = {0, 0};
        		m_uiRootView.getLocationInWindow(rootViewPosition);
        		int[] backButtonPosition = {0, 0};
        		m_backButton.getLocationInWindow(backButtonPosition);
        		int[] floorButtonPosition = {0, 0};
        		m_floorButton.getLocationInWindow(floorButtonPosition);
        		m_tutorialView.setUIPositions(m_leftXPosActiveFloorListContainer + 14,
												backButtonPosition[1] - rootViewPosition[1],
												m_backButton.getHeight(),
												floorButtonPosition[1] - rootViewPosition[1],
												m_floorButton.getHeight(),
												m_floorListAdapter.getCount() > 1);
        		m_tutorialView.animateToActive(0);
        	}
        }, m_stateChangeAnimationTimeMilliseconds + (m_isOnScreen ? m_stateChangeAnimationDelayMilliseconds : 0));
    }

    public void animateToInactive()
    {
        endScrollingUpdate();
        m_isOnScreen = false;
    	
    	animateViewToY((int)m_topYPosInactive);
        animateViewToX((int)m_leftXPosInactive, (int)m_leftXPosInactive, m_isOnScreen);
        
        m_tutorialView.animateToInactive(m_stateChangeAnimationTimeMilliseconds);
    }

    protected void animateViewToY(final int yAsPx)
    {
    	m_topPanel.animate()
        .y(yAsPx)
        .setDuration(m_stateChangeAnimationTimeMilliseconds);
    }
    
    protected void animateViewToX(final int xAsPxBackButton, final int xAsPxFloorListContainer, final boolean addDelay)
    {
    	long delay = addDelay ? m_stateChangeAnimationDelayMilliseconds : 0;
    	
    	m_floorListContainer.animate()
        .x(xAsPxFloorListContainer)
        .setDuration(m_stateChangeAnimationTimeMilliseconds)
        .setStartDelay(delay);
    	
    	m_backButton.animate()
    	.x(xAsPxBackButton)
        .setDuration(m_stateChangeAnimationTimeMilliseconds)
        .setStartDelay(delay);
    }

    public void animateToIntermediateOnScreenState(final float onScreenState)
    {
        int viewYPx = (int)m_topPanel.getY();
        int newYPx = (int)(m_topYPosInactive + (int)(((m_topYPosActive - m_topYPosInactive) * onScreenState) + 0.5f));

        if(viewYPx != newYPx)
        {
        	m_topPanel.setY(newYPx);
        }
    }

    public void notifyOnPause()
    {
        endScrollingUpdate();
    }
    
    private void refreshFloorIndicator(int floorIndex)
    {
    	int nameIndex = (m_floorListAdapter.getCount()-1)-floorIndex;
    	m_floorButtonText.setText((String)m_floorListAdapter.getItem(nameIndex));
    }
    
    private void hideFloorLabels()
    {
        m_floorButtonText.setTextColor(TextColorNormal);

        m_floorLayout.animate().alpha(0.5f).setDuration(m_stateChangeAnimationTimeMilliseconds);
    }
    
    private void showFloorLabels()
    {
    	m_floorButtonText.setTextColor(TextColorDown);
    	
    	m_floorLayout.animate().alpha(1.0f).setDuration(m_stateChangeAnimationTimeMilliseconds);
    }
    
    private void startScrollingUpdate()
    {
    	if(!m_isScrolling)
    	{
    		m_previousYCoordinate = m_scrollYCoordinate;
			m_scrollingRunnable.run();
    	}
    	
    	m_isScrolling = true;
    }
    
    private void scrollingUpdate()
    {
    	if(m_isScrolling)
    	{
	    	final float joystickScrollThresholdDistance = 0.25f;
	    	
	    	if(!m_isButtonInitialJumpRemoved)
	    	{
	    		detectAndRemoveInitialJump(m_scrollYCoordinate);
	    	}
	    	
	    	float newY = m_floorButton.getY() + (m_scrollYCoordinate - m_previousYCoordinate);
			newY = Math.max(0.0f, Math.min(Math.min(getListViewHeight(m_maxFloorsViewableCount - 1), getListViewHeight(m_floorList.getCount() - 1)), newY));
			m_floorButton.setY(newY);
			m_previousYCoordinate = m_scrollYCoordinate;
			
			float scrollDelta = 0;
			
			float listViewHeightOnScreen = getListViewHeight(m_maxFloorsViewableCount - 1);
			float normalisedNewY = newY / listViewHeightOnScreen;
			
			if(normalisedNewY <= joystickScrollThresholdDistance)
			{
				float localT = normalisedNewY / joystickScrollThresholdDistance;
				scrollDelta = getScrollSpeed(1 - localT);
			}
			else if(normalisedNewY >= 1 - joystickScrollThresholdDistance)
			{
				float localT = (normalisedNewY - (1 - joystickScrollThresholdDistance)) / joystickScrollThresholdDistance;
				scrollDelta = getScrollSpeed(-localT);
			}
			
			m_floorList.scrollListBy(m_activity.dipAsPx(-Math.round(scrollDelta)));
			
			View firstVisibleChild = m_floorList.getChildAt(0);
			float topY = (m_floorList.getFirstVisiblePosition() * ListItemHeight) - firstVisibleChild.getTop();
			
			float dragParameter = 1.0f - ((topY + newY) / (getListViewHeight(m_floorList.getCount() - 1)));
			InteriorsExplorerViewJniMethods.OnFloorSelectionDragged(m_nativeCallerPointer, dragParameter);
			
			int floorCount = m_floorList.getCount();
			if(floorCount > m_maxFloorsViewableCount)
			{
				int firstFloorVisibleInView = m_floorList.getFirstVisiblePosition();
				boolean showUp = firstFloorVisibleInView > 0 || firstVisibleChild.getTop() < -(ListItemHeight * 0.5f);
				boolean showDown = floorCount - firstFloorVisibleInView - (firstVisibleChild.getTop() < 0 ? 1 : 0) > m_maxFloorsViewableCount;
				setArrowState(showUp, showDown);
			}
    	}
    }
    
    private void endScrollingUpdate()
    {
    	m_isScrolling = false;
    	
    	m_scrollHandler.removeCallbacks(m_scrollingRunnable);
    }
}
