// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.examples.routesimulation;

import java.util.Vector;

import android.util.Log;

import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

import com.eegeo.MainActivity;
import com.eegeo.R;


public class RouteSimulationExampleHud
{
	private MainActivity m_activity;
	private View m_view;
	private ChangeFollowDirectionOnClickListener m_changeFollowDirectionOnClickListener;
	private ToggleDirectFollowOnClickListener m_toggleDirectFollowOnClickListener;
	private ToggleSideOfRoadToDriveOnOnClickListener m_toggleSideOfRoadToDriveOnOnClickListener;
	private DecreaseSpeedFollowedOnClickListener m_decreaseSpeedFollowedOnClickListener;
	private IncreaseSpeedFollowedOnClickListener m_increaseSpeedFollowedOnClickListener;
	private ToggleFollowCameraOnClickListener m_toggleFollowCameraOnClickListener;
	
	public RouteSimulationExampleHud(MainActivity activity, long nativeCallerPointer, boolean followEnabled)
	{
		m_activity = activity;
		m_view = null;

		m_changeFollowDirectionOnClickListener = new ChangeFollowDirectionOnClickListener(
				m_activity,
				nativeCallerPointer
			);

		m_toggleDirectFollowOnClickListener = new ToggleDirectFollowOnClickListener(
				m_activity,
				nativeCallerPointer
			);
		
		m_toggleSideOfRoadToDriveOnOnClickListener = new ToggleSideOfRoadToDriveOnOnClickListener(
				m_activity,
				nativeCallerPointer
			);
			
		m_decreaseSpeedFollowedOnClickListener = new DecreaseSpeedFollowedOnClickListener(
				m_activity,
				nativeCallerPointer
			);
		
		m_increaseSpeedFollowedOnClickListener = new IncreaseSpeedFollowedOnClickListener(
			m_activity,
			nativeCallerPointer
		);
		
		m_toggleFollowCameraOnClickListener = null;
			
		createHud(nativeCallerPointer, followEnabled);
	}

	private void createHud(final long nativeCallerPointer, final boolean followEnabled)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				try
				{
					final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
					m_view = m_activity.getLayoutInflater().inflate(R.layout.route_simulation_menu_layout, uiRoot, false);

					final Button toggleFollow = (Button)m_view.findViewById(R.id.toggle_follow);
					final Button increaseSpeed = (Button)m_view.findViewById(R.id.increase_speed);
					final Button decreaseSpeed = (Button)m_view.findViewById(R.id.decrease_speed);
					final Button changeDirection = (Button)m_view.findViewById(R.id.change_direction);
					final Button toggleDirectFollow = (Button)m_view.findViewById(R.id.toggle_direct_follow);
					final Button toggleRoadSide = (Button)m_view.findViewById(R.id.toggle_road_side);

					int visibility = followEnabled ? View.VISIBLE : View.INVISIBLE;
					increaseSpeed.setVisibility(visibility);
					decreaseSpeed.setVisibility(visibility);
					changeDirection.setVisibility(visibility);
					toggleDirectFollow.setVisibility(visibility);

					increaseSpeed.setOnClickListener(m_increaseSpeedFollowedOnClickListener);
					decreaseSpeed.setOnClickListener(m_decreaseSpeedFollowedOnClickListener);
					changeDirection.setOnClickListener(m_changeFollowDirectionOnClickListener);
					toggleDirectFollow.setOnClickListener(m_toggleDirectFollowOnClickListener);
					toggleRoadSide.setOnClickListener(m_toggleSideOfRoadToDriveOnOnClickListener);
					
					Vector<Button> buttonsToggledOnFollow = new Vector<Button>();
					buttonsToggledOnFollow.add(increaseSpeed);
					buttonsToggledOnFollow.add(decreaseSpeed);
					buttonsToggledOnFollow.add(changeDirection);
					buttonsToggledOnFollow.add(toggleDirectFollow);
					
					m_toggleFollowCameraOnClickListener = new ToggleFollowCameraOnClickListener(
							m_activity,
							nativeCallerPointer,
							buttonsToggledOnFollow
							);
					
					toggleFollow.setOnClickListener(m_toggleFollowCameraOnClickListener);

					uiRoot.addView(m_view);
				}
				catch (Exception e)
				{
					Log.v("RouteSimulationExampleHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
				}
			}
		});
	}

	public void removeHud()
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
}
