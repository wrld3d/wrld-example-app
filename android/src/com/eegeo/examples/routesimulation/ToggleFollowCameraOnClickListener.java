package com.eegeo.examples.routesimulation;

import java.util.Vector;

import android.view.View;
import android.widget.Button;

import com.eegeo.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class ToggleFollowCameraOnClickListener extends NativeThreadOnClickHandler
{
	Vector<Button> m_buttonsToggledOnFollow;
	
	public ToggleFollowCameraOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer,
			Vector<Button> buttonsToggledOnFollow) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
		m_buttonsToggledOnFollow = buttonsToggledOnFollow;
	}
	
	@Override
	public void onClick(View v) 
	{	
		for (Button button : m_buttonsToggledOnFollow)
		{
			int visibility = (View.VISIBLE == button.getVisibility()) ? View.INVISIBLE : View.VISIBLE;
			button.setVisibility(visibility);
		}
		
		m_nativeMessageRunner.runOnNativeThread(new Runnable()
		{
			public void run()
			{
				onClickNativeThread();
			}
		});
	}

	@Override
	protected void onClickNativeThread() 
	{
		RouteSimulationJniMethods.ToggleFollowCamera(m_nativeCallerPointer);
	}
}