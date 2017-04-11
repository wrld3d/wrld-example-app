// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.initialexperience.intro;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.content.res.Resources;
import android.graphics.Point;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.TranslateAnimation;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class InitialExperienceIntroView implements View.OnClickListener, AnimationListener
{
	private MainActivity m_activity;
	private long m_nativeCallerPointer;
	
	private RelativeLayout m_uiRoot;
	
	private int m_animationDuration;
	
	private RelativeLayout m_banner;
	private RelativeLayout m_bannerInner;
	private ViewGroup m_searchMenuDialog;
	private ViewGroup m_compassDialog;
	private ViewGroup m_mapmodeDialog;
	private ViewGroup m_pinCreationDialog;
	private View m_view;
	private TextView m_welcomeIntroText;
	private TextView m_welcomeIntroDescription;
	
	private Animation m_mainAnimationOn;
	private Animation m_mainAnimationOff;
	
	private boolean m_awaitingInput;
	
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
		m_bannerInner = (RelativeLayout)m_view.findViewById(R.id.welcome_intro_banner_inner);
        m_searchMenuDialog = (ViewGroup)m_view.findViewById(R.id.initial_ux_search_menu_dialog);
        m_compassDialog = (ViewGroup)m_view.findViewById(R.id.initial_ux_compass_dialog);
        m_mapmodeDialog = (ViewGroup)m_view.findViewById(R.id.initial_ux_mapmode_dialog);
        m_pinCreationDialog = (ViewGroup)m_view.findViewById(R.id.initial_ux_pin_creation_dialog);
		m_welcomeIntroText = (TextView)m_view.findViewById(R.id.welcome_intro_text);
		m_welcomeIntroDescription = (TextView)m_view.findViewById(R.id.welcome_intro_description);
        
        Resources resources = m_activity.getResources();
        setDialogText(m_searchMenuDialog,
                      resources.getString(R.string.initial_ux_search_dialog_title),
                      resources.getString(R.string.initial_ux_search_dialog_description));
        setDialogText(m_compassDialog,
                      resources.getString(R.string.initial_ux_compass_dialog_title),
                      resources.getString(R.string.initial_ux_compass_dialog_description));
        setDialogText(m_mapmodeDialog,
                      resources.getString(R.string.initial_ux_mapmode_dialog_title),
                      resources.getString(R.string.initial_ux_mapmode_dialog_description));
        setDialogText(m_pinCreationDialog,
                      resources.getString(R.string.initial_ux_pincreation_dialog_title),
                      resources.getString(R.string.initial_ux_pincreation_dialog_description));
        m_view.setOnClickListener(this);
        
        m_awaitingInput = false;
        
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
	}
    
    public void destroy()
	{
    	m_view.setOnClickListener(null);
	    m_uiRoot.removeView(m_view);
	}

	public void scaleDimensions()
	{
		boolean isTablet = !m_activity.getResources().getBoolean(R.bool.isPhone);
		if(isTablet)
		{
			DisplayMetrics metrics = m_activity.getApplicationContext().getResources().getDisplayMetrics();
			Point screenSize = new Point();
			m_activity.getWindowManager().getDefaultDisplay().getRealSize(screenSize);
			final float dpScale = 1.7f / metrics.density;
			final float tabletScalingFactor = (1705.f / screenSize.y) / dpScale;
			final int introTextYPosition = (int) ((m_banner.getLayoutParams().height * 0.1f) / tabletScalingFactor);
			final int descriptionTextYPosition = (int) ((m_banner.getLayoutParams().height * 0.55f) / tabletScalingFactor);
			final float welcomeDescriptionTextsize = m_welcomeIntroDescription.getTextSize() / metrics.density;
			final float welcomeIntroTextSize = m_welcomeIntroText.getTextSize() / metrics.density;

			RelativeLayout.LayoutParams welcomeDescriptionLayout = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
			welcomeDescriptionLayout.setMargins(0, descriptionTextYPosition, 0, 0);
			welcomeDescriptionLayout.addRule(RelativeLayout.CENTER_HORIZONTAL);
			m_welcomeIntroDescription.setLayoutParams(welcomeDescriptionLayout);
			m_welcomeIntroDescription.setTextSize(TypedValue.COMPLEX_UNIT_SP, welcomeDescriptionTextsize / tabletScalingFactor);

			RelativeLayout.LayoutParams introTextLayout = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
			introTextLayout.setMargins(0, descriptionTextYPosition, 0, 0);
			introTextLayout.addRule(RelativeLayout.CENTER_HORIZONTAL);
			introTextLayout.setMargins(0, introTextYPosition, 0, 0);
			m_welcomeIntroText.setLayoutParams(introTextLayout);
			m_welcomeIntroText.setTextSize(TypedValue.COMPLEX_UNIT_SP, welcomeIntroTextSize / tabletScalingFactor);

			m_banner.getLayoutParams().height = (int) (m_banner.getLayoutParams().height / tabletScalingFactor);
			m_banner.requestLayout();
			m_bannerInner.getLayoutParams().height = (int) (m_bannerInner.getLayoutParams().height / tabletScalingFactor);
			m_bannerInner.requestLayout();
		}
	}
    
    public void show()
    {
		scaleDimensions();

    	m_awaitingInput = true;
    	m_view.setVisibility(View.VISIBLE);

    	m_mainAnimationOn = new TranslateAnimation(-m_uiRoot.getWidth(), 0, 0, 0);
    	m_mainAnimationOn.setDuration(m_animationDuration);
    	m_mainAnimationOn.setInterpolator(new DecelerateInterpolator());
    	m_banner.startAnimation(m_mainAnimationOn);
    	
    	Animation searchDialogAnim = createDialogAnimation(0.0f, 1.0f, m_animationDuration/4, (m_animationDuration/4)*1);
    	m_searchMenuDialog.startAnimation(searchDialogAnim);
    	Animation mapModeAnim = createDialogAnimation(0.0f, 1.0f, m_animationDuration/4, (m_animationDuration/4)*2);
    	m_mapmodeDialog.startAnimation(mapModeAnim);
    	Animation compassAnim = createDialogAnimation(0.0f, 1.0f, m_animationDuration/4, (m_animationDuration/4)*3);
    	m_compassDialog.startAnimation(compassAnim);
    	Animation pinCreateAnim = createDialogAnimation(0.0f, 1.0f, m_animationDuration/4, (m_animationDuration/4)*4);
    	m_pinCreationDialog.startAnimation(pinCreateAnim);
		m_banner.bringToFront();
    }

    public void dismiss()
    {
    	m_awaitingInput = false;
    	m_mainAnimationOff = new TranslateAnimation(0, m_uiRoot.getWidth(), 0, 0);
    	m_mainAnimationOff.setDuration(m_animationDuration);
    	m_mainAnimationOff.setInterpolator(new DecelerateInterpolator());
    	m_mainAnimationOff.setAnimationListener(this);
    	m_banner.startAnimation(m_mainAnimationOff);
    	
    	Animation searchDialogAnim = createDialogAnimation(1.0f, 0.0f, m_animationDuration/4, (m_animationDuration/4)*1);
    	m_searchMenuDialog.startAnimation(searchDialogAnim);
    	Animation mapModeAnim = createDialogAnimation(1.0f, 0.0f, m_animationDuration/4, (m_animationDuration/4)*2);
    	m_mapmodeDialog.startAnimation(mapModeAnim);
    	Animation compassAnim = createDialogAnimation(1.0f, 0.0f, m_animationDuration/4, (m_animationDuration/4)*3);
    	m_compassDialog.startAnimation(compassAnim);
    	Animation pinCreateAnim = createDialogAnimation(1.0f, 0.0f, m_animationDuration/4, (m_animationDuration/4)*4);
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
    
    private void setDialogText(ViewGroup dialogRoot, String titleText, String descText)
    {
    	TextView title = (TextView)dialogRoot.findViewById(R.id.initial_ux_dialog_title);
    	TextView description = (TextView)dialogRoot.findViewById(R.id.initial_ux_dialog_description);
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
		if(m_awaitingInput)
		{
			InitialExperienceIntroJniMethods.OnDismiss(m_nativeCallerPointer);
		}
	}
	
}