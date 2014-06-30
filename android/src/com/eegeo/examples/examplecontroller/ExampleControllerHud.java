// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.examples.examplecontroller;

import android.util.Log;
import android.view.View;
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
	private SelectPreviousExampleOnClickListener m_previousExampleClickListener = null;
	private SelectNextExampleOnClickListener m_nextExampleClickListener = null;
	private SelectExampleOnItemSelectedListener m_selectExampleOnItemSelectedListener = null;
	private Spinner m_spinner = null;
	private String[] m_items;
	private boolean m_spinnerEnabled = false;

	public ExampleControllerHud(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;

		m_previousExampleClickListener = new SelectPreviousExampleOnClickListener(
				m_activity,
				nativeCallerPointer
			);

		m_nextExampleClickListener = new SelectNextExampleOnClickListener(
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
					m_view = m_activity.getLayoutInflater().inflate(R.layout.example_controller_layout, uiRoot, false);

					final Button previousExample = (Button)m_view.findViewById(R.id.previous_example);
					previousExample.setOnClickListener(m_previousExampleClickListener);

					final Button nextExample = (Button)m_view.findViewById(R.id.next_example);
					nextExample.setOnClickListener(m_nextExampleClickListener);

					previousExample.setVisibility(View.INVISIBLE);
					nextExample.setVisibility(View.INVISIBLE);

					uiRoot.addView(m_view);
				}
				catch (Exception e)
				{
					Log.v("ExampleControllerHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
				}
			}
		});
	}

	public void showViews()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
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
					//Log.v("ExampleControllerHud", e.getMessage() == null ? "Error, but no message?!" : e.getMessage());
				}
			}
		});
	}

	public void PopulateExampleSpinner(final long nativeCallerPointer, final String[] items)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				m_items = items;

				m_spinner = (Spinner)m_view.findViewById(R.id.example_list);

				ArrayAdapter<String> adapter = new ArrayAdapter<String>(m_activity, android.R.layout.simple_spinner_item, items);
				m_spinner.setAdapter(adapter);
				m_spinner.setEnabled(m_spinnerEnabled);
				
				m_selectExampleOnItemSelectedListener = new SelectExampleOnItemSelectedListener(
						m_spinner,
						m_activity,
						nativeCallerPointer
					);
		
				m_spinner.setOnItemSelectedListener(m_selectExampleOnItemSelectedListener);
			}
		});
	}

	public void UpdateExampleSpinnerEntry(final String item)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{

				for(int i = 0; i < m_items.length; ++ i)
				{
					if(m_items[i].equals(item))
					{
						m_spinner.setSelection(i);
					}
				}
			}
		});
	}
}
