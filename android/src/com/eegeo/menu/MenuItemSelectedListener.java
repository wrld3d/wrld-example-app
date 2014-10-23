package com.eegeo.menu;

import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

import com.eegeo.INativeMessageRunner;

public class MenuItemSelectedListener implements OnItemClickListener
{
	private final INativeMessageRunner m_nativeMessageRunner;
	private final long m_nativeCallerPointer;
	private MenuListAdapter m_adapter;
	
	public MenuItemSelectedListener(
			MenuListAdapter adapter,
			INativeMessageRunner nativeMessageRunner,
			long nativeCallerPointer)
	{
		m_adapter = adapter;
		m_nativeMessageRunner = nativeMessageRunner;
		m_nativeCallerPointer = nativeCallerPointer;
	}

	@Override
	public void onItemClick (AdapterView<?> parent, View itemClicked, int position, long id)
	{
		if(m_adapter.isAnimating())
		{
			return;
		}
		
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





