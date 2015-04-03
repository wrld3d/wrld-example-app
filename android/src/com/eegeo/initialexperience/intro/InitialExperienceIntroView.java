// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.initialexperience.intro;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.TranslateAnimation;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class InitialExperienceIntroView implements View.OnClickListener, AnimationListener
{
	private MainActivity m_activity;
	private long m_nativeCallerPointer;
	
	private RelativeLayout m_uiRoot;
	
	private int m_animationDuration;
	
	private RelativeLayout m_banner;
	private LinearLayout m_menuDialog;
	private LinearLayout m_compassDialog;
	private LinearLayout m_mapmodeDialog;
	private LinearLayout m_pinCreationDialog;
	private View m_view;
	
	private Animation m_mainAnimationOn;
	private Animation m_mainAnimationOff;
	
	InitialExperienceIntroView(MainActivity activity, long nativeCallerPointer)
    {
		m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
        
        createView();
    }

    public void createView()
    {
    	m_animationDuration = 600;
    	
    	m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.initial_experience_intro_layout, m_uiRoot, false);
        
        m_banner = (RelativeLayout)m_view.findViewById(R.id.initial_ux_intro_banner);
        m_menuDialog = (LinearLayout)m_view.findViewById(R.id.initial_ux_menu_dialog);
        m_compassDialog = (LinearLayout)m_view.findViewById(R.id.initial_ux_compass_dialog);
        m_mapmodeDialog = (LinearLayout)m_view.findViewById(R.id.initial_ux_mapmode_dialog);
        m_pinCreationDialog = (LinearLayout)m_view.findViewById(R.id.initial_ux_pin_creation_dialog);
        
        setDialogText(m_menuDialog, "Main Menu", "Start here to begin exploring");
        setDialogText(m_compassDialog, "Compass", "Find me\nLock rotation");
        setDialogText(m_mapmodeDialog, "Map Mode", "Simple 2D View");
        setDialogText(m_pinCreationDialog, "Pin Creation", "Create your own places");
        m_view.setOnClickListener(this);
        
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
	}
    
    public void destroy()
	{
    	m_view.setOnClickListener(null);
	    m_uiRoot.removeView(m_view);
	}
    
    public void show()
    {
    	m_view.setVisibility(View.VISIBLE);

    	m_mainAnimationOn = new TranslateAnimation(-m_uiRoot.getWidth(), 0, 0, 0);
    	m_mainAnimationOn.setDuration(m_animationDuration);
    	m_mainAnimationOn.setInterpolator(new DecelerateInterpolator());
    	m_banner.startAnimation(m_mainAnimationOn);
    	
    	Animation mainDialogAnim = createDialogAnimation(0.0f, 1.0f, m_animationDuration/4, 0);
    	m_menuDialog.startAnimation(mainDialogAnim);
    	Animation mapModeAnim = createDialogAnimation(0.0f, 1.0f, m_animationDuration/4, (m_animationDuration/4)*1);
    	m_mapmodeDialog.startAnimation(mapModeAnim);
    	Animation compassAnim = createDialogAnimation(0.0f, 1.0f, m_animationDuration/4, (m_animationDuration/4)*2);
    	m_compassDialog.startAnimation(compassAnim);
    	Animation pinCreateAnim = createDialogAnimation(0.0f, 1.0f, m_animationDuration/4, (m_animationDuration/4)*3);
    	m_pinCreationDialog.startAnimation(pinCreateAnim);
    }

    public void dismiss()
    {
    	m_mainAnimationOff = new TranslateAnimation(0, m_uiRoot.getWidth(), 0, 0);
    	m_mainAnimationOff.setDuration(m_animationDuration);
    	m_mainAnimationOff.setInterpolator(new DecelerateInterpolator());
    	m_mainAnimationOff.setAnimationListener(this);
    	m_banner.startAnimation(m_mainAnimationOff);
    	
    	Animation mainDialogAnim = createDialogAnimation(1.0f, 0.0f, m_animationDuration/4, 0);
    	m_menuDialog.startAnimation(mainDialogAnim);
    	Animation mapModeAnim = createDialogAnimation(1.0f, 0.0f, m_animationDuration/4, (m_animationDuration/4)*1);
    	m_mapmodeDialog.startAnimation(mapModeAnim);
    	Animation compassAnim = createDialogAnimation(1.0f, 0.0f, m_animationDuration/4, (m_animationDuration/4)*2);
    	m_compassDialog.startAnimation(compassAnim);
    	Animation pinCreateAnim = createDialogAnimation(1.0f, 0.0f, m_animationDuration/4, (m_animationDuration/4)*3);
    	m_pinCreationDialog.startAnimation(pinCreateAnim);
    }
    
    private Animation createDialogAnimation(float startValue, float endValue, int duration, int delayMs)
    {
    	Animation result = new AlphaAnimation(startValue, endValue);
    	result.setDuration(duration);
    	result.setStartOffset(delayMs);
    	result.setInterpolator(new DecelerateInterpolator());
    	result.setFillAfter(true);
    	return result;
    }
    
    private void setDialogText(LinearLayout dialogRoot, String titleText, String descText)
    {
    	ViewGroup dialog = (ViewGroup)dialogRoot.getChildAt(0);
    	TextView title = (TextView)dialog.getChildAt(0);
    	TextView description = (TextView)dialog.getChildAt(1);
    	title.setText(titleText);
    	description.setText(descText);
    }
	
	@Override
	public void onAnimationEnd(Animation arg0) 
	{
		m_view.setVisibility(View.GONE);
		if(m_mainAnimationOff != null)
		{
			m_mainAnimationOff.setAnimationListener(null);
		}
	}

	@Override
	public void onAnimationRepeat(Animation arg0)
	{
	}

	@Override
	public void onAnimationStart(Animation arg0)
	{
	}

	@Override
	public void onClick(View arg0) 
	{
		InitialExperienceIntroJniMethods.OnDismiss(m_nativeCallerPointer);
	}
	
}