// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SingleCityExampleFactory.h"
#include "SingleCityExample.h"

using namespace Examples;

SingleCityExampleFactory::SingleCityExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* SingleCityExampleFactory::CreateExample() const
{
	return new Examples::SingleCityExample(m_globeCameraController,
	                                       m_world.GetPrecachingService(),
	                                       m_world.GetStreamingVolumeController(),
	                                       m_world,
	                                       m_globeCameraController);
}

std::string SingleCityExampleFactory::ExampleName() const
{
	return Examples::SingleCityExample::GetName();
}
