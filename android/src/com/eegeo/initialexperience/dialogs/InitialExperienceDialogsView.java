package com.eegeo.initialexperience.dialogs;

import android.text.method.LinkMovementMethod;
import android.view.View;
import android.view.animation.AccelerateDecelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.ScaleAnimation;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class InitialExperienceDialogsView implements View.OnClickListener, AnimationListener
{
	private MainActivity m_activity;
	private long m_nativeCallerPointer;
	
	public enum DialogStep
	{
		INVALID,
		SearchMenu,
		PrimaryMenu,
		Compass,
		PinCreation,
		Flatten,
		SourceCode,
		MAX
	}
	
	private View m_view;
	private LinearLayout m_dialogView;
	private Button m_closeButton;
	private TextView m_titleText;
	private TextView m_descriptionText;
	
	private DialogStep[] m_enumValues;
	private RelativeLayout m_uiRoot;
	private View m_arrowUp;
	private View m_arrowDown;
	private View m_arrowRight;
	private View m_arrowLeft;
	private RelativeLayout.LayoutParams m_defaultLayoutParams;
	
	private Animation m_animationIn;
	private Animation m_animationOut;
	
	InitialExperienceDialogsView(MainActivity activity, long nativeCallerPointer)
    {
		m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
        
        createView();
    }

    public void createView()
    {
    	m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.initial_experience_layout, m_uiRoot, false);
        m_dialogView = (LinearLayout)m_view.findViewById(R.id.initial_ux_view);
        m_defaultLayoutParams = (RelativeLayout.LayoutParams)m_dialogView.getLayoutParams();
        
        m_closeButton = (Button)m_dialogView.findViewById(R.id.initial_ux_dialog_close_button);
        m_titleText = (TextView)m_dialogView.findViewById(R.id.initial_ux_dialog_title);
        m_descriptionText = (TextView)m_dialogView.findViewById(R.id.initial_ux_dialog_description);
        m_descriptionText.setMovementMethod(LinkMovementMethod.getInstance());
        m_arrowUp = m_dialogView.findViewById(R.id.initial_ux_dialog_arrow_up);
        m_arrowDown = m_dialogView.findViewById(R.id.initial_ux_dialog_arrow_down);
        m_arrowRight = m_dialogView.findViewById(R.id.initial_ux_dialog_arrow_right);
        m_arrowLeft = m_dialogView.findViewById(R.id.initial_ux_dialog_arrow_left);
        
        m_closeButton.setOnClickListener(this);

        m_enumValues = DialogStep.values();
        
        m_dialogView.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);
        
        setModalBackgroundActive(false);
	}
    
    public void setModalBackgroundActive(boolean active)
    {
    	m_view.setClickable(active);
    }

	public void destroy()
	{
	    m_uiRoot.removeView(m_view);
	}
    public void showDialog(int dialogId, String title, String description)
    {
    	// Validate id coming in.
    	DialogStep step = m_enumValues[dialogId];
    	showDialog(step, title, description);
    }
    
    private void showDialog(DialogStep step, String title, String description)
    {
    	m_arrowUp.setVisibility(View.GONE);
    	m_arrowDown.setVisibility(View.GONE);
    	m_arrowRight.setVisibility(View.GONE);
    	m_arrowLeft.setVisibility(View.GONE);
    	
    	RelativeLayout.LayoutParams layout = new RelativeLayout.LayoutParams(m_defaultLayoutParams);
    	float animationAnchorX = 0.0f;
    	float animationAnchorY = 0.0f;
    	
    	switch(step)
    	{
    	case SearchMenu:
    		m_arrowRight.setVisibility(View.VISIBLE);
    		layout.addRule(RelativeLayout.ALIGN_PARENT_RIGHT);
    		layout.setMargins(m_activity.dipAsPx(0), m_activity.dipAsPx(20), m_activity.dipAsPx(50), m_activity.dipAsPx(0));
    		animationAnchorX = 1.0f;
    		animationAnchorY = 0.5f;
    		break;
    		
    	case PrimaryMenu:
    		m_arrowLeft.setVisibility(View.VISIBLE);
    		layout.addRule(RelativeLayout.ALIGN_PARENT_LEFT);
    		layout.setMargins(m_activity.dipAsPx(50), m_activity.dipAsPx(20), m_activity.dipAsPx(0), m_activity.dipAsPx(0));
    		animationAnchorX = 0.0f;
    		animationAnchorY = 0.5f;
    		break;
    		
    	case Compass:
    		m_arrowUp.setVisibility(View.VISIBLE);
    		layout.addRule(RelativeLayout.CENTER_HORIZONTAL);
    		layout.setMargins(m_activity.dipAsPx(0), m_activity.dipAsPx(70), m_activity.dipAsPx(0), m_activity.dipAsPx(0));
    		animationAnchorX = 0.5f;
    		animationAnchorY = 0.0f;
    		break;
    		
    	case PinCreation:
    		m_arrowDown.setVisibility(View.VISIBLE);
    		layout.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
    		layout.addRule(RelativeLayout.CENTER_HORIZONTAL);
    		layout.setMargins(m_activity.dipAsPx(0), m_activity.dipAsPx(0), m_activity.dipAsPx(0), m_activity.dipAsPx(50));
    		animationAnchorX = 0.5f;
    		animationAnchorY = 1.0f;
    		break;
    		
    	case Flatten:
    		m_arrowLeft.setVisibility(View.VISIBLE);
    		layout.addRule(RelativeLayout.CENTER_VERTICAL);
    		layout.setMargins(m_activity.dipAsPx(40), m_activity.dipAsPx(0), m_activity.dipAsPx(0), m_activity.dipAsPx(0));
    		animationAnchorX = 0.0f;
    		animationAnchorY = 0.5f;
    		break;
    		
    	case SourceCode:
    		layout.addRule(RelativeLayout.CENTER_IN_PARENT);
    		layout.setMargins(m_activity.dipAsPx(0), m_activity.dipAsPx(0), m_activity.dipAsPx(0), m_activity.dipAsPx(00));
    		animationAnchorX = 0.5f;
    		animationAnchorY = 0.5f;
    		break;
    		
    		default: break;
    	}
    	
    	m_dialogView.setLayoutParams(layout);
    	m_titleText.setText(title);
    	m_descriptionText.setText(description);
    	
    	m_animationIn = createAnimation(0.0f, 1.0f, animationAnchorX, animationAnchorY);
    	m_animationOut = createAnimation(1.0f, 0.0f, animationAnchorX, animationAnchorY);
    	m_dialogView.setVisibility(View.VISIBLE);
    	m_dialogView.startAnimation(m_animationIn);
    }
    
    public void dismissCurrentDialog()
    {
    	m_animationOut.setAnimationListener(this);
    	m_dialogView.startAnimation(m_animationOut);
    }

	@Override
	public void onClick(View v) 
	{
		InitialExperienceDialogsJniMethods.CloseButtonClicked(m_nativeCallerPointer);
	}
	
	private Animation createAnimation(float startScale, float endScale, float anchorX, float anchorY)
	{
		Animation anim = new ScaleAnimation(startScale, endScale, startScale, endScale, Animation.RELATIVE_TO_SELF, anchorX, Animation.RELATIVE_TO_SELF, anchorY);
		anim.setDuration(400);
		anim.setInterpolator(new AccelerateDecelerateInterpolator());
		return anim;
	}

	@Override
	public void onAnimationEnd(Animation animation) 
	{
		m_dialogView.setVisibility(View.GONE);
		m_animationOut.setAnimationListener(null);
	}

	@Override
	public void onAnimationRepeat(Animation animation)
	{
		
	}

	@Override
	public void onAnimationStart(Animation animation) 
	{
		
	}
	
}
