// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.examples;

import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.Spinner;
import android.widget.TextView;

import com.eegeo.MainActivity;
import com.eegeo.R;

//this is the java companion type to native JavaHudCrossThreadCommunicationExample
//
public class ThemeReaderWriterHud
{
	private MainActivity m_activity;
	private View m_view;

	public static native void setCurrentTheme(long nativeCallerPointer, String location);
	public static native void readCurrentThemeName(long nativeCallerPointer);

	public ThemeReaderWriterHud(MainActivity activity)
	{
		m_activity = activity;
		m_view = null;
	}

	public void showUi(final long nativeCallerPointer)
	{
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = m_activity.getLayoutInflater().inflate(R.layout.theme_reader_writer_ui, uiRoot, false);

		final Spinner spinner = (Spinner)m_view.findViewById(R.id.themes);

		String items[] = new String[4];
		items[0] = "SummerSanFrancisco";
		items[1] = "WinterNewYork";
		items[2] = "AutumnLondon";
		items[3] = "SpringJapan";
		ArrayAdapter<String> adapter = new ArrayAdapter<String>(m_activity, android.R.layout.simple_spinner_item, items);
		spinner.setAdapter(adapter);

		final Button getTheme = (Button)m_view.findViewById(R.id.get_current_theme_name);
		final Button changeTheme = (Button)m_view.findViewById(R.id.change_theme);

		final TextView currentThemeLabel = (TextView)m_view.findViewById(R.id.current_theme_name_text);
		currentThemeLabel.setText("Current Theme --> ????");

		getTheme.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				readCurrentThemeName(nativeCallerPointer);
			}
		});

		changeTheme.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				String selection = (String)spinner.getSelectedItem();
				setCurrentTheme(nativeCallerPointer, selection);
			}
		});

		uiRoot.addView(m_view);
	}

	public void setCurrentThemeName(final String currentThemeName)
	{
		final TextView currentThemeLabel = (TextView)m_view.findViewById(R.id.current_theme_name_text);
		currentThemeLabel.setText("Current Theme --> " + currentThemeName);
	}

	public void removeUi()
	{
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		uiRoot.removeView(m_view);
	}
}