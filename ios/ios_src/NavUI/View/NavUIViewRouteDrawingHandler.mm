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
        
        m_navModelObserver = [[WRLDNavModelObserver alloc] init];
        [m_navModelObserver setDelegate:self];
        [m_navModelObserver registerObserver:@"route"];
        [m_navModelObserver registerObserver:@"currentDirection"];
        
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
        return;
    }
    
    if([keyPath isEqual:@"currentDirection"])
    {
        if (m_navModel.currentDirection>0)
        {
            m_pDrawingController->SetRouteColor(static_cast<int>(m_navModel.currentDirection-1), Eegeo::v4(0, 0, 1, 0.8));
        }
        m_pDrawingController->SetRouteColor(static_cast<int>(m_navModel.currentDirection), Eegeo::v4(0, 1, 0, 0.8));
    }
}

- (void)drawRoute:(WRLDNavRoute*)route
{
    int directionId = 0;
    for (WRLDNavDirection *direction in route.directions)
    {
        std::vector<ExampleApp::NavRouting::SdkModel::NavRouteDrawingVertexData> verts;
        
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
        
        verts.erase(std::unique(verts.begin(), verts.end()), verts.end());
        m_pDrawingController->AddRoute(directionId, verts, Eegeo::v4(1, 0, 0, 0.8));
        directionId++;
    }
}

@end
