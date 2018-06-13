#pragma once

#include <string>
#import <UIKit/UIKit.h>
#include "NavWidgetViewIncludes.h"
#include "WrldNav/WrldNav.h"
#include "WrldNavWidget/WrldNavWidget.h"
#include "IAppModeModel.h"
#include "INavWidgetView.h"
#include "INavWidgetViewModel.h"
#include "ICompassView.h"


namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            
            class NavWidgetView : public WRLDNSObjectObserverCpp, public INavWidgetView
            {
                
            private:
                
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClickedCallback;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClearButtonClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClearButtonClickedCallback;
                Eegeo::Helpers::CallbackCollection0 m_startEndLocationsSwappedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startEndRoutingButtonClickedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const int> m_selectedDirectionIndexChangedCallback;
                Eegeo::Helpers::CallbackCollection1<const bool> m_rerouteDialogClosedCallbacks;
                Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& m_topPanelVisibleHeightChangedCallbacks;
                Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& m_bottomPanelVisibleHeightChangedCallbacks;
                
                WRLDNavWidgetBase* m_pView;
                WRLDNavModel* m_pNavModel;                
                
                void SetLocation(const SdkModel::NavRoutingLocationModel& locationModel, bool isStartLocation);
                
                WRLDNavRoute* BuildWRLDNavRouteFromNavRoutingRouteModel(const SdkModel::NavRoutingRouteModel& routeModel);
                WRLDNavDirection* BuildWlrdNavDirectionFromFromNavRoutingDirectionModel(const SdkModel::NavRoutingDirectionModel& directionModel );
                NSString* BuildNSStringFromString(const std::string& string);
                
            public:
                NavWidgetView(WRLDNavModel* m_pNavModel,
                              Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& topPanelVisibleHeightChangedCallbacks,
                              Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& bottomPanelVisibleHeightChangedCallbacks);
                
                ~NavWidgetView() { };
                
                UIView* GetUIView();
                
                BOOL consumesTouch(UITouch*);
                
                void changeReceived(const std::string& keyPath);
                
                void Show() ;
                
                void Hide() ;
                
                void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel);
                void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel);
                
                void ClearStartLocation() ;
                void ClearEndLocation() ;
                
                void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel,  bool isNewRoute);
                
                void ClearRoute();
                
                void SetCurrentDirection(int directionIndex);
                void UpdateCurrentDirection(const SdkModel::NavRoutingDirectionModel& directionModel);
                void SetSelectedDirection(int directionIndex);

                void SetRemainingRouteDuration(double seconds);
                
                void SetNavMode(SdkModel::NavRoutingMode mode);
                
                void ShowRerouteDialog(const std::string message);
                
                void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback);
                void HandleClosedCallback();
                
                void InsertStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void HandleStartLocationClickedCallback();
                
                void InsertEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void HandleEndLocationClickedCallback();
                
                void InsertStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void HandleStartLocationClearButtonClickedCallback();
                
                void InsertEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) ;
                void HandleEndLocationClearButtonCallback();
                
                void InsertStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void HandleStartEndLocationsSwappedCallback();
                
                void InsertStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback);
                void HandleStartEndRoutingButtonClickedCallback();
                
                void InsertSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback);
                void RemoveSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback);
                void HandleSelectedDirectionIndexChangedCallback(int selectedDirection);
                
                void InsertRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback);
                void RemoveRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback);
                void HandleRerouteDialogClosed(bool shouldReroute);
                
                THeight GetTopViewHeight();
                THeight GetBottomViewHeight();
            };
        }
    }
}
