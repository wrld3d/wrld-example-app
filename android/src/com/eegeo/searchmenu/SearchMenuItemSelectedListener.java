package com.eegeo.searchmenu;

import com.eegeo.INativeMessageRunner;
import com.eegeo.menu.MenuViewJniMethods;

import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class SearchMenuItemSelectedListener implements OnItemClickListener 
{
	private final INativeMessageRunner m_nativeMessageRunner;
	private final long m_nativeCallerPointer;
	
	public SearchMenuItemSelectedListener(
			INativeMessageRunner nativeMessageRunner,
			long nativeCallerPointer)
	{
		m_nativeMessageRunner = nativeMessageRunner;
		m_nativeCallerPointer = nativeCallerPointer;
	}

	@Override
	public void onItemClick (AdapterView<?> parent, View itemClicked, int position, long id)
	{
		final String selection = (String)parent.getAdapter().getItem(position);
		final int index = position;
        																																		
		m_nativeMessageRunner.runOnNativeThread(new Runnable()
		{
			public void run()
			{
				MenuViewJniMethods.SelectedItem(m_nativeCallerPointer, selection, index);
			}
		});
	}
}

