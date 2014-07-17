// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteDrawingExample.h"
#include "RouteBuilder.h"
#include "VectorMath.h"
#include "RouteStyle.h"
#include "CameraHelpers.h"

using namespace Examples;
using namespace Eegeo;
using namespace Eegeo::Routes;

RouteDrawingExample::RouteDrawingExample(RouteService& routeService,
        EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_routeService(routeService)
	,m_world(world)
	,m_createdRoutes(false)
	,m_globeCameraStateRestorer(cameraController)
{
	Eegeo::Space::EcefTangentBasis cameraInterestBasis;

	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
	    Eegeo::Space::LatLong::FromDegrees(37.793348, -122.399035).ToECEF(),
	    354.824249,
	    cameraInterestBasis);

	cameraController.SetView(cameraInterestBasis, 1374.298706);
}

void RouteDrawingExample::Update(float dt)
{
	//Defer creating the routes until the loading state is over.
	if(m_world.Initialising())
	{
		return;
	}

	//Just create the routes once.
	if(!m_createdRoutes)
	{
		//An arbitrarily selected default half-width for the route line segments.
		const float halfWidth = 5.f;
		const float routeSpeedMetersPerSecond = 40.f;

		//The color format is (Red, Green, Blue, Transparency - 0.0 is fully transparent and 1.0 is fully opaque).
		const Eegeo::v4 routeRed(1, 0, 0, 0.6f);
		const Eegeo::v4 routeGreen(0, 1, 0, 0.6f);
		const Eegeo::v4 routeBlue(0, 0, 1, 0.6f);

		//An arbitrarily selected altitude for the route visualisation.
		const float altitudeMeters = 3.f;

		//The route builder helper object provides a fluent interface to make building a route simpler.
		RouteBuilder builder;

		//We want the set of route vertices, and we get it by starting with an initial color and width and
		//adding points. This route starts near the Transamerica Pyramid.
		//
		//We can add points by (latDegrees, longDegrees, altitudeMeters) tuples or by a LatLongAltitide object..
		//
		//The color can be changed arbitrarily along the route.
		//
		std::vector<RouteVertex> points = builder.Start(routeRed, halfWidth, routeSpeedMetersPerSecond, Routes::Road)
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

		// A route thickness scaling policy should be provided; this informs the route how it should modify its thickness
		// (for example, based on camera altitude, or to play a "pulse" animation). Two implementations are provided; the
		// IdentityRouteThicknessPolicy and the LinearAltitudeScaleBasedRouteThicknessPolicy. For this example we use the
		// identity policy which will not modify the thickness of the route. The style accepts a const reference, so it
		// does not take ownership over the thickness policy.
		Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);

		//We can now create a route from this set of points.
		//
		//The route can be created using the CreateRoute method on the RouteService, which must
		//be destroyed through the complementary DestroyRoute method on RouteService.
		Route* route = m_routeService.CreateRoute(points, routeStyle, false);

		//Keep a reference to the route so we can Destroy it later.
		m_routes.push_back(route);

		//Create a separate route to demonstrate multiple routes drawing at once...
		//
		//This route surrounds AT & T Park. This route has some nasty data; the route
		//doubles back on itself (to produce exactly opposing poly-line segments)
		//and has a duplicated point, but still renders.
		std::vector<RouteVertex> otherPoints = builder.Start(routeBlue, halfWidth/2.f, routeSpeedMetersPerSecond, Routes::Road)
		                                       .AddPoint(37.779483,-122.388609,altitudeMeters)
		                                       .AddPoint(37.779916,-122.389317,altitudeMeters)
		                                       .ChangeColor(routeGreen)
		                                       //a nasty bit with a duplicated point and a parallel line
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

		m_routes.push_back(m_routeService.CreateRoute(otherPoints, routeStyle, false));

		//this route curves around entirely on itself, and traces the bounds of treasure island
		std::vector<RouteVertex> islandCircuitPoints = builder.Start(routeGreen, halfWidth, routeSpeedMetersPerSecond, Routes::Road)
		        .AddPoint(37.826701,-122.379162, altitudeMeters)
		        .AddPoint(37.830429,-122.377531, altitudeMeters)
		        .AddPoint(37.832328,-122.373368, altitudeMeters)
		        .AddPoint(37.831209,-122.368605, altitudeMeters)
		        .AddPoint(37.822633,-122.362983, altitudeMeters)
		        .AddPoint(37.818768,-122.364313, altitudeMeters)
		        .AddPoint(37.816158,-122.371480, altitudeMeters)
		        .AddPoint(37.818294,-122.373368, altitudeMeters)
		        .AddPoint(37.816938,-122.375128, altitudeMeters)
		        .AddPoint(37.820226,-122.374742, altitudeMeters)
		        .AddPoint(37.824158,-122.377574, altitudeMeters)
		        .FinishRoute();

		m_routes.push_back(m_routeService.CreateRoute(islandCircuitPoints, routeStyle, false));

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
