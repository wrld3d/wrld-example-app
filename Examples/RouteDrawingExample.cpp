//
//  RouteDrawingExample.cpp
//  ExampleApp
//
//  Created by Scott on 14/11/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "RouteDrawingExample.h"
#include "RouteBuilder.h"
#include "VectorMath.h"

using namespace Examples;
using namespace Eegeo;
using namespace Eegeo::Routes;

RouteDrawingExample::RouteDrawingExample(RouteService& routeService,
                                         EegeoWorld& world)
:m_routeService(routeService)
,m_world(world)
,m_createdRoutes(false)
{
    
}

void RouteDrawingExample::Update()
{
    //Defer creating the routes until the loading state is over.
    if(m_world.Initialising()) {
        return;
    }
    
    //Just create the routes once.
    if(!m_createdRoutes)
    {
        //An arbitrarily selected default half-width for the route line segments.
        float halfWidth = 5.f;

        //The color format is (Red, Green, Blue, Transparency - 0.0 is fully transparent and 1.0 is fully opaque).
        Eegeo::v4 routeRed(1, 0, 0, 0.6f);
        Eegeo::v4 routeGreen(0, 1, 0, 0.6f);
        Eegeo::v4 routeBlue(0, 0, 1, 0.6f);
        
        //An arbitrarily selected altitude for the route visualisation.
        float altitudeMeters = 3.f;
        
        //The route builder helper object provides a fluent interface to make building a route simpler.
        RouteBuilder builder;
        
        //We want the set of route vertices, and we get it by starting with an initial color and width and
        //adding points. This route starts near the Transamerica Pyramid.
        //
        //We can add points by (latDegrees, longDegrees, altitudeMeters) tuples or by a LatLongAltitide object..
        //
        //The color can be changed arbitrarily along the route.
        //
        std::vector<RouteVertex> points = builder.Start(routeRed, halfWidth)
        .AddPoint(37.795729,-122.401698, altitudeMeters)
        .AddPoint(37.794873,-122.401516, altitudeMeters)
        .AddPoint(37.794728,-122.403179, altitudeMeters)
        .ChangeColor(routeGreen)
        .AddPoint(37.794483,-122.404863, altitudeMeters)
        .AddPoint(37.793618,-122.404670, altitudeMeters)
        .AddPoint(37.793813,-122.403007, altitudeMeters)
        .ChangeColor(routeRed)
        .AddPoint(37.792940,-122.402825, altitudeMeters)
        .AddPoint(37.793109,-122.401108, altitudeMeters)
        .AddPoint(37.792143,-122.400990, altitudeMeters)
        .AddPoint(37.790303,-122.400603, altitudeMeters)
        .AddPoint(37.790324,-122.400126, altitudeMeters)
        .AddPoint(37.794449,-122.394906, altitudeMeters)
        .ChangeColor(routeBlue)
        .AddPoint(37.793253,-122.393238, altitudeMeters)
        .ChangeColor(routeRed)
        .AddPoint(37.793707,-122.392578, altitudeMeters)
        .FinishRoute(); //Calling FinishRoute returns to us the set of points...
        
        //We can now create a route from this set of points.
        //
        //The route can be created using the CreateRoute method on the RouteService, which must
        //be destroyed through the complementary DestroyRoute method on RouteService.
        Route* route = m_routeService.CreateRoute(points);
        
        //Keep a reference to the route so we can Destroy it later.
        m_routes.push_back(route);
        
        //Create a separate route to demonstrate multiple routes drawing at once...
        //
        //This route surrounds AT & T Park. This route has some nasty data; the route
        //doubles back on itself (to produce exactly oppositing poly-line segments)
        //and has a duplicated point, but still renders.
        std::vector<RouteVertex> otherPoints = builder.Start(routeBlue, halfWidth/2.f)
        .AddPoint(37.779483,-122.388609,altitudeMeters)
        .AddPoint(37.779916,-122.389317,altitudeMeters)
        .ChangeColor(routeGreen)
        //a nasty bit with a dupe point and a parallel line
        .AddPoint(37.777957,-122.391785,altitudeMeters)
        .AddPoint(37.779916,-122.389317,altitudeMeters)
        .AddPoint(37.777957,-122.391785,altitudeMeters)
        .AddPoint(37.777957,-122.391785,altitudeMeters)
        .ChangeColor(routeRed)
        .AddPoint(37.777126,-122.390551,altitudeMeters)
        .AddPoint(37.776134,-122.389972,altitudeMeters)
        .ChangeColor(routeBlue)
        .AddPoint(37.776397,-122.387922,altitudeMeters)
        .FinishRoute();
        
        m_routes.push_back(m_routeService.CreateRoute(otherPoints));
        
        //We have created the routes so don't need to do so again.
        m_createdRoutes = true;
    }
}

void RouteDrawingExample::Suspend()
{
    //Destroy all of the routes...
    for(std::vector<Route*>::iterator i = m_routes.begin(); i != m_routes.end(); ++ i)
    {
        //Destroy the route - we do not need to delete the route pointer ourselves, the API will handle this
        //as well as cleaning up associated views, etc.
        m_routeService.DestroyRoute(*i);
    }
    
    m_routes.clear();
    m_createdRoutes = false;
}