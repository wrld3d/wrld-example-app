//
//  WebRequestExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

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
