#import <Foundation/Foundation.h>

#include "NavWidgetViewIncludes.h"
#include "NavWidgetView.h"
#include "NavWidgetView.h"
#include "ICompassView.h"
#include <MapKit/MapKit.h>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            
            NavWidgetView::NavWidgetView(WRLDNavModel* navModel, Compass::View::ICompassView& compassView)
            {
                m_pNavModel = navModel;
                
                if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
                {
                    m_pView = [[WRLDNavWidgetTablet alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                    compassView.SetNavigationModeOffset(0);
                }
                else
                {
                    m_pView = [[WRLDNavWidgetPhone alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                    compassView.SetNavigationModeOffset(96);
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
                [m_pNavModel setRoute:BuildWRLDNavRouteFromNavRoutingRouteModel(routeModel)];
            }
            
            void NavWidgetView::ClearRoute()
            {
                [m_pNavModel setRoute:NULL];
            }
            
            void NavWidgetView::SetRemainingRouteDuration(double seconds)
            {
                [m_pNavModel setRemainingRouteDuration:seconds];
            }
            
            void NavWidgetView::SetNavMode(SdkModel::NavRoutingMode mode)
            {
                WRLDNavMode navMode;
                
                switch (mode)
                {
                    case SdkModel::Ready:
                    navMode = WRLDNavModeReady;
                    break;
                    
                    case SdkModel::Active:
                    navMode = WRLDNavModeActive;
                    break;
                    
                    default:
                    navMode = WRLDNavModeNotReady;
                    break;
                }
                
                [m_pNavModel setNavMode:navMode];
            }
            
            void NavWidgetView::SetCurrentDirection(int currentDirection)
            {
                [m_pNavModel setCurrentDirection:(NSInteger)currentDirection];
            }

            void NavWidgetView::SetSelectedDirection(int directionIndex)
            {
                [m_pNavModel setSelectedDirection:(NSInteger)directionIndex];
            }
            
            void NavWidgetView::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.AddCallback(callback);
            }
            
            void NavWidgetView::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.RemoveCallback(callback);
            }
            void NavWidgetView::HandleClosedCallback()
            {
                m_closedCallbacks.ExecuteCallbacks();
            }
            
            void NavWidgetView::InsertStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startLocationClickedCallbacks.AddCallback(callback);
            }
            
            void NavWidgetView::RemoveStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startLocationClickedCallbacks.RemoveCallback(callback);
            }
            void NavWidgetView::HandleStartLocationClickedCallback()
            {
                m_startLocationClickedCallbacks.ExecuteCallbacks();
            }
            
            void NavWidgetView::InsertEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_endLocationClickedCallback.AddCallback(callback);
            }
            void NavWidgetView::RemoveEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_endLocationClickedCallback.RemoveCallback(callback);
            }
            void NavWidgetView::HandleEndLocationClickedCallback()
            {
                m_endLocationClickedCallback.ExecuteCallbacks();
            }
            
            void NavWidgetView::InsertStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startLocationClearButtonClickedCallbacks.AddCallback(callback);
            }
            void NavWidgetView::RemoveStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startLocationClearButtonClickedCallbacks.RemoveCallback(callback);
            }
            void NavWidgetView::HandleStartLocationClearButtonClickedCallback()
            {
                m_startLocationClearButtonClickedCallbacks.ExecuteCallbacks();
            }
            
            void NavWidgetView::InsertEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_endLocationClearButtonClickedCallback.AddCallback(callback);
            }
            void NavWidgetView::RemoveEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_endLocationClearButtonClickedCallback.RemoveCallback(callback);
            }
            void NavWidgetView::HandleEndLocationClearButtonCallback()
            {
                m_endLocationClearButtonClickedCallback.ExecuteCallbacks();
            }
            
            void NavWidgetView::InsertStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startEndLocationsSwappedCallbacks.AddCallback(callback);
            }
            void NavWidgetView::RemoveStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startEndLocationsSwappedCallbacks.RemoveCallback(callback);
            }
            void NavWidgetView::HandleStartEndLocationsSwappedCallback()
            {
                m_startEndLocationsSwappedCallbacks.ExecuteCallbacks();
            }
            
            void NavWidgetView::InsertStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startEndRoutingButtonClickedCallbacks.AddCallback(callback);
            }
            void NavWidgetView::RemoveStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_startEndRoutingButtonClickedCallbacks.RemoveCallback(callback);
            }
            void NavWidgetView::HandleStartEndRoutingButtonClickedCallback()
            {
                m_startEndRoutingButtonClickedCallbacks.ExecuteCallbacks();
            }
            
            void NavWidgetView::InsertSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_selectedDirectionIndexChangedCallback.AddCallback(callback);
            }
            void NavWidgetView::RemoveSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_selectedDirectionIndexChangedCallback.RemoveCallback(callback);
            }
            void NavWidgetView::HandleSelectedDirectionIndexChangedCallback(int selectedDirection)
            {
                m_selectedDirectionIndexChangedCallback.ExecuteCallbacks(selectedDirection);
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
            
            WRLDNavRoute* NavWidgetView::BuildWRLDNavRouteFromNavRoutingRouteModel(const SdkModel::NavRoutingRouteModel& routeModel)
            {
                NSMutableArray<WRLDNavDirection *>* directionsArray = [[NSMutableArray<WRLDNavDirection *> alloc] init];
                
                for( auto& direction : routeModel.GetDirections())
                {
                    [directionsArray addObject:BuildWlrdNavDirectionFromFromNavRoutingDirectionModel(direction)];
                }
                
                return [[WRLDNavRoute alloc] initWithEstimatedRouteDuration:routeModel.GetDuration() directions:directionsArray];
            }
            
            WRLDNavDirection* NavWidgetView::BuildWlrdNavDirectionFromFromNavRoutingDirectionModel(const SdkModel::NavRoutingDirectionModel& directionModel )
            {
                NSMutableArray<NSValue*>* path = [[NSMutableArray alloc] init];

                //TODO Set up Paths Correctly without Casting Problems otherwise the device wont build when not debuging/Running on a machine.
                
                return [[WRLDNavDirection alloc] initWithName: BuildNSStringFromString(directionModel.GetName())
                                                         icon: BuildNSStringFromString(directionModel.GetIcon())
                                                  instruction: BuildNSStringFromString(directionModel.GetInstruction())
                                              thenInstruction: BuildNSStringFromString(directionModel.GetNextInstruction())
                                                         path: path
                                                     indoorID: BuildNSStringFromString(directionModel.GetIndoorMapId().Value())
                                                      floorID: directionModel.GetIndoorMapFloorId()
                                                 isMultiFloor: directionModel.GetIsMultiFloor()];
            }
            
            NSString* NavWidgetView::BuildNSStringFromString(const std::string& string)
            {
                return [NSString stringWithCString:string.c_str()
                                          encoding:[NSString defaultCStringEncoding]];
            }
        }
    }
}
