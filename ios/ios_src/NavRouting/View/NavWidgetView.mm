#import <Foundation/Foundation.h>

#include "NavWidgetViewIncludes.h"
#include "NavWidgetView.h"
#include "NavWidgetView.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            
            NavWidgetView::NavWidgetView()
            {
                m_pView = [[WRLDNavWidgetBase alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                
                [m_pView setHidden:true];
                
            }
            
            UIView* NavWidgetView::GetUIView()
            {
                return m_pView;
            }
            
            BOOL NavWidgetView::consumesTouch(UITouch*)
            {
                return NO;
            }
            
            void NavWidgetView::Show()
            {
                
            }
            
            void NavWidgetView::Hide()
            {
            }
            
            void NavWidgetView::SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                
            }
            
            void NavWidgetView::ClearStartLocation()
            {
                
            }
            
            void NavWidgetView::SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                
            }
            
            void NavWidgetView::ClearEndLocation()
            {
                
            }
            
            void NavWidgetView::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            void NavWidgetView::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            
            void NavWidgetView::InsertStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            void NavWidgetView::RemoveStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            
            void NavWidgetView::InsertEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            void NavWidgetView::RemoveEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            
            void NavWidgetView::InsertStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            void NavWidgetView::RemoveStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            
            void NavWidgetView::InsertEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            void NavWidgetView::RemoveEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            
            void NavWidgetView::InsertStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
            void NavWidgetView::RemoveStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                
            }
        }
    }
}
