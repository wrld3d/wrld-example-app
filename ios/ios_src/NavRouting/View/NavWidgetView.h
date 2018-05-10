#pragma once

#include <string>
#import <UIKit/UIKit.h>
#include "NavWidgetViewIncludes.h"
#include "WrldNavWidget/WrldNavWidget.h"
#include "IAppModeModel.h"
#include "INavWidgetView.h"
#include "INavWidgetViewModel.h"


namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            
            class NavWidgetView : public INavWidgetView
            {
                
            private:
                
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClickedCallback;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClearButtonClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClearButtonClickedCallback;
                Eegeo::Helpers::CallbackCollection0 m_startEndLocationsSwappedCallbacks;
                
                WRLDNavWidgetBase* m_pView;
                WRLDNavModel* m_pNavModel;
                
                void SetLocation(const SdkModel::NavRoutingLocationModel& locationModel, bool isStartLocation);
                               
                
            public:
                NavWidgetView(WRLDNavModel* m_pNavModel);
                
                ~NavWidgetView() { };
                
                UIView* GetUIView();
                
                
                
                BOOL consumesTouch(UITouch*);
                
                void Show() ;
                
                void Hide() ;
                
                void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel);
                void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel);
                
                void ClearStartLocation() ;
                void ClearEndLocation() ;
                
                void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel);
                
                void ClearRoute();
                
                void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                
                void InsertEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                
                void InsertStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) ;
                
                void InsertEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) ;
                
                void InsertStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) ;
                void RemoveStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) ;
                
            };
        }
    }
}
