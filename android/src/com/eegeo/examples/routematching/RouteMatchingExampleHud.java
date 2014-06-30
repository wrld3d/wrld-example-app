// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.examples.routematching;

import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

import com.eegeo.MainActivity;
import com.eegeo.R;

public class RouteMatchingExampleHud
{
	private MainActivity m_activity;
	private View m_view;
	private ToggleRouteMatchingOnClickListener m_toggleRouteMatchingOnClickListener;

	public RouteMatchingExampleHud(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_view = null;
		
		m_toggleRouteMatchingOnClickListener = new ToggleRouteMatchingOnClickListener(
				m_activity,
				nativeCallerPointer
			);
		
		createHud();
	}

	private void createHud()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				try
				{
					final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
					m_view = m_activity.getLayoutInflater().inflate(R.layout.route_matching_menu_layout, uiRoot, false);

					final Button toggleRouteMatching = (Button)m_view.findViewById(R.id.toggle_match);

					toggleRouteMatching.setOnClickListener(m_toggleRouteMatchingOnClickListener);

					uiRoot.addView(m_view);
				}
				catch (Exception e)
				{
					Log.v("RouteMatchingExampleHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
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
