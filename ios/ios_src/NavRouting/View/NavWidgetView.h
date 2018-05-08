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
//                UIViewController* m_pController;
//                
//                UIColor* m_pColour;
//                
//                float m_width;
//                float m_height;
//                
//                float m_screenWidth;
//                float m_screenHeight;
//                float m_pixelScale;
//                
//                float m_yPosActive;
//                float m_yPosInactive;
                
                WRLDNavWidgetBase* m_pView;
                
            public:
                NavWidgetView();
                
                ~NavWidgetView() { };
                
                UIView* GetUIView();
                
                BOOL consumesTouch(UITouch*);
                
                // Public WRLDNavWidgetBase View
                
                void Show() ;
                
                void Hide() ;
                
                void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel);
                
                void ClearStartLocation() ;
                
                void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel);
                
                void ClearEndLocation() ;
                
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

