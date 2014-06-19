// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteThicknessPolicyExample.h"
#include "RouteBuilder.h"
#include "VectorMath.h"
#include "RouteStyle.h"
#include "CameraHelpers.h"

using namespace Examples;
using namespace Eegeo;
using namespace Eegeo::Routes;

RouteThicknessPolicyExample::RouteThicknessPolicyExample(RouteService& routeService,
        Eegeo::Rendering::RenderContext& renderContext,
        EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_routeService(routeService)
	,m_world(world)
	,m_createdRoutes(false)
	,m_linearAltitudeBasedRouteThicknessPolicy(renderContext)
	,m_globeCameraStateRestorer(cameraController)
{
	Eegeo::Space::EcefTangentBasis cameraInterestBasis;

	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
	    Eegeo::Space::LatLong::FromDegrees(37.793348, -122.399035).ToECEF(),
	    354.824249,
	    cameraInterestBasis);

	cameraController.SetView(cameraInterestBasis, 1374.298706);
}

void RouteThicknessPolicyExample::Update(float dt)
{
	//Defer creating the routes until the loading state is over.
	if(m_world.Initialising())
	{
		return;
	}

	//Just create the routes once.
	if(!m_createdRoutes)
	{
		//Some route data...
		const float halfWidth = 5.f;
		const float routeSpeedMetersPerSecond = 40.f;
		const Eegeo::v4 routeColor(1, 0, 1, 0.6f);
		const float altitudeMeters = 3.f;

		RouteBuilder builder;

		//// Demonstrate a custom route scaling policy on a route around the transamerica pyramid.
		//// This route animates to thicken and thin.
		std::vector<Eegeo::Routes::RouteVertex> transamericaPyramidRoutePoints = builder.Start(routeColor, halfWidth, routeSpeedMetersPerSecond, Routes::Road)
		        .AddPoint(37.795729,-122.401698, altitudeMeters)
		        .AddPoint(37.794873,-122.401516, altitudeMeters)
		        .AddPoint(37.794728,-122.403179, altitudeMeters)
		        .AddPoint(37.794483,-122.404863, altitudeMeters)
		        .AddPoint(37.793618,-122.404670, altitudeMeters)
		        .AddPoint(37.793813,-122.403007, altitudeMeters)
		        .AddPoint(37.792940,-122.402825, altitudeMeters)
		        .AddPoint(37.793109,-122.401108, altitudeMeters)
		        .AddPoint(37.792143,-122.400990, altitudeMeters)
		        .AddPoint(37.790303,-122.400603, altitudeMeters)
		        .AddPoint(37.790324,-122.400126, altitudeMeters)
		        .AddPoint(37.794449,-122.394906, altitudeMeters)
		        .AddPoint(37.793253,-122.393238, altitudeMeters)
		        .AddPoint(37.793707,-122.392578, altitudeMeters)
		        .FinishRoute();

		Eegeo::Routes::Style::RouteStyle transamericaPyramidStyle(Eegeo::Routes::Style::RouteStyle::JoinStyleArc, &m_myScalingRouteThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
		Route* transamericaPyramidRoute = m_routeService.CreateRoute(transamericaPyramidRoutePoints, transamericaPyramidStyle, false);
		m_routes.push_back(transamericaPyramidRoute);

		//// Demonstrate the built-in altitude based route scaling policy on a route at north treasure isle. This route thickens as the camera
		//// altitude increases.
		std::vector<Eegeo::Routes::RouteVertex> northTreasureIsleRoutePoints = builder.Start(routeColor, halfWidth, routeSpeedMetersPerSecond, Routes::Road)
		        .AddPoint(37.827209,-122.377746,altitudeMeters)
		        .AddPoint(37.826057,-122.37663,altitudeMeters)
		        .AddPoint(37.825802,-122.374223,altitudeMeters)
		        .AddPoint(37.825921,-122.372035,altitudeMeters)
		        .AddPoint(37.826802,-122.369674,altitudeMeters)
		        .AddPoint(37.828667,-122.369159,altitudeMeters)
		        .AddPoint(37.830209,-122.369824,altitudeMeters)
		        .AddPoint(37.830328,-122.373172,altitudeMeters)
		        .FinishRoute();

		Eegeo::Routes::Style::RouteStyle northTreasureIsleStyle(Eegeo::Routes::Style::RouteStyle::JoinStyleArc, &m_linearAltitudeBasedRouteThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
		Route* northTreasureIsleRoute = m_routeService.CreateRoute(northTreasureIsleRoutePoints, northTreasureIsleStyle, false);
		m_routes.push_back(northTreasureIsleRoute);

		//// Demonstrate the built-in identity route scaling policy on a route at south treasure isle. This route remains
		//// the same thickness.
		std::vector<Eegeo::Routes::RouteVertex> southTreasureIsleRoutePoints = builder.Start(routeColor, halfWidth, routeSpeedMetersPerSecond, Routes::Road)
		        .AddPoint(37.818226,-122.370339,altitudeMeters)
		        .AddPoint(37.820294,-122.371713,altitudeMeters)
		        .AddPoint(37.821599,-122.370940,altitudeMeters)
		        .AddPoint(37.822701,-122.368279,altitudeMeters)
		        .AddPoint(37.822260,-122.366735,altitudeMeters)
		        .AddPoint(37.820277,-122.365361,altitudeMeters)
		        .FinishRoute();

		Eegeo::Routes::Style::RouteStyle southTreasureIsleStyle(Eegeo::Routes::Style::RouteStyle::JoinStyleHard, &m_identityRouteThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
		Route* southTreasureIsleRoute = m_routeService.CreateRoute(southTreasureIsleRoutePoints, southTreasureIsleStyle, false);
		m_routes.push_back(southTreasureIsleRoute);


		//We have created the routes so don't need to do so again.
		m_createdRoutes = true;
	}

	//Update our custom thickness policy to make it animate.
	m_myScalingRouteThicknessPolicy.UpdateScale();
}

void RouteThicknessPolicyExample::MyScalingRouteThicknessPolicy::UpdateScale()
{
	m_scale = m_scale + ((1.f/30.f/5.f) * (m_scaledown ? -1.f : 1.f));
	m_scaledown = m_scaledown ? m_scale > 0.5f : (!m_scaledown ? m_scale > 2.f : false);
}

float RouteThicknessPolicyExample::MyScalingRouteThicknessPolicy::GetThicknessScale(const Fitting::FittedRoute& route) const
{
	return m_scale;
}

void RouteThicknessPolicyExample::Suspend()
{
	//Destroy all of the routes...
	for(std::vector<Route*>::iterator i = m_routes.begin(); i != m_routes.end(); ++ i)
	{
		m_routeService.DestroyRoute(*i);
	}

	m_routes.clear();
	m_createdRoutes = false;
}
