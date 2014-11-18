// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.worldpinonmapview;

import android.animation.Animator;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.RelativeLayout.LayoutParams;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class WorldPinOnMapView implements View.OnClickListener
{
	protected MainActivity m_activity = null;
	protected long m_nativeCallerPointer;
	private View m_view = null;
	private RelativeLayout m_uiRoot = null;
	private final int m_stateChangeAnimationTimeMilliseconds = 200;
	private float m_x;
	private float m_y;
	private float m_height;
	private float m_horizontalOffsetPx;
	private TextView m_titleView;
	private TextView m_detailsView;

	public WorldPinOnMapView(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;

		m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_on_map_layout, m_uiRoot, false);
		m_view.setOnClickListener(this);
		m_uiRoot.addView(m_view);
		RelativeLayout.LayoutParams layout = (LayoutParams) m_view.getLayoutParams();
		m_horizontalOffsetPx = layout.width / 2.f;
		m_height = layout.height;

		m_view.setVisibility(View.GONE);
		m_titleView = (TextView)m_view.findViewById(R.id.search_result_on_map_view_title);
		m_detailsView = (TextView)m_view.findViewById(R.id.search_result_on_map_view_details);
	}

	public void destroy()
	{
		m_uiRoot.removeView(m_view);
	}

	public void showAtScreenLocation(final String title, final String details, final float x, final float y, final float openState)
	{
		m_x = x - m_horizontalOffsetPx;
		m_y = y - m_height;

		m_view.setEnabled(true);
		m_titleView.setText(title);
		m_detailsView.setText(details);
		m_view.setVisibility(View.VISIBLE);
		animateToAlpha(openState);
		m_view.setX(m_x);
		m_view.setY(m_y);
	}

	public void updateScreenLocation(final float x, final float y)
	{
		m_x = x - m_horizontalOffsetPx;
		m_y = y - m_height;

		m_view.setX(m_x);
		m_view.setY(m_y);
	}

	public void updateScreenVisibility(final float onScreenState)
	{
		m_view.setAlpha(onScreenState);
	}

	public void dismiss()
	{
		animateToAlpha(0.f);
	}

	public void onClick(View view)
	{
		WorldPinOnMapViewJniMethods.HandleClick(m_nativeCallerPointer);
	}

	private void animateToAlpha(final float alpha)
	{
		m_view.animate()
		.alpha(alpha)
		.setDuration(m_stateChangeAnimationTimeMilliseconds)
		.setListener(new Animator.AnimatorListener()
		{
			public void onAnimationEnd(Animator animation)
			{
				if(alpha == 0.f)
				{
					m_view.setEnabled(false);
					m_view.setX(-m_view.getWidth());
					m_view.setY(-m_view.getHeight());
				}
				else
				{
					m_view.setEnabled(true);
				}
			}

			public void onAnimationCancel(Animator animation) {}
			public void onAnimationRepeat(Animator animation) {}
			public void onAnimationStart(Animator animation) {}
		});
	}
}
