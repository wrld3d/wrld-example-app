// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import android.view.View;

public class SearchMenuCloseButtonClickedHandler implements View.OnClickListener
{
    private long m_nativeCallerPointer;
    private final SearchMenuView m_searchMenuView;

    SearchMenuCloseButtonClickedHandler(long nativeCallerPointer,
            							final SearchMenuView menuView)
    {
        m_nativeCallerPointer = nativeCallerPointer;
        m_searchMenuView = menuView;
    }

    @Override
    public void onClick(View view)
    {
    	m_searchMenuView.setEditText("", false);
        SearchMenuViewJniMethods.OnSearchCleared(m_nativeCallerPointer);
    }
}
