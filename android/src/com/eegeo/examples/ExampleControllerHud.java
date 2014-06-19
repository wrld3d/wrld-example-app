// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.examples;

import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.Spinner;

import com.eegeo.MainActivity;
import com.eegeo.R;

public class ExampleControllerHud
{
	private MainActivity m_activity = null;
	private View m_view = null;
	private Spinner m_spinner = null;
	private String[] m_items;
	private boolean m_spinnerEnabled = false;

	public static native void ActivatePrevious(long nativeCallerPointer);
	public static native void ActivateNext(long nativeCallerPointer);
	public static native void SelectExample(long nativeCallerPointer, String selectedExample);

	public ExampleControllerHud(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		createHud(nativeCallerPointer);
	}

	private void createHud(final long nativeCallerPointer)
	{
		try
		{
			final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
			m_view = m_activity.getLayoutInflater().inflate(R.layout.example_controller_layout, uiRoot, false);

			final Button previousExample = (Button)m_view.findViewById(R.id.previous_example);

			previousExample.setOnClickListener(new OnClickListener()
			{
				@Override
				public void onClick(View v)
				{
					ActivatePrevious(nativeCallerPointer);
				}
			});

			final Button nextExample = (Button)m_view.findViewById(R.id.next_example);

			nextExample.setOnClickListener(new OnClickListener()
			{
				@Override
				public void onClick(View v)
				{
					ActivateNext(nativeCallerPointer);
				}
			});

			previousExample.setVisibility(View.INVISIBLE);
			nextExample.setVisibility(View.INVISIBLE);

			uiRoot.addView(m_view);
		}
		catch (Exception e)
		{
			Log.v("ExampleControllerHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
		}
	}

	public void showViews()
	{
		final Button previousExample = (Button)m_view.findViewById(R.id.previous_example);
		final Button nextExample = (Button)m_view.findViewById(R.id.next_example);

		previousExample.setVisibility(View.VISIBLE);
		nextExample.setVisibility(View.VISIBLE);

		m_spinnerEnabled = true;
		if(m_spinner != null)
		{
			m_spinner = (Spinner)m_view.findViewById(R.id.example_list);
			m_spinner.setEnabled(m_spinnerEnabled);
		}
	}

	public void removeHud()
	{
		try
		{
			final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
			uiRoot.removeView(m_view);
			m_view = null;
		}
		catch (Exception e)
		{
			//Log.v("ExampleControllerHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
		}
	}

	public void PopulateExampleSpinner(final long nativeCallerPointer, final String[] items)
	{
		m_items = items;

		m_spinner = (Spinner)m_view.findViewById(R.id.example_list);

		ArrayAdapter<String> adapter = new ArrayAdapter<String>(m_activity, android.R.layout.simple_spinner_item, items);
		m_spinner.setAdapter(adapter);
		m_spinner.setEnabled(m_spinnerEnabled);

		m_spinner.setOnItemSelectedListener(new OnItemSelectedListener()
		{
			int spinnerCurrentSelection = -1;

			@Override
			public void onItemSelected(AdapterView<?> parentView, View selectedItemView,
			                           int position, long id)
			{
				if(spinnerCurrentSelection >= 0 && spinnerCurrentSelection != position)
				{
					String selection = (String)m_spinner.getSelectedItem();
					SelectExample(nativeCallerPointer, selection);
				}
				spinnerCurrentSelection = position;
			}

			@Override
			public void onNothingSelected(AdapterView<?> parentView)
			{
			}
		});
	}

	public void UpdateExampleSpinnerEntry(final String item)
	{
		for(int i = 0; i < m_items.length; ++ i)
		{
			if(m_items[i].equals(item))
			{
				m_spinner.setSelection(i);
			}
		}
	}
}
