// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
package com.eegeo.interiorsexplorer;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.view.MotionEvent;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class InteriorsExplorerTutorialView implements View.OnTouchListener
{
    protected MainActivity m_activity = null;
    
    private RelativeLayout m_uiRoot = null;
    private View m_uiRootView = null;
    private LinearLayout m_uiExitDialog = null;
    private RelativeLayout m_uiExitDialogArrow = null;
    private RelativeLayout m_uiExitDialogOuterArrow = null;
    private LinearLayout m_uiChangeFloorDialog = null;
    private RelativeLayout m_uiChangeFloorDialogArrow = null;
    private RelativeLayout m_uiChangeFloorDialogOuterArrow = null;
    
    private float m_dialogWidth = 0;
    private float m_dialogHeight = 0;
    private float m_newPositionX = 0;
    private float m_dismissButtonPositionY = 0;
    private float m_dismissButtonHeight= 0;
    private float m_floorChangeButtonPositionY = 0;
    private float m_floorChangeButtonHeight = 0;
    private boolean m_showChangeFloorDialog = false;
    
    private final long m_animationTimeMilliseconds = 250;
    
    private final int dialogOutlineSize = 2;
    
    private final int dialogGap = 14;
    
    public InteriorsExplorerTutorialView(MainActivity activity)
    {
        m_activity = activity;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_uiRootView = m_activity.getLayoutInflater().inflate(R.layout.interiors_explorer_tutorial_layout, m_uiRoot, false);
        
        m_uiExitDialog = (LinearLayout) m_uiRootView.findViewById(R.id.interiors_explorer_tutorial_exit_dialog);
        setDialogText(m_uiExitDialog, "Exit Indoors", "Press the exit button to\ngo back outside.");
        m_uiExitDialog.setAlpha(0);
        
        m_uiExitDialogArrow = (RelativeLayout) m_uiExitDialog.findViewById(R.id.interiors_explorer_tutorial_dialog_arrow);
        m_uiExitDialogOuterArrow = (RelativeLayout) m_uiExitDialog.findViewById(R.id.interiors_explorer_tutorial_dialog_outer_arrow);
        
        m_uiChangeFloorDialog = (LinearLayout) m_uiRootView.findViewById(R.id.interiors_explorer_tutorial_change_floor_dialog);
        setDialogText(m_uiChangeFloorDialog, "Change Floors", "Slide the elevator \nbutton to move \nbetween floors.");
        m_uiChangeFloorDialog.setAlpha(0);
        
        m_uiChangeFloorDialogArrow = (RelativeLayout) m_uiChangeFloorDialog.findViewById(R.id.interiors_explorer_tutorial_dialog_arrow);
        m_uiChangeFloorDialogOuterArrow = (RelativeLayout) m_uiChangeFloorDialog.findViewById(R.id.interiors_explorer_tutorial_dialog_outer_arrow);
        
        m_uiRootView.setOnTouchListener(this);
        
        m_uiRootView.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{
		    	m_dialogWidth = m_uiExitDialog.getWidth();
		    	m_dialogHeight = m_uiExitDialog.getHeight();
		    	
		    	resizeDialog(m_uiExitDialog);
		    	resizeDialog(m_uiChangeFloorDialog);
		    	repositionDialogs();
		    	
		    	m_uiRootView.removeOnLayoutChangeListener(this);
			}
        });
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_uiRootView);
        m_uiRootView = null;
    }
    
    @Override
    public boolean onTouch(View view, MotionEvent event)
    {
		hide();
		
		return false;
	}
    
    public void show(boolean showExitDialog, boolean showChangeFloorDialog)
    {
    	m_uiRoot.addView(m_uiRootView);
    	
    	m_uiExitDialog.setVisibility(showExitDialog ? View.VISIBLE : View.INVISIBLE);
    	m_uiChangeFloorDialog.setVisibility(showChangeFloorDialog ? View.VISIBLE : View.INVISIBLE);
    }
    
    public void hide()
    {
        m_uiExitDialog.setAlpha(0.0f);
        m_uiChangeFloorDialog.setAlpha(0.0f);
    	m_uiRoot.removeView(m_uiRootView);
    }
    
    public void setUIPositions(float newPositionX, float dismissButtonPositionY, float dismissButtonHeight, float floorChangeButtonPositionY, float floorChangeButtonHeight, boolean showChangeFloorDialog)
    {
		m_newPositionX = newPositionX;
		m_dismissButtonPositionY = dismissButtonPositionY;
		m_dismissButtonHeight = dismissButtonHeight;
		m_floorChangeButtonPositionY = floorChangeButtonPositionY;
		m_floorChangeButtonHeight = floorChangeButtonHeight;
		m_showChangeFloorDialog = showChangeFloorDialog;
    	
    	repositionDialogs();
    }
    
    private void repositionDialogs()
    {
    	float exitDialogY = m_dismissButtonPositionY - (m_dialogHeight / 2.0f) + (m_dismissButtonHeight / 2.0f);
    	m_uiExitDialog.setX(m_newPositionX - m_dialogWidth);
    	m_uiExitDialog.setY(exitDialogY);
    	m_uiExitDialogArrow.setY((m_dialogHeight - m_uiExitDialogOuterArrow.getHeight()) / 2.0f);
    	m_uiExitDialogOuterArrow.setY((m_dialogHeight - m_uiExitDialogOuterArrow.getHeight()) / 2.0f);
    	
    	float changeDialogY = m_floorChangeButtonPositionY - (m_uiChangeFloorDialog.getHeight() / 2.0f) + (m_floorChangeButtonHeight / 2.0f);
    	m_uiChangeFloorDialog.setX(m_newPositionX - m_uiChangeFloorDialog.getWidth());
    	m_uiChangeFloorDialog.setY(changeDialogY);
    	m_uiChangeFloorDialogArrow.setY((m_uiChangeFloorDialog.getHeight() - m_uiChangeFloorDialogOuterArrow.getHeight()) / 2.0f);
    	m_uiChangeFloorDialogOuterArrow.setY((m_uiChangeFloorDialog.getHeight() - m_uiChangeFloorDialogOuterArrow.getHeight()) / 2.0f);
    	
    	m_uiChangeFloorDialog.setVisibility(m_showChangeFloorDialog ? View.VISIBLE : View.GONE);
    	
    	int currentDialogGap = (int) (changeDialogY - (exitDialogY + m_dialogHeight));
    	if(currentDialogGap < dialogGap)
    	{
    		int offset = (dialogGap - currentDialogGap) / 2;
    		
    		m_uiExitDialog.setY(exitDialogY - offset);
    		m_uiExitDialogArrow.setY(m_uiExitDialogArrow.getY() + offset);
    		m_uiExitDialogOuterArrow.setY(m_uiExitDialogOuterArrow.getY() + offset);
    		
    		m_uiChangeFloorDialog.setY(changeDialogY + offset);
    		m_uiChangeFloorDialogArrow.setY(m_uiChangeFloorDialogArrow.getY() - offset);
    		m_uiChangeFloorDialogOuterArrow.setY(m_uiChangeFloorDialogOuterArrow.getY() - offset);
    	}
    }

    public void animateToActive(long delayMilliseconds)
    {
    	m_uiExitDialog.animate().alpha(1).setDuration(m_animationTimeMilliseconds).setStartDelay(delayMilliseconds + (long) (m_animationTimeMilliseconds * 0.8f));
    	m_uiChangeFloorDialog.animate().alpha(1).setDuration(m_animationTimeMilliseconds).setStartDelay(delayMilliseconds);
    }

    public void animateToInactive(long delayMilliseconds)
    {
    	m_uiExitDialog.animate().alpha(0).setDuration(m_animationTimeMilliseconds).setStartDelay(delayMilliseconds);
    	m_uiChangeFloorDialog.animate().alpha(0).setDuration(m_animationTimeMilliseconds).setStartDelay(delayMilliseconds);
    }
    
    private void setDialogText(LinearLayout dialogRoot, String titleText, String descText)
    {
    	TextView title = (TextView) dialogRoot.findViewById(R.id.interiors_explorer_tutorial_dialog_title);
    	TextView description = (TextView) dialogRoot.findViewById(R.id.interiors_explorer_tutorial_dialog_description);
    	title.setText(titleText);
    	description.setText(descText);
    }
    
    private void resizeDialog(LinearLayout dialogRoot)
    {
    	LinearLayout outerBackground = (LinearLayout) dialogRoot.findViewById(R.id.interiors_explorer_tutorial_dialog_outer_background);
    	LinearLayout innerBackground = (LinearLayout) dialogRoot.findViewById(R.id.interiors_explorer_tutorial_dialog_inner_background);
    	LinearLayout.LayoutParams layoutParams = (LinearLayout.LayoutParams) outerBackground.getLayoutParams();
    	layoutParams.height = innerBackground.getHeight() + m_activity.dipAsPx(dialogOutlineSize * 2);
    	outerBackground.setLayoutParams(layoutParams);
    }
}
