// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.menu;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

import android.util.Log;
import android.view.View;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import android.widget.RelativeLayout;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

public abstract class MenuView implements View.OnClickListener, MenuAnimationStateCallback
{
	protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    protected View m_view = null;
    protected ListView m_list = null;
    protected OnItemClickListener m_menuItemSelectedListener = null;
    protected Boolean m_loggingEnabled = true;
    
    protected boolean m_animating = false;
    
    protected MenuAnimationHandler m_menuAnimationHandler = null;

    protected abstract void refreshListData(List<String> groups, List<Boolean> groupsExpandable, HashMap<String, List<String>> groupToChildrenMap);

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
    	m_animating = false;
    	
    	MenuViewJniMethods.ViewCloseCompleted(m_nativeCallerPointer);
    	
        m_list.setVisibility(View.GONE);
    }
    
    @Override
	public void onOpenOnScreenAnimationComplete()
	{
    	m_animating = false;
    	
    	m_list.setEnabled(true);
    	
    	MenuViewJniMethods.ViewOpenCompleted(m_nativeCallerPointer);
	}

    public float normalisedAnimationProgress()
    {
    	return m_menuAnimationHandler.getOpenOnScreenState();
    }
    
    public void animateToClosedOnScreen()
    {
    	if(m_animating || m_menuAnimationHandler.isClosedOnScreen())
    	{
    		return;
    	}
    	
    	m_animating = true;
    	
    	m_menuAnimationHandler.playToClosedOnScreen();
    	
    	m_list.setEnabled(false);
    }

    public void animateToOpenOnScreen()
    {
    	if(m_animating || m_menuAnimationHandler.isOpenOnScreen())
    	{
    		return;
    	}
    	
    	m_animating = true;
    	
    	m_menuAnimationHandler.playToOpenOnScreen();
    }

    public void animateOffScreen()
    {
    	if(m_animating || m_menuAnimationHandler.isOffScreen())
    	{
    		return;
    	}
    	
    	m_animating = true;
    	
    	m_menuAnimationHandler.playToOffScreen();
    	
    	m_list.setEnabled(false);
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
        final boolean[] groupIsExpandable,
        final String[] childJson)
    {
        List<String> groups = Arrays.asList(groupNames);
        List<Boolean> groupsExpandable = toBooleanList(groupIsExpandable);
        HashMap<String, List<String>> childMap = new HashMap<String,List<String>>();
        int childIndex = 0;
        for(int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
        {
            int size = groupSizes[groupIndex];
            ArrayList<String> children = new ArrayList<String>();
            for(int i = 0; i < size; i++)
            {
                children.add(childJson[childIndex]);
                childIndex++;
            }
            childMap.put(groupNames[groupIndex], children);
        }

        refreshListData(groups, groupsExpandable, childMap);
    }

    protected List<Boolean> toBooleanList(boolean[] booleanArray)
    {
        ArrayList<Boolean> list = new ArrayList<Boolean>();
        for(int i = 0; i < booleanArray.length; i++)
        {
            list.add(booleanArray[i]);
        }
        return list;
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
}
