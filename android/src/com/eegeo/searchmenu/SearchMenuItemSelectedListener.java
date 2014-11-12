package com.eegeo.searchmenu;

import com.eegeo.menu.MenuViewJniMethods;

import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class SearchMenuItemSelectedListener implements OnItemClickListener
{
	private final long m_nativeCallerPointer;

	public SearchMenuItemSelectedListener(
	    long nativeCallerPointer)
	{
		m_nativeCallerPointer = nativeCallerPointer;
	}

	@Override
	public void onItemClick (AdapterView<?> parent, View itemClicked, int position, long id)
	{
		final String selection = (String)parent.getAdapter().getItem(position);
		final int index = position;

		MenuViewJniMethods.SelectedItem(m_nativeCallerPointer, selection, index);
	}
}

