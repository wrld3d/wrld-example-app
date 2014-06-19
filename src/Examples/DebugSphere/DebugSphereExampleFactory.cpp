// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DebugSphereExampleFactory.h"
#include "DebugSphereExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"

using namespace Examples;

DebugSphereExampleFactory::DebugSphereExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* DebugSphereExampleFactory::CreateExample() const
{
	return new Examples::DebugSphereExample(m_world.GetRenderContext(),
	                                        Eegeo::Space::LatLongAltitude::FromECEF(m_world.GetInterestPointProvider().GetEcefInterestPoint()),
	                                        m_globeCameraController);
}

std::string DebugSphereExampleFactory::ExampleName() const
{
	return Examples::DebugSphereExample::GetName();
}


