// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.menu;

import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class MenuItemSelectedListener implements OnItemClickListener
{
    private final long m_nativeCallerPointer;
    private MenuListAdapter m_adapter;
    private final MenuView m_menuView;

    public MenuItemSelectedListener(
        MenuListAdapter adapter,
        MenuView menuView,
        long nativeCallerPointer)
    {
        m_adapter = adapter;
        m_menuView = menuView;
        m_nativeCallerPointer = nativeCallerPointer;
    }

    @Override
    public void onItemClick (AdapterView<?> parent, View itemClicked, int position, long id)
    {
        if(m_adapter.isAnimating() || m_menuView.isAnimating() || m_menuView.isDragging())
        {
            return;
        }

        final int sectionIndex = m_adapter.getSectionIndex(position);
        final int childIndex = m_adapter.getItemIndex(position);

        MenuViewJniMethods.SelectedItem(m_nativeCallerPointer, sectionIndex, childIndex);
    }
}





