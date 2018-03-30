// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavUIViewModule.h"

#include "WrldNav/WrldNav.h"
#include "WrldNavWidget/WrldNavWidget.h"

#include "SearchResultPoiViewInterop.h"

#include "iOSLocationService.h"

#include "IOpenableControlViewModel.h"

#include "NavUIViewRouteUpdateHandler.h"

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
    namespace NavUI
    {
        namespace View
        {
            struct NavUIViewModule::Private : public WRLDNavModelObserverCpp
            {
                WRLDNavModel* model{nullptr};
                WRLDNavWidgetBase* view{nullptr};
                
                NavUIViewRouteUpdateHandler* m_pNavUIViewRouteUpdateHandler;
                
                ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* searchResultsPoiViewInterop;
                Eegeo::iOS::iOSLocationService* iOSLocationService;
                
                Eegeo::Helpers::TCallback1<Private, Search::SdkModel::SearchResultModel> directionsClickedCallbackObj;
                
                ExampleApp::OpenableControl::View::IOpenableControlViewModel& openable;
                
                Private(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* searchResultsPoiViewInterop_,
                        Eegeo::iOS::iOSLocationService* iOSLocationService_,
                        ExampleApp::OpenableControl::View::IOpenableControlViewModel& openable_):
                    searchResultsPoiViewInterop(searchResultsPoiViewInterop_),
                    iOSLocationService(iOSLocationService_),
                    directionsClickedCallbackObj(this, &Private::directionsClickedCallback),
                    openable(openable_)
                {
                    searchResultsPoiViewInterop->InsertDirectionsCallback(directionsClickedCallbackObj);
                    
                    registerObserver("startLocation");
                    registerObserver("endLocation");
                    registerObserver("routeDirections");
                }
                
                ~Private()
                {
                    searchResultsPoiViewInterop->RemoveDirectionsCallback(directionsClickedCallbackObj);
                    Eegeo_DELETE m_pNavUIViewRouteUpdateHandler;
                    
                    [view release];
                    [model release];
                }
                
                //Called when the 'Directions' button on the POI card is clicked
                void directionsClickedCallback(Search::SdkModel::SearchResultModel& searchResultModel)
                {
                    WRLDNavLocation* location;
                    const Eegeo::Space::LatLong& ll =  searchResultModel.GetLocation();
                    if(searchResultModel.IsInterior())
                    {
                        const Eegeo::Resources::Interiors::InteriorId& interior = searchResultModel.GetBuildingId();
                        location = [[WRLDNavLocation alloc] initWithName:[NSString stringWithCString:searchResultModel.GetTitle().c_str()
                                                                                            encoding:[NSString defaultCStringEncoding]]
                                                                  latLon:CLLocationCoordinate2DMake(ll.GetLatitudeInDegrees(), ll.GetLongitudeInDegrees())
                                                                indoorID:[NSString stringWithCString:interior.Value().c_str()
                                                                                            encoding:[NSString defaultCStringEncoding]]
                                                                 floorID:searchResultModel.GetFloor()];
                    }
                    else
                    {
                        location = [[WRLDNavLocation alloc] initWithName:[NSString stringWithCString:searchResultModel.GetTitle().c_str()
                                                                                            encoding:[NSString defaultCStringEncoding]]
                                                                  latLon:CLLocationCoordinate2DMake(ll.GetLatitudeInDegrees(), ll.GetLongitudeInDegrees())
                                                                indoorID:nil
                                                                 floorID:0];
                    }
                    
                    [model setEndLocation:location];
                    setStartLocationToCurrentLocation();
                    
                    if(!openable.Open(true))
                    {
                        if(openable.IsFullyOpen())
                        {
                            openable.Close();
                        }
                        return;
                    }
                    
                    [model sendNavEvent:@"combinedWidgetAnimateIn"];
                }
                
                void setStartLocationToCurrentLocation()
                {
                    Eegeo::Space::LatLong latLong(0.0, 0.0);
                    if(!iOSLocationService->GetLocation(latLong))
                    {
                        [model setStartLocation:nil];
                        return;
                    }
                    
                    WRLDNavLocation* location =
                    [[WRLDNavLocation alloc] initWithName:@"Current location"
                                                   latLon:CLLocationCoordinate2DMake(latLong.GetLatitudeInDegrees(), latLong.GetLongitudeInDegrees())
                                                 indoorID:nil
                                                  floorID:0];

                    [model setStartLocation:location];
                }
                
                //void modelSet() override {}
                
                void changeReceived(const std::string& keyPath) override
                {
                    if((keyPath == "startLocation") ||
                       (keyPath == "endLocation"))
                    {
                        m_pNavUIViewRouteUpdateHandler->UpdateRoute();
                    }
                    else if(keyPath == "route" && model.route == nil)
                    {
                        m_pNavUIViewRouteUpdateHandler->ClearRoute();
                    }
                }
                
                void eventReceived(const std::string& key) override
                {
                    if(key == "closeSetupJourneyClicked")
                    {
                        openable.Close();
                        m_pNavUIViewRouteUpdateHandler->ClearRoute();
                        [navModel() sendNavEvent:@"combinedWidgetAnimateOut"];
                    }
                    
                    else if(key == "selectStartLocationClicked")
                    {
                        NSLog(@"TDP eventReceived selectStartLocationClicked");
                    }
                    
                    else if(key == "selectEndLocationClicked")
                    {
                        NSLog(@"TDP eventReceived selectStartLocationClicked");
                    }
                }
            };
            
            NavUIViewModule::NavUIViewModule(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* searchResultsPoiViewInterop,
                                             Eegeo::iOS::iOSLocationService* iOSLocationService,
                                             ExampleApp::OpenableControl::View::IOpenableControlViewModel& openable,
                                             ExampleApp::NavRouting::SdkModel::NavRouteDrawingController& routeDrawingController,
                                             ExampleApp::NavRouting::SdkModel::NavRoutingServiceController& routingServiceController):
              d(new Private(searchResultsPoiViewInterop,
                            iOSLocationService,
                            openable))
            {
                d->model = [[WRLDNavModel alloc] init];
                d->setNavModel(d->model);
                
                d->m_pNavUIViewRouteUpdateHandler = Eegeo_NEW(NavUIViewRouteUpdateHandler)(d->model,
                                                                                           routeDrawingController,
                                                                                           routingServiceController);
                
                if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
                    d->view = [[WRLDNavWidgetTablet alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                else
                    d->view = [[WRLDNavWidgetPhone alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                
                [d->view setViewVisibilityWithAnimate:false hideViews:true];
                
                [d->view setAutoresizingMask:UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight];
                [[d->view observer] setNavModel:d->model];
            }

            NavUIViewModule::~NavUIViewModule()
            {
                delete d;
            }

            UIView& NavUIViewModule::GetNavUIView() const
            {
                return *d->view;
            }
        }
    }
}
