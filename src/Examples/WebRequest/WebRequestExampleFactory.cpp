// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WebRequestExampleFactory.h"
#include "WebRequestExample.h"

using namespace Examples;

WebRequestExampleFactory::WebRequestExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* WebRequestExampleFactory::CreateExample() const
{
	return new Examples::WebRequestExample(m_world.GetWebRequestFactory(),
	                                       m_globeCameraController);
}

std::string WebRequestExampleFactory::ExampleName() const
{
	return Examples::WebRequestExample::GetName();
}
