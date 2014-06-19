// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.examples;

import java.util.ArrayList;
import java.util.List;

import android.widget.Button;
import android.widget.RelativeLayout;

import com.eegeo.MainActivity;
import com.eegeo.R;


//this is the java companion type to native PositionJavaPinButtonExample
//
public class HudPinController
{
	private MainActivity m_activity;
	private List<Button> m_buttons = new ArrayList<Button>();

	public HudPinController(MainActivity activity)
	{
		m_activity = activity;
	}

	public int addJavaPinButton()
	{
		int id = m_buttons.size() + 1; //zero is used as "non-existent"
		final Button pin = new Button(m_activity);
		m_buttons.add(pin);

		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		uiRoot.addView(pin);

		return id;
	}

	public void removeJavaPinButton(final int id)
	{
		int index = id - 1;
		final Button pin = m_buttons.get(index);
		m_buttons.remove(index);

		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		uiRoot.removeView(pin);
	}

	public void updatePinButtonScreenLocation(final int pinID, final float x, final float y)
	{
		Button pin = m_buttons.get(pinID - 1);
		RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(80, 80);
		params.leftMargin = (int)x;
		params.topMargin = (int)y;
		pin.setLayoutParams(params);
	}
}
