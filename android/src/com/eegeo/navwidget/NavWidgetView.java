// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.navwidget;

import android.location.Location;
import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IBackButtonListener;
import com.eegeo.mobileexampleapp.R;
import com.wrld.widgets.navigation.model.WrldNavEvent;
import com.wrld.widgets.navigation.model.WrldNavLocation;
import com.wrld.widgets.navigation.model.WrldNavMode;
import com.wrld.widgets.navigation.model.WrldNavModel;
import com.wrld.widgets.navigation.model.WrldNavModelObserver;
import com.wrld.widgets.navigation.model.WrldNavModelObserverListener;
import com.wrld.widgets.navigation.model.WrldNavRoute;
import com.wrld.widgets.navigation.model.WrldNavDirection;
import com.wrld.widgets.navigation.widget.WrldNavWidget;
import com.wrld.widgets.navigation.widget.WrldNavWidgetViewObserver;
import com.wrld.widgets.navigation.widget.WrldNavWidgetViewVisibilityListener;
import com.wrld.widgets.navigation.widget.WrldNavWidgetViewSizeListener;

import java.util.List;

public class NavWidgetView implements IBackButtonListener, WrldNavModelObserverListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private WrldNavWidget m_navWidget = null;
    private WrldNavModelObserver m_observer;

    private WrldNavWidgetViewObserver m_viewObserver;

    private WrldNavModel m_model;

    private boolean m_isTopPanelVisible = false;
    private boolean m_isBottomPanelVisible = false;
    private float m_topPanelHeight = 0.0f;
    private float m_bottomPanelHeight = 0.0f;

    public NavWidgetView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.nav_widget_layout, m_uiRoot, false);

        m_uiRoot.addView(m_view);
        m_activity.addBackButtonPressedListener(this);

        m_model = new WrldNavModel();

        m_navWidget = (WrldNavWidget) m_view.findViewById(R.id.wrld_nav_widget_view);
        m_navWidget.getObserver().setNavModel(m_model);
        m_viewObserver = m_navWidget.getViewObserver();

        m_observer = new WrldNavModelObserver();
        m_observer.observeProperty(WrldNavModel.WrldNavModelProperty.SelectedDirectionIndex);
        m_observer.observeProperty(WrldNavModel.WrldNavModelProperty.CurrentNavMode);
        m_observer.setListener(this);
        m_observer.setNavModel(m_model);

        m_viewObserver.addSizeChangedListener(new WrldNavWidgetViewSizeListener(){
            public void onTopPanelHeightChanged(float height)
            {
                m_topPanelHeight = height;
                NavWidgetViewJniMethods.SetTopViewHeight(m_nativeCallerPointer, calculateVisibleTopHeight());
            }
            public void onBottomPanelHeightChanged(float height)
            {
                m_bottomPanelHeight = height;
                NavWidgetViewJniMethods.SetBottomViewHeight(m_nativeCallerPointer, calculateVisibleBottomHeight());
            }
            public void onLeftPanelWidthChanged(float width)
            {
            }
        });

        m_viewObserver.addVisibilityListener(new WrldNavWidgetViewVisibilityListener(){
            public void onTopPanelVisible(boolean isVisible) {
                m_isTopPanelVisible = isVisible;
                NavWidgetViewJniMethods.SetTopViewHeight(m_nativeCallerPointer, calculateVisibleTopHeight());
            }
            public void onBottomPanelVisible(boolean isVisible) {
                m_isBottomPanelVisible = isVisible;
                NavWidgetViewJniMethods.SetBottomViewHeight(m_nativeCallerPointer, calculateVisibleBottomHeight());
            }
            public void onLeftPanelVisible(boolean isVisible){}
        });

        NavWidgetViewJniMethods.SetTopViewHeight(m_nativeCallerPointer, (int) m_viewObserver.getTopPanelHeight());
        NavWidgetViewJniMethods.SetBottomViewHeight(m_nativeCallerPointer,  (int) m_viewObserver.getBottomPanelHeight());
    }

    private int calculateVisibleTopHeight()
    {
        if(m_isTopPanelVisible){
            return (int) m_topPanelHeight;
        }
        return 0;
    }

    private int calculateVisibleBottomHeight()
    {
        if(m_isBottomPanelVisible){
            return (int) m_bottomPanelHeight;
        }
        return 0;
    }

    private void handleCloseClicked()
    {
        NavWidgetViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }

    private WrldNavLocation createNavLocation(String name, double lat, double lon, boolean isIndoors, String indoorMapId, int floorMapFloorId)
    {
        Location loc = new Location("Wrld");
        loc.setLatitude(lat);
        loc.setLongitude(lon);

        WrldNavLocation location;

        if (isIndoors)
        {
            location = new WrldNavLocation(name, loc, indoorMapId, floorMapFloorId);
        }
        else
        {
            location = new WrldNavLocation(name, loc);
        }

        return location;
    }

    public void setStartLocation(String name, double lat, double lon, boolean isIndoors, String indoorMapId, int floorMapFloorId)
    {
        m_model.setStartLocation(createNavLocation(name, lat, lon, isIndoors, indoorMapId, floorMapFloorId));
    }

    public void clearStartLocation()
    {
        m_model.setStartLocation(null);
    }

    public void setEndLocation(String name, double lat, double lon, boolean isIndoors, String indoorMapId, int floorMapFloorId)
    {
        m_model.setEndLocation(createNavLocation(name, lat, lon, isIndoors, indoorMapId, floorMapFloorId));
    }

    public void clearEndLocation()
    {
        m_model.setEndLocation(null);
    }

    public void setRoute(WrldNavRoute route, boolean isNewRoute)
    {
        if (isNewRoute)
        {
            m_model.setRoute(route);
        }
        else
        {
            List<WrldNavDirection> directions = route.directions;

            for (int i = 0; i < directions.size(); i++)
            {
                m_model.setDirection(i, directions.get(i));
            }

            m_model.sendNavEvent(WrldNavEvent.RouteUpdated);
        }
    }

    public void clearRoute()
    {
        m_model.setRoute(null);
    }

    public void setCurrentDirectionIndex(int directionIndex)
    {
        m_model.setCurrentDirectionIndex(directionIndex);
    }

    public void setCurrentDirection(WrldNavDirection currentDirection)
    {
        m_model.setCurrentDirection(currentDirection);
    }

    public void setSelectedDirectionIndex(int directionIndex)
    {
        m_model.setSelectedDirectionIndex(directionIndex);
    }

    public void setRemainingRouteDurationSeconds(double remainingRouteDurationSeconds)
    {
        m_model.setRemainingRouteDurationSeconds(remainingRouteDurationSeconds);
    }

    public void setCurrentNavMode(WrldNavMode navMode)
    {
        m_model.setCurrentNavMode(navMode);
    }

    public void showNavWidgetView()
    {
        m_model.sendNavEvent(WrldNavEvent.WidgetAnimateIn);
    }

    public void dismissNavWidgetView()
    {
        m_model.sendNavEvent(WrldNavEvent.WidgetAnimateOut);
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
        switch (wrldNavModelProperty)
        {
            case SelectedDirectionIndex:
                NavWidgetViewJniMethods.SelectedDirectionIndexChanged(m_nativeCallerPointer, m_model.getSelectedDirectionIndex());
                break;
        }
    }

    @Override
    public void onEventReceived(WrldNavEvent wrldNavEvent)
    {
        switch (wrldNavEvent)
        {
            case CloseSetupJourneyClicked:
                handleCloseClicked();
                break;
            case SelectStartLocationClicked:
                NavWidgetViewJniMethods.SelectStartLocationClicked(m_nativeCallerPointer);
                break;
            case SelectEndLocationClicked:
                NavWidgetViewJniMethods.SelectEndLocationClicked(m_nativeCallerPointer);
                break;
            case StartLocationClearButtonClicked:
                NavWidgetViewJniMethods.StartLocationClearButtonClicked(m_nativeCallerPointer);
                break;
            case EndLocationClearButtonClicked:
                NavWidgetViewJniMethods.EndLocationClearButtonClicked(m_nativeCallerPointer);
                break;
            case StartEndLocationsSwapped:
                NavWidgetViewJniMethods.StartEndLocationsSwapped(m_nativeCallerPointer);
                break;
            case StartEndButtonClicked:
                NavWidgetViewJniMethods.StartEndButtonClicked(m_nativeCallerPointer);
                break;
        }
    }
}
