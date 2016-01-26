// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import android.view.View;

public class SearchMenuCloseButtonClickedHandler implements View.OnClickListener
{
    private long m_nativeCallerPointer;

    SearchMenuCloseButtonClickedHandler(long nativeCallerPointer)
    {
        m_nativeCallerPointer = nativeCallerPointer;
    }

    @Override
    public void onClick(View view)
    {
        SearchMenuViewJniMethods.OnSearchCleared(m_nativeCallerPointer);
    }
}
