// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.menu;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

import org.json.JSONObject;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.ExpandableListView;
import android.widget.RelativeLayout;

public abstract class MenuView implements View.OnClickListener, MenuAnimationStateCallback
{
	protected enum MenuState
	{
	    OFF_SCREEN,
	    CLOSED_ON_SCREEN,
	    OPEN_ON_SCREEN
	};
	
	protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    protected View m_view = null;
    protected MenuExpandableListView m_list = null;
    protected MenuExpandableListOnClickListener m_expandableListOnClickListener = null;
    
    protected Boolean m_loggingEnabled = true;
    
    protected MenuState m_menuState = MenuState.OFF_SCREEN;
    protected boolean m_animating = false;
    
    protected MenuAnimationHandler m_menuAnimationHandler = null;

    protected abstract void refreshListData(List<String> groups, HashMap<String, List<String>> groupToChildrenMap);
    
    protected abstract void onMenuChildItemClick(ExpandableListView parent, View view, int groupPosition, int childPosition, long id);

    public MenuView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
    }

    public void destroy()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        uiRoot.removeView(m_view);
        m_view = null;
    }

    public boolean isAnimating()
    {
        return m_animating;
    }

    public boolean isDragging()
    {
        return false;
    }

    public void updateAnimation(final float deltaSeconds)
    {
    	// TODO: IR: animations are handled automatically via MenuAnimationHandler
    }
    
    @Override
    public void onOffScreenAnimationComplete()
    {
    	m_animating = false;
    }
    
    @Override
    public void onClosedOnScreenAnimationComplete()
    {
    	MenuViewJniMethods.ViewCloseCompleted(m_nativeCallerPointer);
    	
    	m_animating = false;
    	
        m_list.setVisibility(View.GONE);
    }
    
    @Override
	public void onOpenOnScreenAnimationComplete()
	{
    	MenuViewJniMethods.ViewOpenCompleted(m_nativeCallerPointer);
    	
    	m_animating = false;
    	
    	m_list.setEnabled(true);
	}

    public float normalisedAnimationProgress()
    {
    	return m_menuAnimationHandler.getOpenOnScreenState();
    }
    
    public void animateToClosedOnScreen()
    {
    	if((m_animating && m_menuState != MenuState.OFF_SCREEN) || m_menuAnimationHandler == null || m_menuAnimationHandler.isClosedOnScreen())
    	{
    		return;
    	}

    	m_animating = true;
    	
    	m_menuAnimationHandler.playToClosedOnScreen();
    	
    	m_list.setEnabled(false);
    	
    	m_menuState = MenuState.CLOSED_ON_SCREEN;
    	
    	Handler closeHandler = new Handler();
    	closeHandler.postDelayed(new Runnable()
    	{
			@Override
			public void run()
			{
				MenuViewJniMethods.ViewCloseCompleted(m_nativeCallerPointer);
			}
		}, 1);
    }

    public void animateToOpenOnScreen()
    {
    	if(m_animating || m_menuAnimationHandler.isOpenOnScreen())
    	{
    		return;
    	}
    	
    	m_animating = true;
    	
    	m_menuAnimationHandler.playToOpenOnScreen();
    	
    	m_menuState = MenuState.OPEN_ON_SCREEN;


    	Handler openHandler = new Handler();
    	openHandler.postDelayed(new Runnable()
    	{
			@Override
			public void run()
			{
				MenuViewJniMethods.ViewOpenStarted(m_nativeCallerPointer);
			}
		}, 1);
    }

    public void animateOffScreen()
    {
    	if(m_animating) 
    	{
    		if(m_menuAnimationHandler.isOffScreen()) 
    		{
				m_menuAnimationHandler.cancelAnimation();
				
				m_animating = false;
    		} 
    	} 
    	else if(m_menuAnimationHandler.isOffScreen())
    	{
    		m_menuState = MenuState.OFF_SCREEN;
    	}
    	
    	if(m_animating || m_menuAnimationHandler.isOffScreen())
    	{
    		return;
    	}
    	
    	m_animating = true;
    	
    	m_menuAnimationHandler.playToOffScreen();
    	
    	m_list.setEnabled(false);
    	
    	m_menuState = MenuState.OFF_SCREEN;
    }
    
    public void animateToIntermediateOnScreenState(final float onScreenState)
    {
    	if(m_animating)
    	{
    		return;
    	}
    	
    	m_menuAnimationHandler.setToIntermediateOnScreenState(onScreenState);
    }

    public void animateToIntermediateOpenState(final float openState)
    {
    	if(m_animating)
    	{
    		return;
    	}
    	
    	m_menuAnimationHandler.setToIntermediateOpenState(openState);
    }

    public void populateData(
        final long nativeCallerPointer,
        final String[] groupNames,
        final int[] groupSizes,
        final String[] childJson)
    {
        List<String> groups = Arrays.asList(groupNames);
        HashMap<String, List<String>> childMap = new HashMap<String,List<String>>();
        
        int childIndex = 1;
        
        for(int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
        {
            int sizeWithoutHeader = groupSizes[groupIndex] - 1;
            
            ArrayList<String> children = new ArrayList<String>();
            for(int i = 0; i < sizeWithoutHeader; ++i)
            {
            	String json = childJson[childIndex];
                children.add(json);
                childIndex++;
            }
           
            childIndex++;
            
            childMap.put(getNameFromJson(groupNames[groupIndex]), children);
        }

        refreshListData(groups, childMap);
    }
    
    private String getNameFromJson(String groupJson)
    {
    	try
		{
			JSONObject json = new JSONObject(groupJson);
			String name = json.getString("name");
			return name;
		}
		catch(Exception e)
		{
			Log.e("MenuView", String.format("Unable to parse name from group JSON: %s", e.toString()));
			return null;
		}
    }

    protected void handleDragStart(int xPx, int yPx)
    {

    }

    protected abstract void handleDragUpdate(int xPx, int yPx);

    protected abstract void handleDragFinish(int xPx, int yPx);

    public void onClick(View view)
    {
        if(!canInteract())
        {
            return;
        }

        MenuViewJniMethods.ViewClicked(m_nativeCallerPointer);
    }

    protected void log(String label, String message)
    {
        if(m_loggingEnabled)
        {
            Log.v("Eegeo", label + " :: " + message);
        }
    }

    protected boolean canInteract()
    {
    	return !m_animating && (m_menuAnimationHandler.isClosedOnScreen() || m_menuAnimationHandler.isOpenOnScreen());
    }
	
    @Override
	public void onOpenOnScreenAnimationStart() 
	{
        m_list.setVisibility(View.VISIBLE);
	}

	public void toggleSection(int sectionIndex)
    {
        m_list.expandGroup(sectionIndex);
    }
}
