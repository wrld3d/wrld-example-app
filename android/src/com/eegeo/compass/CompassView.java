package com.eegeo.compass;

import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.graphics.PorterDuff.Mode;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

public class CompassView implements View.OnClickListener
{
	private MainActivity m_activity = null;
	private long m_nativeCallerPointer;
	private View m_view = null;
	private View m_compassPoint = null;
	private View m_compassOuter = null;
	private View m_compassInner = null;
	private View m_compassPointShadow = null;
	private View m_compassLock = null;
	private int m_colorGold;
	private int m_colorWhite;

	private float m_compassPointOffset;

	private float m_yPosActive;
	private float m_yPosInactive;

	private final long m_stateChangeAnimationTimeMilliseconds = 200;

	public CompassView(MainActivity activity, long nativeCallerPointer)
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
		m_view = m_activity.getLayoutInflater().inflate(R.layout.compass_layout, uiRoot, false);
		m_view.setOnClickListener(this);

		m_compassOuter = m_view.findViewById(R.id.compass_outer_shape);
		m_compassInner = m_view.findViewById(R.id.compass_inner_shape);
		m_compassPoint = m_view.findViewById(R.id.compass_arrow_shape);
		m_compassPointShadow = m_view.findViewById(R.id.compass_arrow_shape_shadow);
		m_compassLock = m_view.findViewById(R.id.compass_lock);

		m_colorGold = m_activity.getResources().getColor(R.color.gold);
		m_colorWhite = m_activity.getResources().getColor(R.color.white);

		RelativeLayout.LayoutParams viewLayout = (LayoutParams) m_compassOuter.getLayoutParams();

		RelativeLayout.LayoutParams compassViewLayout = (LayoutParams) m_compassPoint.getLayoutParams();
		m_compassPointOffset = (viewLayout.width * 0.5f) - (compassViewLayout.width * 0.5f);

		m_yPosActive = m_activity.dipAsPx(16);
		m_yPosInactive = -m_activity.dipAsPx(viewLayout.height);

		m_view.setX((uiRoot.getWidth() * 0.5f) - (viewLayout.width * 0.5f));
		m_view.setY(m_yPosInactive);

		setCompassColours(m_colorGold, m_colorWhite);

		uiRoot.addView(m_view);
		showGpsDisabledView();
	}

	public void updateHeading(float headingAngleRadians)
	{
		final float theta = -headingAngleRadians;

		final float sinTheta = (float)Math.sin(theta);
		final float cosTheta = (float)Math.cos(theta);
		final float x = 0.f;
		final float y = m_activity.dipAsPx(-15.f);
		final float newX = x*cosTheta - y*sinTheta;
		final float newY = y*cosTheta + x*sinTheta;
		m_compassPoint.setX(m_compassPointOffset + newX);
		m_compassPoint.setY(m_compassPointOffset + newY);

		final float shadowOffset = m_activity.dipAsPx(2.0f);
		m_compassPointShadow.setX(m_compassPointOffset + newX + shadowOffset);
		m_compassPointShadow.setY(m_compassPointOffset + newY + shadowOffset);
	}

	public void showGpsDisabledView()
	{
		setCompassColours(m_colorGold, m_colorWhite);

		m_compassLock.animate().alpha(0.0f).setDuration(200).start();
	}

	public void showGpsFollowView()
	{
		setCompassColours(m_colorWhite, m_colorGold);

		m_compassLock.animate().alpha(0.0f).setDuration(200).start();
	}

	public void showGpsCompassModeView()
	{
		setCompassColours(m_colorWhite, m_colorGold);

		m_compassLock.animate().alpha(1.0f).setDuration(200).start();
	}

	@Override
	public void onClick(View view)
	{
		CompassViewJniMethods.HandleClick(m_nativeCallerPointer);
	}

	public void animateToActive()
	{
		animateViewToY((int)m_yPosActive);
	}

	public void animateToInactive()
	{
		animateViewToY((int)m_yPosInactive);
	}

	protected void animateViewToY(final int yAsPx)
	{
		m_view.animate()
		.y(yAsPx)
		.setDuration(m_stateChangeAnimationTimeMilliseconds);
	}

	public void animateToIntermediateOnScreenState(final float onScreenState)
	{
		int viewYPx = (int)m_view.getY();
		int newYPx = (int)(m_yPosInactive + (int)(((m_yPosActive - m_yPosInactive) * onScreenState) + 0.5f));

		if(viewYPx != newYPx)
		{
			m_view.setY(newYPx);
		}
	}

	private void setCompassColours(int bodyColour, int pointColour)
	{
		m_compassOuter.getBackground().setColorFilter(pointColour, Mode.MULTIPLY);
		m_compassOuter.invalidate();

		m_compassPoint.getBackground().setColorFilter(pointColour, Mode.MULTIPLY);
		m_compassPoint.invalidate();

		m_compassInner.getBackground().setColorFilter(bodyColour, Mode.MULTIPLY);
		m_compassInner.invalidate();
	}

}
