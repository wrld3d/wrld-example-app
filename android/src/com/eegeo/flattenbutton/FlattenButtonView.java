package com.eegeo.flattenbutton;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.view.View;
import android.widget.RelativeLayout;
import android.widget.ToggleButton;

public class FlattenButtonView implements View.OnClickListener 
{	
	protected MainActivity m_activity = null;
	protected long m_nativeCallerPointer;
	protected ToggleButton m_view = null;
	
	private float m_xPosActive;
	private float m_xPosInactive;
	
	private final long m_stateChangeAnimationTimeMilliseconds = 200;
	
	public FlattenButtonView(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;

		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				createView();
			}
		});
	}
	
	public void destroy()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
				uiRoot.removeView(m_view);
				m_view = null;
			}
		});
	}
	
	private void createView()
	{
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = (ToggleButton)m_activity.getLayoutInflater().inflate(R.layout.flatten_button_layout, uiRoot, false);
		
		m_view.setOnClickListener(this);
		
		m_xPosActive = 0.0f;
		m_xPosInactive = -m_activity.dipAsPx(40);
		
		m_view.setX(m_xPosInactive);
		m_view.setY(uiRoot.getHeight()*0.5f - m_activity.dipAsPx(20));
		
		uiRoot.addView(m_view);
	}
	
	public void updateViewStateBasedOnFlattening(final boolean isFlattened)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				m_view.setChecked(isFlattened);
			}
		});	
	}
	
	@Override
	public void onClick(View view) 
	{
		m_activity.runOnNativeThread(new Runnable()
		{
			public void run()
			{
				FlattenButtonViewJniMethods.SetFlatten(m_nativeCallerPointer, ((ToggleButton)m_view).isChecked());
			}
		});
	}
	
	public void animateToActive()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				animateViewToX((int)m_xPosActive);
			}
		});	
	}
	
	public void animateToInactive()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				animateViewToX((int)m_xPosInactive);
			}
		});	
	}
	
	protected void animateViewToX(final int xAsPx)
	{
		m_view.animate()
			.x(xAsPx)
			.setDuration(m_stateChangeAnimationTimeMilliseconds);
	}
	
	public void animateToIntermediateOnScreenState(final float onScreenState)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{   
				int viewXPx = (int)m_view.getX();
			    int newXPx = (int)(m_xPosInactive + (int)(((m_xPosActive - m_xPosInactive) * onScreenState) + 0.5f));
			 
			    if(viewXPx != newXPx) 
			    {
				    m_view.setX(newXPx);
			    }
			}
		});
	}
}
