// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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


