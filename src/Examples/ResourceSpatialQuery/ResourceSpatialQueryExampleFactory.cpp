//
//  ResourceSpatialQueryExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "ResourceSpatialQueryExampleFactory.h"
#include "ResourceSpatialQueryExample.h"

using namespace Examples;

ResourceSpatialQueryExampleFactory::ResourceSpatialQueryExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* ResourceSpatialQueryExampleFactory::CreateExample() const
{
	return new Examples::ResourceSpatialQueryExample(m_world.GetResourceSpatialQueryService(),
	        m_world.GetInterestPointProvider(),
	        m_globeCameraController);
}

std::string ResourceSpatialQueryExampleFactory::ExampleName() const
{
	return Examples::ResourceSpatialQueryExample::GetName();
}


