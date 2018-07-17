#import <Foundation/Foundation.h>

#include "NavWidgetViewIncludes.h"
#include "NavWidgetView.h"
#include "ICompassView.h"
#include <MapKit/MapKit.h>

//Wrld Example App fudges the propagation of touch events so to prevent our touch events getting
//passed down to the Map we need to extend our common widget with a consumesTouch selector.
@interface WRLDNavWidgetBase(ExampleApp)
- (BOOL)consumesTouch:(UITouch *)touch;
@end

@implementation WRLDNavWidgetBase(ExampleApp)
- (BOOL)consumesTouch:(UITouch *)touch
{
    return [self pointInside:[touch locationInView:self] withEvent:nil];
}
@end

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            
            NavWidgetView::NavWidgetView(WRLDNavModel* navModel,
                                         Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& topPanelVisibleHeightChangedCallbacks,
                                         Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& bottomPanelVisibleHeightChangedCallbacks)
            : m_topPanelVisibleHeightChangedCallbacks(topPanelVisibleHeightChangedCallbacks)
            , m_bottomPanelVisibleHeightChangedCallbacks(bottomPanelVisibleHeightChangedCallbacks)
            , m_rerouteDialogOptionSelectedCallback(this, &NavWidgetView::OnRerouteDialogOptionSelected)
            , m_isVisible(false)
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
                registerObserver("topPanelVisibleHeight");
                registerObserver("bottomPanelVisibleHeight");
                setObject(m_pView);
                
                m_pRerouteDialog = [[NavRoutingRerouteDialog alloc] initWithFrame:[UIScreen mainScreen].bounds];
                [m_pRerouteDialog InsertRerouteDialogClosedCallback:&m_rerouteDialogOptionSelectedCallback];
                
                m_pCalculatingRoute = [[NavRoutingCalculatingRoute alloc] initWithFrame:[UIScreen mainScreen].bounds];
                
            }
            
            NavWidgetView::~NavWidgetView()
            {
                [m_pRerouteDialog RemoveRerouteDialogClosedCallback:&m_rerouteDialogOptionSelectedCallback];
                [m_pRerouteDialog release];
                
                [m_pCalculatingRoute release];
            }
            
            UIView* NavWidgetView::GetUIView()
            {
                return m_pView;
            }
            
            void NavWidgetView::Show()
            {
                m_isVisible = true;
                [m_pNavModel sendNavEvent:WRLDNavEventWidgetAnimateIn];
                [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleDefault;
            }
            
            void NavWidgetView::Hide()
            {
                m_isVisible = false;
                [m_pNavModel sendNavEvent:WRLDNavEventWidgetAnimateOut];
                m_topPanelVisibleHeightChangedCallbacks.ExecuteCallbacks(0);
                m_bottomPanelVisibleHeightChangedCallbacks.ExecuteCallbacks(0);
                [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;
            }
            
            void NavWidgetView::SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                NavWidgetView::SetLocation(locationModel, true);
                m_locationSetCallbacks.ExecuteCallbacks(true);
            }
            void NavWidgetView::SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                NavWidgetView::SetLocation(locationModel, false);
                m_locationSetCallbacks.ExecuteCallbacks(false);
            }
            
            void NavWidgetView::changeReceived(const std::string& keyPath)
            {
                if(keyPath == "topPanelVisibleHeight")
                {
                    INavWidgetView::THeight topViewHeight = GetTopViewHeight();
                    m_topPanelVisibleHeightChangedCallbacks.ExecuteCallbacks(topViewHeight);
                }
                if(keyPath == "bottomPanelVisibleHeight")
                {
                    INavWidgetView::THeight bottomViewHeight = GetBottomViewHeight();
                    m_bottomPanelVisibleHeightChangedCallbacks.ExecuteCallbacks(bottomViewHeight);
                }
            }
            
            void NavWidgetView::ClearStartLocation()
            {
                [m_pNavModel setStartLocation:NULL];
            }
            void NavWidgetView::ClearEndLocation()
            {
                [m_pNavModel setEndLocation:NULL];
            }
            
            void NavWidgetView::SetRoute(const SdkModel::NavRoutingRouteModel& routeModel, bool isNewRoute)
            {
                
                if(isNewRoute)
                {
                    [m_pNavModel setRoute:BuildWRLDNavRouteFromNavRoutingRouteModel(routeModel)];
                }
                else
                {
                    const auto& directions =routeModel.GetDirections();
                    
                    
                    for(int i = 0; i < directions.size(); i++ )
                    {
                        if([m_pNavModel setDirection:i direction:BuildWlrdNavDirectionFromFromNavRoutingDirectionModel(directions.at(i))])
                        {
                            continue;
                        }
                    }
                    [m_pNavModel sendNavEvent:WRLDNavEventRouteUpdated];
                }
                
                
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
                
                if(m_isVisible)
                {
                    if (navMode == WRLDNavModeActive)
                    {
                        [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;
                    }
                    else
                    {
                        [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleDefault;
                    }
                }
            }
            
            void NavWidgetView::ShowRerouteDialog(const std::string message)
            {
                [m_pRerouteDialog setMessage:[NSString stringWithCString: message.c_str() encoding:NSUTF8StringEncoding]];
                [m_pView.superview addSubview:m_pRerouteDialog];
            }
            
            void NavWidgetView::OnRerouteDialogOptionSelected(const bool& shouldReroute)
            {
                [m_pRerouteDialog removeFromSuperview];
                HandleRerouteDialogClosed(shouldReroute);
            }
            
            void NavWidgetView::SetCurrentDirection(int currentDirection)
            {
                [m_pNavModel setCurrentDirectionIndex:(NSInteger)currentDirection];
            }
            
            void NavWidgetView::UpdateCurrentDirection(const SdkModel::NavRoutingDirectionModel& directionModel)
            {
                [m_pNavModel setCurrentDirection:BuildWlrdNavDirectionFromFromNavRoutingDirectionModel(directionModel)];
            }

            void NavWidgetView::SetSelectedDirection(int directionIndex)
            {
                [m_pNavModel setSelectedDirectionIndex:(NSInteger)directionIndex];
            }
            
            void NavWidgetView::ShowCalculatingRouteSpinner()
            {
                [m_pView.superview addSubview:m_pCalculatingRoute];
                [m_pCalculatingRoute setSpinnerState:true];
            }
            
            void NavWidgetView::HideCalculatingRouteSpinner()
            {
                [m_pCalculatingRoute setSpinnerState:false];
                [m_pCalculatingRoute removeFromSuperview];
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
            
            void NavWidgetView::InsertRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback)
            {
                m_rerouteDialogClosedCallbacks.AddCallback(rerouteDialogClosedCallback);
            }
            
            void NavWidgetView::RemoveRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback)
            {
                m_rerouteDialogClosedCallbacks.RemoveCallback(rerouteDialogClosedCallback);
            }
            
            void NavWidgetView::HandleRerouteDialogClosed(bool shouldReroute)
            {
                m_rerouteDialogClosedCallbacks.ExecuteCallbacks(shouldReroute);
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
            
            INavWidgetView::THeight NavWidgetView::GetTopViewHeight()
            {
                return (INavWidgetView::THeight)m_pView.topPanelVisibleHeight;
            }
            
            INavWidgetView::THeight NavWidgetView::GetBottomViewHeight()
            {
                return (INavWidgetView::THeight)m_pView.bottomPanelVisibleHeight;
            }
            
            void NavWidgetView::SetStartPointFromResultIndex(int index)
            {
                m_navigationStartPointFromResultCallbacks.ExecuteCallbacks(index);
            }
            
            void NavWidgetView::SetEndPointFromResultIndex(int index)
            {
                m_navigationEndPointFromResultCallbacks.ExecuteCallbacks(index);
            }
            
            void NavWidgetView::SetSearchingForLocation(bool isSearching, bool forStartLocation)
            {
                m_navigationSearchForLocationChangedCallbacks.ExecuteCallbacks(isSearching, forStartLocation);
            }
            
            void NavWidgetView::InsertOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationStartPointFromResultCallbacks.AddCallback(callback);
            }
            
            void NavWidgetView::RemoveOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationStartPointFromResultCallbacks.AddCallback(callback);
            }
            
            void NavWidgetView::InsertOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationEndPointFromResultCallbacks.AddCallback(callback);
            }
            
            void NavWidgetView::RemoveOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationEndPointFromResultCallbacks.RemoveCallback(callback);
            }
            
            void NavWidgetView::InsertOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool>& callback)
            {
                m_navigationSearchForLocationChangedCallbacks.AddCallback(callback);
            }
            
            void NavWidgetView::RemoveOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool>& callback)
            {
                m_navigationSearchForLocationChangedCallbacks.RemoveCallback(callback);
            }
            
            void NavWidgetView::InsertLocationSetCallback(Eegeo::Helpers::ICallback1<const bool>& callback)
            {
                m_locationSetCallbacks.AddCallback(callback);
            }
            
            void NavWidgetView::RemoveLocationSetCallback(Eegeo::Helpers::ICallback1<const bool>& callback)
            {
                m_locationSetCallbacks.RemoveCallback(callback);
            }
        }
    }
}
