//
//  LoadModelExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "LoadModelExampleFactory.h"
#include "LoadModelExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"
#include "LocalAsyncTextureLoader.h"

using namespace Examples;

LoadModelExampleFactory::LoadModelExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* LoadModelExampleFactory::CreateExample() const
{
	return new Examples::LoadModelExample(m_world.GetRenderContext(),
	                                      Eegeo::Space::LatLongAltitude::FromECEF(m_world.GetInterestPointProvider().GetEcefInterestPoint()),
	                                      m_world.GetFileIO(),
	                                      m_world.GetLocalAsyncTextureLoader(),
	                                      m_world.GetGlobalFogging(),
	                                      m_globeCameraController);
}

std::string LoadModelExampleFactory::ExampleName() const
{
	return Examples::LoadModelExample::GetName();
}

