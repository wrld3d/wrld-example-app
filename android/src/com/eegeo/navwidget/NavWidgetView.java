// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.navwidget;

import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IBackButtonListener;
import com.eegeo.mobileexampleapp.R;
import com.wrld.widgets.navigation.model.WrldNavEvent;
import com.wrld.widgets.navigation.model.WrldNavMode;
import com.wrld.widgets.navigation.model.WrldNavModel;
import com.wrld.widgets.navigation.model.WrldNavModelObserverListener;
import com.wrld.widgets.navigation.widget.WrldNavWidget;

public class NavWidgetView implements IBackButtonListener, WrldNavModelObserverListener, View.OnClickListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private WrldNavWidget m_navWidget = null;

    //Test model
    private WrldNavModel m_model;

    public NavWidgetView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.nav_widget_layout, m_uiRoot, false);

        m_uiRoot.addView(m_view);
        m_activity.addBackButtonPressedListener(this);

        Button btn = (Button) m_view.findViewById(R.id.test_button);
        btn.setOnClickListener(this);

//        m_model = new WrldNavModel();
//
//        m_navWidget = (WrldNavWidget) m_view.findViewById(R.id.wrld_nav_widget_view);
//        m_navWidget.getObserver().setNavModel(m_model);
    }

    private void handleCloseClicked()
    {
        m_view.setEnabled(false);

        NavWidgetViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }

    public void dismissNavWidgetView()
    {
        //TODO animate out
        m_view.setVisibility(View.GONE);
    }
    public void destroy()
    {
        m_uiRoot.removeView(m_view);
        m_activity.removeBackButtonPressedListener(this);
    }

    @Override
    public boolean onBackButtonPressed()
    {
        if (m_view.getVisibility() == View.VISIBLE)
        {
            WrldNavMode currentNavMode = m_model.getCurrentNavMode();
            if (currentNavMode == WrldNavMode.NotReady || currentNavMode == WrldNavMode.Ready)
            {
                handleCloseClicked();
            }
            else
            {
                m_model.sendNavEvent(WrldNavEvent.StartEndButtonClicked);
            }

            return true;
        }
        return false;
    }

    @Override
    public void onModelSet()
    {

    }

    @Override
    public void onPropertyChanged(WrldNavModel.WrldNavModelProperty wrldNavModelProperty)
    {

    }

    @Override
    public void onEventReceived(WrldNavEvent wrldNavEvent)
    {
        if (wrldNavEvent == WrldNavEvent.CloseSetupJourneyClicked)
        {
            handleCloseClicked();
        }
    }

    @Override
    public void onClick(View view) {
        Log.i("test tag", "click");
        handleCloseClicked();
    }
}
