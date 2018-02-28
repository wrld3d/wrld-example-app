// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.ProjectSwallowApp.R;
import android.view.View;
import android.widget.RelativeLayout;

import com.wrld.widgets.searchbox.WrldSearchWidget;
import com.eegeo.searchproviders.MyTestSearchProvider;

public class SearchWidgetView
{
    protected MainActivity m_activity;
    protected MyTestSearchProvider m_searchProvider;
    protected long m_nativeCallerPointer;
    protected long m_providerNativeCallerPointer;
    protected View m_view;

    protected WrldSearchWidget m_searchWidget;

    public SearchWidgetView(MainActivity activity, MyTestSearchProvider searchProvider,
                            long nativeCallerPointer, long providerNativeCallerPointer)
    {
        m_activity = activity;
        m_searchProvider = searchProvider;
        m_nativeCallerPointer = nativeCallerPointer;
        m_providerNativeCallerPointer = providerNativeCallerPointer;

        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_widget_view_layout, uiRoot, false);
        uiRoot.addView(m_view);

        m_searchWidget = (WrldSearchWidget) m_activity.getFragmentManager().findFragmentById(R.id.search_widget);
        m_searchWidget.addSearchProvider(m_searchProvider);
    }

    public void onSearchCompleted(String[] searchResults)
    {
        m_searchProvider.onSearchCompleted(searchResults);
    }
}
