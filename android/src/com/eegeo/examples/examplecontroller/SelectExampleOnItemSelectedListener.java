package com.eegeo.examples.examplecontroller;

import android.view.View;
import android.widget.AdapterView;
import android.widget.Spinner;
import android.widget.AdapterView.OnItemSelectedListener;

import com.eegeo.INativeMessageRunner;

class SelectExampleOnItemSelectedListener implements OnItemSelectedListener
{
	private int m_spinnerCurrentSelection = -1;
	private final Spinner m_spinner;
	private final INativeMessageRunner m_nativeMessageRunner;
	private final long m_nativeCallerPointer;
	
	public SelectExampleOnItemSelectedListener(
			Spinner spinner,
			INativeMessageRunner nativeMessageRunner,
			long nativeCallerPointer)
	{
		m_spinner = spinner;
		m_nativeMessageRunner = nativeMessageRunner;
		m_nativeCallerPointer = nativeCallerPointer;
	}

	@Override
	public void onItemSelected(AdapterView<?> parentView, View selectedItemView,
	                           int position, long id)
	{
		if(m_spinnerCurrentSelection >= 0 && m_spinnerCurrentSelection != position)
		{
			final String selection = (String)m_spinner.getSelectedItem();

			m_nativeMessageRunner.runOnNativeThread(new Runnable()
			{
				public void run()
				{
					ExampleControllerJniMethods.SelectExample(m_nativeCallerPointer, selection);
				}
			});
		}
		m_spinnerCurrentSelection = position;
	}

	@Override
	public void onNothingSelected(AdapterView<?> parentView)
	{
	}
}