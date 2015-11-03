// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
package com.eegeo.interiorsexplorer;

import com.eegeo.mobileexampleapp.R;

import android.view.View;
import android.widget.RelativeLayout;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.view.View.MeasureSpec;
import android.util.*;
import java.util.ArrayList;
import java.util.List;

import com.eegeo.entrypointinfrastructure.MainActivity;

public class InteriorsExplorerView implements View.OnClickListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_uiRootView = null;
    private View m_topPanel = null;
    private ImageView m_floorSelectionTop = null;
    private ImageView m_floorSelectionBottom = null;
    
    private ImageView m_backButton = null;
    private TextView m_floorNameView = null;

    private final long m_stateChangeAnimationTimeMilliseconds = 200;
    
    private float m_topYPosActive;
    private float m_topYPosInactive;
    
    private ListView m_floorList;
    private float m_leftXPosActive;
    private float m_leftXPosInactive;
    
    private InteriorsFloorListAdapter m_floorListAdapter = null;
    private InteriorsFloorSelectedListener m_floorListListener = null;
    
    private boolean m_canProcessButtons;

    public InteriorsExplorerView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_uiRootView = m_activity.getLayoutInflater().inflate(R.layout.interiors_explorer_layout, uiRoot, false);
        
        m_topPanel = m_uiRootView.findViewById(R.id.top_panel);
        
        m_floorSelectionTop = (ImageView)m_uiRootView.findViewById(R.id.floor_selection_top);
        m_floorSelectionBottom = (ImageView)m_uiRootView.findViewById(R.id.floor_selection_bottom);
        
        m_backButton = (ImageView)m_uiRootView.findViewById(R.id.back_button);
        m_backButton.setOnClickListener(this);
        
        m_floorNameView = (TextView)m_uiRootView.findViewById(R.id.floor_name);
        
        m_floorList = (ListView)m_uiRootView.findViewById(R.id.interiors_floor_item_list);
        
        m_floorListAdapter = new InteriorsFloorListAdapter(m_activity, R.layout.interiors_floor_list_item);
        m_floorList.setAdapter(m_floorListAdapter);
        
        m_floorListListener = new InteriorsFloorSelectedListener(m_nativeCallerPointer, this);
        m_floorList.setOnItemClickListener(m_floorListListener);
        
        m_uiRootView.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{				
				final float screenHeight = uiRoot.getHeight();
		    	final float screenWidth = uiRoot.getWidth();
		    	
		    	float controlWidth = m_topPanel.getWidth();
		    	float controlHeight = m_topPanel.getHeight();
		    	
		    	m_topYPosActive = controlHeight;
		    	m_topYPosInactive = -controlHeight;
		    	
		    	m_topPanel.setX((screenWidth * 0.5f) - (controlWidth * 0.5f));
		    	m_topPanel.setY(m_topYPosInactive);
		    	
		    	controlWidth = m_floorList.getWidth();
		    	controlHeight = m_floorList.getHeight();
		    	
		    	m_leftXPosActive = 0;
		    	m_leftXPosInactive = -controlWidth;
		    	
		    	m_floorList.setX(m_leftXPosInactive);
		    	m_floorList.setY((screenHeight * 0.5f) - (controlHeight * 0.5f));
		    	
		    	m_floorSelectionTop.setX(m_leftXPosInactive);
		    	m_floorSelectionTop.setY((screenHeight * 0.5f) - (controlHeight * 0.5f) - m_floorSelectionTop.getHeight());
		    	
		    	m_floorSelectionBottom.setX(m_leftXPosInactive);
		    	m_floorSelectionBottom.setY((screenHeight * 0.5f) + (controlHeight * 0.5f));
		    	
		    	m_uiRootView.removeOnLayoutChangeListener(this);
			}
        });
        uiRoot.addView(m_uiRootView);
    }
    
    private int getListViewHeight(ListView list) 
    {
        ListAdapter adapter = list.getAdapter();

        int listviewHeight = 0;

        list.measure(MeasureSpec.makeMeasureSpec(MeasureSpec.UNSPECIFIED, MeasureSpec.UNSPECIFIED), 
                     MeasureSpec.makeMeasureSpec(0, MeasureSpec.UNSPECIFIED));

        listviewHeight = list.getMeasuredHeight() * adapter.getCount() + (adapter.getCount() * list.getDividerHeight());

        return listviewHeight;
   }

    public void destroy()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        uiRoot.removeView(m_uiRootView);
        m_uiRootView = null;
    }
    
    public void updateFloors(String[] floorShortNames, int currentlySelectedFloorIndex)
    {
    	m_floorListListener.SetNumFloors(floorShortNames.length);
    	
    	List<String> temp = new ArrayList<String>();
    	for(int i = floorShortNames.length - 1; i >= 0; --i)
    	{
    		temp.add(floorShortNames[i]);
    	}
    	
    	m_floorListAdapter.setData(temp);
    	
    	final float screenHeight = m_uiRootView.getHeight();
    	float controlHeight = getListViewHeight(m_floorList);
    	m_floorList.setY((screenHeight * 0.5f) - (controlHeight * 0.5f));
    	m_floorSelectionTop.setY((screenHeight * 0.5f) - (controlHeight * 0.5f) - m_floorSelectionTop.getHeight());
    	m_floorSelectionBottom.setY((screenHeight * 0.5f) + (controlHeight * 0.5f));
    }
    
    public void setFloorName(String name)
    {
    	m_floorNameView.setText(name);
    }
    
    public void setSelectedFloorIndex(int index)
    {
    	InteriorsExplorerViewJniMethods.OnFloorSelected(m_nativeCallerPointer, index);
    }
    
    public void setTouchEnabled(boolean enabled)
    {
    	m_canProcessButtons = enabled;
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
    	animateViewToY((int)m_topYPosActive);
        animateViewToX((int)m_leftXPosActive);
    }

    public void animateToInactive()
    {
        animateViewToY((int)m_topYPosInactive);
        animateViewToX((int)m_leftXPosInactive);
    }

    protected void animateViewToY(final int yAsPx)
    {
    	m_topPanel.animate()
        .y(yAsPx)
        .setDuration(m_stateChangeAnimationTimeMilliseconds);
    }
    
    protected void animateViewToX(final int xAsPx)
    {
    	m_floorList.animate()
        .x(xAsPx)
        .setDuration(m_stateChangeAnimationTimeMilliseconds);
    	
    	m_floorSelectionTop.animate()
        .x(xAsPx)
        .setDuration(m_stateChangeAnimationTimeMilliseconds);
    	
    	m_floorSelectionBottom.animate()
        .x(xAsPx)
        .setDuration(m_stateChangeAnimationTimeMilliseconds);
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
}
