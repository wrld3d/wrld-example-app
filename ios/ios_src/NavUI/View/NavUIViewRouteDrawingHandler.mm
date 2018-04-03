// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavUIViewRouteDrawingHandler.h"

#include <MapKit/MapKit.h>

@interface NavUIViewRouteDrawingHandler()<WRLDNavModelObserverProtocol>
@end

@implementation NavUIViewRouteDrawingHandler
{
    ExampleApp::NavRouting::SdkModel::NavRouteDrawingController* m_pDrawingController;
    WRLDNavModel* m_navModel;
    
    WRLDNavModelObserver* m_navModelObserver;
}

- (instancetype) initWithDrawingController:(ExampleApp::NavRouting::SdkModel::NavRouteDrawingController*)drawingController
                              journeyModel:(WRLDNavModel*)navModel
{
    if (self = [super init])
    {
        m_pDrawingController = drawingController;
        m_navModel = navModel;
        
        m_navModelObserver = [[WRLDNavModelObserver alloc] initWithDelegate:self];
        [m_navModelObserver registerObserver:@"route"];
        
        [m_navModelObserver setNavModel:m_navModel];
        
        if (m_navModel.route != nil)
        {
            [self drawRoute:m_navModel.route];
        }
    }
    
    return self;
}

- (void) dealloc
{
    m_pDrawingController->ClearRoute();
    [super dealloc];
}

- (void) changeReceived: (NSString *)keyPath
{
    if([keyPath isEqual:@"route"])
    {
        m_pDrawingController->ClearRoute();
        
        if (m_navModel.route != nil)
        {
            [self drawRoute:m_navModel.route];
        }
    }
}

- (void)drawRoute:(WRLDNavRoute*)route
{
    std::vector<ExampleApp::NavRouting::SdkModel::NavRouteDrawingVertexData> verts;
    
    for (WRLDNavDirection *direction in route.directions)
    {
        if (direction.path.count < 2)
        {
            continue;
        }
        
        std::string indoorID;
        
        if (direction.indoorID != nil)
        {
            indoorID = std::string([direction.indoorID UTF8String]);
        }
        
        for (NSValue *point in direction.path)
        {
            CLLocationCoordinate2D latLng = point.MKCoordinateValue;
            
            verts.emplace_back(latLng.latitude, latLng.longitude, indoorID, static_cast<int>(direction.floorID), static_cast<bool>(direction.isMultiFloor));
        }
    }

    verts.erase(std::unique(verts.begin(), verts.end()), verts.end());
    
    m_pDrawingController->DrawRoute(verts);
}

@end
