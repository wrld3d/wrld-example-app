// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import com.eegeo.mobileexampleapp.MainActivity;

import android.view.View;

public class SearchMenuCloseButtonClickedHandler implements View.OnClickListener
{
    private MainActivity m_activity;
    private long m_nativeCallerPointer;

    SearchMenuCloseButtonClickedHandler(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;
    }

    @Override
    public void onClick(View view)
    {
        SearchMenuViewJniMethods.HandleClosed(m_nativeCallerPointer);
    }
}
