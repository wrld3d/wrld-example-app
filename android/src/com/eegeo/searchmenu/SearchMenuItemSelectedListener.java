// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import com.eegeo.menu.MenuViewJniMethods;

import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class SearchMenuItemSelectedListener implements OnItemClickListener
{

    private final long m_nativeCallerPointer;
    private final SearchMenuView m_searchMenuView;

    public SearchMenuItemSelectedListener(
        long nativeCallerPointer,
        final SearchMenuView menuView)
    {
        m_nativeCallerPointer = nativeCallerPointer;
        m_searchMenuView = menuView;
    }

    @Override
    public void onItemClick (AdapterView<?> parent, View itemClicked, int position, long id)
    {
        if(m_searchMenuView.isAnimating() || m_searchMenuView.isDragging())
        {
            return;
        }

        final int index = position;

        MenuViewJniMethods.SelectedItem(m_nativeCallerPointer, 0, index);
    }
}

