// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.examples;

import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.RelativeLayout;

import com.eegeo.MainActivity;
import com.eegeo.R;

public class RouteSimulationExampleHud
{
	private MainActivity m_activity;
	private View m_view;

	public static native void ToggleFollowCamera(long nativeCallerPointer, long nativeCallerProxyPointer);
	public static native void ChangeFollowDirection(long nativeCallerPointer, long nativeCallerProxyPointer);
	public static native void IncreaseSpeedFollowed(long nativeCallerPointer, long nativeCallerProxyPointer);
	public static native void DecreaseSpeedFollowed(long nativeCallerPointer, long nativeCallerProxyPointer);
	public static native void ToggleDirectFollow(long nativeCallerPointer, long nativeCallerProxyPointer);
	public static native void ToggleSideOfRoadToDriveOn(long nativeCallerPointer, long nativeCallerProxyPointer);

	public RouteSimulationExampleHud(MainActivity activity, long nativeCallerPointer, long nativeCallerProxyPointer, boolean followEnabled)
	{
		m_activity = activity;
		m_view = null;

		createHud(nativeCallerPointer, nativeCallerProxyPointer, followEnabled);
	}

	private void createHud(final long nativeCallerPointer, final long nativeCallerProxyPointer, final boolean followEnabled)
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

					toggleFollow.setOnClickListener(new OnClickListener()
					{
						@Override
						public void onClick(View v)
						{
							ToggleFollowCamera(nativeCallerPointer, nativeCallerProxyPointer);

							int visibility = (View.VISIBLE == increaseSpeed.getVisibility()) ? View.INVISIBLE : View.VISIBLE;
							increaseSpeed.setVisibility(visibility);
							decreaseSpeed.setVisibility(visibility);
							changeDirection.setVisibility(visibility);
							toggleDirectFollow.setVisibility(visibility);
						}
					});

					increaseSpeed.setOnClickListener(new OnClickListener()
					{
						@Override
						public void onClick(View v)
						{
							IncreaseSpeedFollowed(nativeCallerPointer, nativeCallerProxyPointer);
						}
					});

					decreaseSpeed.setOnClickListener(new OnClickListener()
					{
						@Override
						public void onClick(View v)
						{
							DecreaseSpeedFollowed(nativeCallerPointer, nativeCallerProxyPointer);
						}
					});

					changeDirection.setOnClickListener(new OnClickListener()
					{
						@Override
						public void onClick(View v)
						{
							ChangeFollowDirection(nativeCallerPointer, nativeCallerProxyPointer);
						}
					});

					toggleDirectFollow.setOnClickListener(new OnClickListener()
					{
						@Override
						public void onClick(View v)
						{
							ToggleDirectFollow(nativeCallerPointer, nativeCallerProxyPointer);
						}
					});

					toggleRoadSide.setOnClickListener(new OnClickListener()
					{
						@Override
						public void onClick(View v)
						{
							ToggleSideOfRoadToDriveOn(nativeCallerPointer, nativeCallerProxyPointer);
						}
					});

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
				try
				{
					final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
					uiRoot.removeView(m_view);
					m_view = null;
				}
				catch (Exception e)
				{
					//Log.v("RouteSimulationExampleHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
				}
			}
		});
	}
}
