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
            
            NavWidgetView::NavWidgetView(WRLDNavModel* navModel)
            {
                m_pNavModel = navModel;
                
                if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
                {
                    m_pView = [[WRLDNavWidgetTablet alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                }
                else
                {
                    m_pView = [[WRLDNavWidgetPhone alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                }
                
                [m_pView setViewVisibilityWithAnimate:false hideViews:true];
                [m_pView setAutoresizingMask:UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight];
                
                [[m_pView observer] setNavModel:navModel];
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
                [m_pNavModel sendNavEvent:WRLDNavEventWidgetAnimateIn];
            }
            
            void NavWidgetView::Hide()
            {
                [m_pNavModel sendNavEvent:WRLDNavEventWidgetAnimateOut];
            }
            
            void NavWidgetView::SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                NavWidgetView::SetLocation(locationModel, true);
            }
            void NavWidgetView::SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                NavWidgetView::SetLocation(locationModel, false);
            }
            
            void NavWidgetView::ClearStartLocation()
            {
                [m_pNavModel setStartLocation:NULL];
            }
            void NavWidgetView::ClearEndLocation()
            {
                [m_pNavModel setEndLocation:NULL];
            }
            
            void NavWidgetView::SetRoute(const SdkModel::NavRoutingRouteModel& routeModel)
            {
                
            }
            
            void NavWidgetView::ClearRoute()
            {
                
            }
            
            void NavWidgetView::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.AddCallback(callback);
            }
            
            void NavWidgetView::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.RemoveCallback(callback);
            }
            
            void NavWidgetView::InsertStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startLocationClickedCallbacks.AddCallback(callback);
            }
            
            void NavWidgetView::RemoveStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startLocationClickedCallbacks.RemoveCallback(callback);
            }
            
            void NavWidgetView::InsertEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_endLocationClickedCallback.AddCallback(callback);
            }
            void NavWidgetView::RemoveEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_endLocationClickedCallback.RemoveCallback(callback);
            }
            
            void NavWidgetView::InsertStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startLocationClearButtonClickedCallbacks.AddCallback(callback);
            }
            void NavWidgetView::RemoveStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startLocationClearButtonClickedCallbacks.RemoveCallback(callback);
            }
            
            void NavWidgetView::InsertEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_endLocationClearButtonClickedCallback.AddCallback(callback);
            }
            void NavWidgetView::RemoveEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_endLocationClearButtonClickedCallback.RemoveCallback(callback);
            }
            
            void NavWidgetView::InsertStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startEndLocationsSwappedCallbacks.AddCallback(callback);
            }
            void NavWidgetView::RemoveStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startEndLocationsSwappedCallbacks.RemoveCallback(callback);
            }
            
            void NavWidgetView::SetLocation(const SdkModel::NavRoutingLocationModel& locationModel, bool isStartLocation)
            {
                Eegeo::Space::LatLong latLong = locationModel.GetLatLon();
                
                WRLDNavLocation* location = [[WRLDNavLocation alloc] initWithName:[NSString stringWithCString:locationModel.GetName().c_str()
                                                                                                     encoding:[NSString defaultCStringEncoding]]
                                                                           latLon:CLLocationCoordinate2DMake(latLong.GetLatitudeInDegrees(), latLong.GetLongitudeInDegrees())
                                                                         indoorID:[NSString stringWithCString:locationModel.GetIndoorMapId().Value().c_str()
                                                                                                     encoding:[NSString defaultCStringEncoding]]
                                                                          floorID:locationModel.GetIndoorMapFloorId()];
                
                if(isStartLocation)
                {
                    [m_pNavModel setStartLocation:location];
                }
                else
                {
                    [m_pNavModel setEndLocation:location];
                }
            }
        }
    }
}
