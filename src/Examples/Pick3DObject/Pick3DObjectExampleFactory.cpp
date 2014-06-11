//
//  Pick3DObjectExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "Pick3DObjectExampleFactory.h"
#include "Pick3DObjectExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"

using namespace Examples;

Pick3DObjectExampleFactory::Pick3DObjectExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* Pick3DObjectExampleFactory::CreateExample() const
{
	return new Examples::Pick3DObjectExample(m_world.GetRenderContext(),
	        Eegeo::Space::LatLongAltitude::FromECEF(m_world.GetInterestPointProvider().GetEcefInterestPoint()),
	        m_world.GetCameraProvider(),
	        m_globeCameraController);
}

std::string Pick3DObjectExampleFactory::ExampleName() const
{
	return Examples::Pick3DObjectExample::GetName();
}

