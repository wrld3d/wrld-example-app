package com.eegeo.mypincreation;

import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.ToggleButton;

import com.eegeo.flattenbutton.FlattenButtonViewJniMethods;
import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class MyPinCreationButtonView implements View.OnClickListener 
{	
	protected MainActivity m_activity = null;
	protected long m_nativeCallerPointer;
	protected Button m_view = null;
	
	private float m_yPosActive;
	private float m_yPosInactive;
	
	private final long m_stateChangeAnimationTimeMilliseconds = 200;
	
	public MyPinCreationButtonView(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;

		createView();
	}
	
	public void destroy()
	{
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		uiRoot.removeView(m_view);
		m_view = null;
	}
	
	private void createView()
	{
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = (Button)m_activity.getLayoutInflater().inflate(R.layout.poi_creation_button_layout, uiRoot, false);
		
		m_view.setOnClickListener(this);
		
		m_yPosActive = uiRoot.getHeight() - m_activity.dipAsPx(45);
		m_yPosInactive = uiRoot.getHeight();
		
		m_view.setX(uiRoot.getWidth()*0.5f - m_activity.dipAsPx(20));
		m_view.setY(m_yPosInactive);
		
		uiRoot.addView(m_view);
	}
	
	@Override
	public void onClick(View view) 
	{
		MyPinCreationJniMethods.StartButtonPressed(m_nativeCallerPointer);
	}
	
	public void animateToActive()
	{
		animateViewToY((int)m_yPosActive);
	}
	
	public void animateToInactive()
	{
		animateViewToY((int)m_yPosInactive);
	}
	
	protected void animateViewToY(final int xAsPx)
	{
		m_view.animate()
			.y(xAsPx)
			.setDuration(m_stateChangeAnimationTimeMilliseconds);
	}
	
	public void animateToIntermediateOnScreenState(final float onScreenState)
	{
		int viewXPx = (int)m_view.getX();
	    int newXPx = (int)(m_yPosInactive + (int)(((m_yPosActive - m_yPosInactive) * onScreenState) + 0.5f));
	 
	    if(viewXPx != newXPx) 
	    {
		    m_view.setY(newXPx);
	    }
	}
}

