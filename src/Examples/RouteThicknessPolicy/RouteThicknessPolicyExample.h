// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteThicknessPolicyExample__
#define __ExampleApp__RouteThicknessPolicyExample__

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "Route.h"
#include "EegeoWorld.h"
#include "IdentityRouteThicknessPolicy.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"
#include "FittedRoute.h"

namespace Examples
{
class RouteThicknessPolicyExample : public IExample
{
private:
	class MyScalingRouteThicknessPolicy : public Eegeo::Routes::Style::Thickness::IRouteThicknessPolicy
	{
		float m_scale;
		bool m_scaledown;
		float GetThicknessScale(const Eegeo::Routes::Fitting::FittedRoute& route) const;
	public:
		MyScalingRouteThicknessPolicy():m_scale(1.f), m_scaledown(false) {}
		void UpdateScale();
	};

	Eegeo::Routes::RouteService& m_routeService;
	Eegeo::EegeoWorld& m_world;

	bool m_createdRoutes;
	std::vector<Eegeo::Routes::Route*> m_routes;
	Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_identityRouteThicknessPolicy;
	Eegeo::Routes::Style::Thickness::LinearAltitudeBasedRouteThicknessPolicy m_linearAltitudeBasedRouteThicknessPolicy;
	MyScalingRouteThicknessPolicy m_myScalingRouteThicknessPolicy;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

public:
	RouteThicknessPolicyExample(Eegeo::Routes::RouteService& routeService,
	                            Eegeo::Rendering::RenderContext& renderContext,
	                            Eegeo::EegeoWorld& eegeoWorld,
	                            Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "RouteThicknessPolicyExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend();
};
}

#endif /* defined(__ExampleApp__RouteThicknessPolicyExample__) */
