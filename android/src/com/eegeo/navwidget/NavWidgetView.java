// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.navwidget;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.location.Location;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewPropertyAnimator;
import android.view.animation.Animation;
import android.view.animation.LinearInterpolator;
import android.view.animation.RotateAnimation;
import android.view.inputmethod.InputMethodManager;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IBackButtonListener;
import com.eegeo.mobileexampleapp.R;
import com.eegeo.searchmenu.SearchWidgetResult;
import com.eegeo.searchproviders.MyTestSearchProvider;
import com.wrld.widgets.navigation.model.WrldNavEvent;
import com.wrld.widgets.navigation.model.WrldNavLocation;
import com.wrld.widgets.navigation.model.WrldNavMode;
import com.wrld.widgets.navigation.model.WrldNavModel;
import com.wrld.widgets.navigation.model.WrldNavModelObserver;
import com.wrld.widgets.navigation.model.WrldNavModelObserverListener;
import com.wrld.widgets.navigation.model.WrldNavRoute;
import com.wrld.widgets.navigation.model.WrldNavDirection;
import com.wrld.widgets.navigation.search.WrldNavSearchLocationView;
import com.wrld.widgets.navigation.widget.WrldNavWidget;
import com.wrld.widgets.navigation.widget.WrldNavWidgetViewObserver;
import com.wrld.widgets.navigation.widget.WrldNavWidgetViewVisibilityListener;
import com.wrld.widgets.navigation.widget.WrldNavWidgetViewSizeListener;
import com.wrld.widgets.search.WrldSearchWidget;
import com.wrld.widgets.search.model.SearchProvider;
import com.wrld.widgets.search.model.SearchProviderQueryResult;
import com.wrld.widgets.search.model.SearchQuery;
import com.wrld.widgets.search.model.SearchResult;
import com.wrld.widgets.search.model.SearchResultsListener;
import com.wrld.widgets.search.model.SuggestionProvider;

import java.util.List;

public class NavWidgetView implements IBackButtonListener, WrldNavModelObserverListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private AlertDialog m_calculatingSpinner = null;
    private View m_navSearchHintView = null;
    private boolean m_hasShownHint;

    private WrldNavWidget m_navWidget = null;
    private WrldNavModelObserver m_observer;

    private WrldNavWidgetViewObserver m_viewObserver;

    private WrldNavModel m_model;

    private boolean m_isNavWidgetVisible = false;
    private boolean m_isTopPanelVisible = false;
    private boolean m_isBottomPanelVisible = false;
    private float m_topPanelHeight = 0.0f;
    private float m_bottomPanelHeight = 0.0f;

    private WrldSearchWidget m_searchWidget;
    private WrldNavSearchLocationView m_searchLocationView;
    private boolean m_searchingForLocation;
    private boolean m_searchingForStartLocation;
    private ViewPropertyAnimator m_searchLocationViewAnimation;
    private SearchResultsListener m_autocompleteListener;
    private SearchResultsListener m_searchResultListener;
    private MyTestSearchProvider m_locationSearchProvider;

    private final int m_searchNavTopMargin;

    public NavWidgetView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);

        m_view = m_activity.getLayoutInflater().inflate(R.layout.nav_widget_layout, m_uiRoot, false);

        m_searchNavTopMargin = (int)activity.getResources().getDimension(R.dimen.nav_search_top_margin);

        m_uiRoot.addView(m_view);
        m_activity.addBackButtonPressedListener(this);

        m_model = new WrldNavModel();

        m_navWidget = (WrldNavWidget) m_view.findViewById(R.id.wrld_nav_widget_view);
        m_navWidget.getObserver().setNavModel(m_model);
        m_viewObserver = m_navWidget.getViewObserver();

        m_searchLocationView = m_uiRoot.findViewById(R.id.wrld_nav_search_widget_view);
        m_searchLocationView.getBackButton().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                endSearchForLocation();
            }
        });

        m_searchLocationView.addOnLayoutChangeListener(new View.OnLayoutChangeListener() {
            @Override
            public void onLayoutChange(View v, int left, int top, int right, int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom) {
                m_searchLocationView.removeOnLayoutChangeListener(this);
                setSearchLocationVisibility(false, false);
            }
        });

        m_navSearchHintView = m_uiRoot.findViewById(R.id.wrld_nav_search_hint_container);
        m_navSearchHintView.setVisibility(View.GONE);
        m_hasShownHint = false;

        if(m_searchWidget == null) {
            m_searchWidget = m_searchLocationView.getSearchWidget();
        }

        m_autocompleteListener = new SearchResultsListener() {

            @Override
            public void onSearchResultsReceived(SearchQuery searchQuery, List<SearchProviderQueryResult> list)
            {
                dismissSearchHint();
            }

            @Override
            public void onSearchResultsCleared() { }

            @Override
            public void onSearchResultsSelected(SearchResult searchResult) {
            }
        };
        m_searchResultListener = new SearchResultsListener() {
            @Override
            public void onSearchResultsReceived(SearchQuery searchQuery, List<SearchProviderQueryResult> list) { }

            @Override
            public void onSearchResultsCleared() { }

            @Override
            public void onSearchResultsSelected(SearchResult searchResult) {
                SearchWidgetResult widgetResult = (SearchWidgetResult) searchResult;

                if(m_searchingForStartLocation) {
                    NavWidgetViewJniMethods.SetNavigationStartPointFromSuggestion(
                            m_nativeCallerPointer,
                            widgetResult.getIndex());
                }
                else {
                    NavWidgetViewJniMethods.SetNavigationEndPointFromSuggestion(
                            m_nativeCallerPointer,
                            widgetResult.getIndex());
                }
                endSearchForLocation();
            }
        };

        m_observer = new WrldNavModelObserver();
        m_observer.observeProperty(WrldNavModel.WrldNavModelProperty.SelectedDirectionIndex);
        m_observer.observeProperty(WrldNavModel.WrldNavModelProperty.CurrentNavMode);
        m_observer.observeProperty(WrldNavModel.WrldNavModelProperty.StartLocation);
        m_observer.observeProperty(WrldNavModel.WrldNavModelProperty.EndLocation);
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

    public void addLocationSuggestionProvider(SuggestionProvider locationSuggestionProvider) {
        m_searchWidget.addSuggestionProvider(locationSuggestionProvider);
    }

    public void removeLocationSuggestionProvider(SuggestionProvider locationSuggestionProvider) {
        m_searchWidget.removeSuggestionProvider(locationSuggestionProvider);
    }

    public void setLocationSearchProvider(MyTestSearchProvider locationSearchProvider) {
        if(m_locationSearchProvider != null)
        {
            m_searchWidget.removeSearchProvider(m_locationSearchProvider);
            m_locationSearchProvider = null;
        }

        m_locationSearchProvider = locationSearchProvider;

        if(m_locationSearchProvider != null) {
            m_searchWidget.addSearchProvider(locationSearchProvider);
        }
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
        m_isNavWidgetVisible = true;
    }

    public void dismissNavWidgetView()
    {
        m_model.sendNavEvent(WrldNavEvent.WidgetAnimateOut);
        m_isNavWidgetVisible = false;
    }

    public void showRerouteDialog(String message)
    {
        final AlertDialog dialog = new AlertDialog.Builder(m_activity).create();
        LayoutInflater layoutInflater = m_activity.getLayoutInflater();
        View rerouteDialog = layoutInflater.inflate(R.layout.nav_widget_reroute_dialog_layout, null);

        rerouteDialog.findViewById(R.id.nav_reroute_dialog_btn_yes).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                NavWidgetViewJniMethods.RerouteDialogClosed(m_nativeCallerPointer, false);
                dialog.dismiss();
            }
        });

        rerouteDialog.findViewById(R.id.nav_reroute_dialog_btn_no).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                NavWidgetViewJniMethods.RerouteDialogClosed(m_nativeCallerPointer, true);
                dialog.dismiss();
            }
        });

        dialog.setOnCancelListener(new DialogInterface.OnCancelListener() {
            @Override
            public void onCancel(DialogInterface dialog) {
                NavWidgetViewJniMethods.RerouteDialogClosed(m_nativeCallerPointer, true);
            }
        });

        TextView messageText = rerouteDialog.findViewById(R.id.nav_reroute_dialog_msg);
        messageText.setText(message);

        dialog.setCancelable(false);
        dialog.setView(rerouteDialog);
        dialog.show();
    }


    public void showCalculatingRouteSpinner()
    {
        m_calculatingSpinner = new AlertDialog.Builder(m_activity).create();

        LayoutInflater layoutInflater = m_activity.getLayoutInflater();
        View calculatingSpinnerView = layoutInflater.inflate(R.layout.nav_widget_calculating_route_layout, null);

        ImageView calculatingSpinnerImageView = calculatingSpinnerView.findViewById(R.id.calculating_spinner_image_view);

        //Animate
        RotateAnimation rotate = new RotateAnimation(0,360, Animation.RELATIVE_TO_SELF, 0.5f, Animation.RELATIVE_TO_SELF, 0.5f);

        rotate.setDuration(2000);
        rotate.setInterpolator(new LinearInterpolator());
        rotate.setRepeatCount(Animation.INFINITE);

        calculatingSpinnerImageView.setAnimation(rotate);

        m_calculatingSpinner.setCancelable(false);
        m_calculatingSpinner.setView(calculatingSpinnerView);
        m_calculatingSpinner.show();

    }

    public void hideCalculatingRouteSpinner()
    {
        if(m_calculatingSpinner != null)
        {
            m_calculatingSpinner.dismiss();
            m_calculatingSpinner = null;
        }
    }
    
    public void destroy()
    {
        m_uiRoot.removeView(m_view);
        m_activity.removeBackButtonPressedListener(this);
    }

    @Override
    public boolean onBackButtonPressed()
    {
        if (m_isNavWidgetVisible)
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
            case StartLocation:
            case EndLocation:
                m_model.setRoute(null);
                if(m_searchingForLocation) {
                    endSearchForLocation();
                }
                break;
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
                {
                    boolean isStartLocation = true;
                    searchForLocation(isStartLocation);
                }
                break;
            case SelectEndLocationClicked:
                NavWidgetViewJniMethods.SelectEndLocationClicked(m_nativeCallerPointer);
                {
                    boolean isStartLocation = false;
                    searchForLocation(isStartLocation);
                }
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

    public void searchForLocation(boolean startLocation) {
        m_searchingForLocation = true;
        m_searchingForStartLocation = startLocation;
        setSearchLocationVisibility(true, true);
        m_model.sendNavEvent(WrldNavEvent.WidgetAnimateOut);
        m_searchWidget.getSuggestionResultsModel().addResultListener(m_autocompleteListener);
        m_searchWidget.getSearchResultsModel().addResultListener(m_searchResultListener);
        m_searchWidget.clearSearch();
        NavWidgetViewJniMethods.SetSearchingForLocation(m_nativeCallerPointer, true, m_searchingForStartLocation);

        if(!m_hasShownHint)
        {
            m_hasShownHint = true;
            showSearchHint();
        }

        m_locationSearchProvider.showNavButtons(false);

    }

    public void endSearchForLocation() {
        m_searchingForLocation = false;
        m_searchWidget.getSearchResultsModel().removeResultListener(m_searchResultListener);
        m_searchWidget.getSuggestionResultsModel().removeResultListener(m_autocompleteListener);
        setSearchLocationVisibility(false, true);
        m_model.sendNavEvent(WrldNavEvent.WidgetAnimateIn);
        NavWidgetViewJniMethods.SetSearchingForLocation(m_nativeCallerPointer, false, m_searchingForStartLocation);
        dismissSearchHint();

        m_locationSearchProvider.showNavButtons(true);
    }

    private void setSearchLocationVisibility(final boolean visible, boolean animate) {
        if(m_searchLocationViewAnimation != null) {
            m_searchLocationViewAnimation.cancel();
            m_searchLocationViewAnimation=null;
        }

        int panelHeight = m_searchLocationView.getHeight();
        float targetY = visible ? m_searchNavTopMargin : -panelHeight;
        if(animate) {
            m_searchLocationViewAnimation = m_searchLocationView.animate()
                    .y(targetY)
                    .withEndAction(new Runnable() {

                        @Override
                        public void run() {
                            if(visible) {
                                //      Try focus on the searchbox and show keyboard
                                View searchBoxView = m_searchWidget.getView().findViewById(R.id.searchbox_search_searchview);
                                if (searchBoxView != null) {
                                    searchBoxView.requestFocus();
                                    InputMethodManager imm = (InputMethodManager) m_activity.getSystemService(Context.INPUT_METHOD_SERVICE);
                                    imm.toggleSoftInput(InputMethodManager.SHOW_IMPLICIT, 0);
                                }
                            }
                            else
                            {
                                m_searchWidget.getView().clearFocus();
                            }
                        }
                    })
                    .setDuration(300);
        }
        else {
            m_searchLocationView.setY(targetY);
        }
    }

    private void showSearchHint() {
        m_navSearchHintView.setVisibility(View.VISIBLE);
        m_navSearchHintView.setAlpha(0.0f);
        m_navSearchHintView.animate()
                .alpha(1.0f)
                .setStartDelay(300)
                .setDuration(200)
                .withEndAction(new Runnable() {

                    @Override
                    public void run() {
                        if(m_searchingForLocation) {
                            m_navSearchHintView.animate()
                                    .alpha(0.0f)
                                    .setStartDelay(5000)
                                    .setDuration(200)
                                    .withEndAction(new Runnable() {

                                        @Override
                                        public void run() {
                                            m_navSearchHintView.setVisibility(View.GONE);
                                        }
                                    });
                        }
                    }
                });

    }

    private void dismissSearchHint() {
        if(m_navSearchHintView.getVisibility() != View.GONE) {
            m_navSearchHintView.setAnimation(null);
            m_navSearchHintView.animate()
                    .alpha(0.0f)
                    .setDuration(200)
                    .setStartDelay(0)
                    .withEndAction(new Runnable() {

                        @Override
                        public void run() {
                            m_navSearchHintView.setVisibility(View.GONE);
                        }
                    });
        }
    }
}
