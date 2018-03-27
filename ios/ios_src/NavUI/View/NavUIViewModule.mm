// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavUIViewModule.h"

#include "WrldJourneysWidget/WrldJourneysWidget.h"
#include "WrldJourneys/WRLDNavModelObserverCpp.h"

#include "WrldJourneysWidget/WrldJourneysWidget-Swift.h"

#include "SearchResultPoiViewInterop.h"

#include "iOSLocationService.h"

//Wrld Example App fudges the propagation of touch events so to prevent our touch events getting
//passed down to the Map we need to extend our common widget with a consumesTouch selector.
@interface WrldNavWidgetBase(ExampleApp)
- (BOOL)consumesTouch:(UITouch *)touch;
@end

@implementation WrldNavWidgetBase(ExampleApp)
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
                JourneysModel* model{nullptr};
                WrldNavWidgetBase* view{nullptr};
                
                ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* searchResultsPoiViewInterop;
                Eegeo::iOS::iOSLocationService* iOSLocationService;
                
                Eegeo::Helpers::TCallback1<Private, Search::SdkModel::SearchResultModel> directionsClickedCallbackObj;
                
                Private(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* searchResultsPoiViewInterop_,
                        Eegeo::iOS::iOSLocationService* iOSLocationService_):
                    searchResultsPoiViewInterop(searchResultsPoiViewInterop_),
                    iOSLocationService(iOSLocationService_),
                    directionsClickedCallbackObj(this, &Private::directionsClickedCallback)
                {
                    searchResultsPoiViewInterop->InsertDirectionsCallback(directionsClickedCallbackObj);
                }
                
                ~Private()
                {
                    searchResultsPoiViewInterop->RemoveDirectionsCallback(directionsClickedCallbackObj);
                    [view release];
                    [model release];
                }
                
                //Called when the 'Directions' button on the POI card is clicked
                void directionsClickedCallback(Search::SdkModel::SearchResultModel& searchResultModel)
                {
                    WRLDNavLocation* location = [[WRLDNavLocation alloc] init];
                    
                    [location setName: [NSString stringWithCString:searchResultModel.GetTitle().c_str()
                                                          encoding:[NSString defaultCStringEncoding]]];
                    
                    const Eegeo::Space::LatLong& ll =  searchResultModel.GetLocation();
                    [location setLatLon: CLLocationCoordinate2DMake(ll.GetLatitude(), ll.GetLongitude())];
                    
                    if(searchResultModel.IsInterior())
                    {
                        const Eegeo::Resources::Interiors::InteriorId& interior = searchResultModel.GetBuildingId();
                        [location setIndoorID: [NSString stringWithCString:interior.Value().c_str()
                                                                  encoding:[NSString defaultCStringEncoding]]];
                        [location setFloorID: searchResultModel.GetFloor()];
                    }
                    else
                    {
                        [location setIndoorID: nil];
                        [location setFloorID: 0];
                    }
                    
                    [model setEndLocation:location];
                    setStartLocationToCurrentLocation();
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
                    
                    WRLDNavLocation* location = [[WRLDNavLocation alloc] init];
                    
                    [location setName: @"Current location"];
                    [location setLatLon: CLLocationCoordinate2DMake(latLong.GetLatitudeInDegrees(), latLong.GetLongitudeInDegrees())];
                    [location setIndoorID: nil];
                    [location setFloorID: 0];
                    [model setStartLocation:location];
                    
                    NSLog(@"TDP lon %f", [location latLon].longitude);
                    NSLog(@"TDP lat %f", [location latLon].latitude);
                }
                
                void modelSet() override
                {
                    NSLog(@"TDP modelSet");
                }
                
                void changeReceived(const std::string& keyPath) override
                {
                    NSLog(@"TDP changeReceived");
                }
                
                void eventReceived(const std::string& key) override
                {
                    if(key == "closeSetupJourneyClicked")
                    {
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
                                             Eegeo::iOS::iOSLocationService* iOSLocationService):
              d(new Private(searchResultsPoiViewInterop,
                            iOSLocationService))
            {
                d->model = [[JourneysModel alloc] init];                
                d->setNavModel(d->model);
                
                if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
                    d->view = [[WrldNavWidgetTablet alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                else
                    d->view = [[WrldNavWidgetPhone alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
                
                [d->view setViewVisibilityWithAnimate:false hideViews:true];
                
                [d->view setAutoresizingMask:UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight];
                [[d->view observer] setJourneysModel:d->model]; 
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
