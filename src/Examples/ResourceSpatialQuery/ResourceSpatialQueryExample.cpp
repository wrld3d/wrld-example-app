//
//  SpatialResourceQueryExample.cpp
//  ExampleApp
//
//  Created by eeGeo on 14/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "ResourceSpatialQueryExample.h"
#include "IInterestPointProvider.h"

using namespace Examples;

ResourceSpatialQueryExample::ResourceSpatialQueryExample(Eegeo::Resources::ResourceSpatialQueryService& resourceSpatialQueryService,
        Eegeo::Location::IInterestPointProvider& interestPointProvider,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_resourceSpatialQueryService(resourceSpatialQueryService)
	,m_interestPointProvider(interestPointProvider)
	,m_numBuildings(0)
	,m_key(0)
	,m_globeCameraStateRestorer(cameraController)
{

}

void ResourceSpatialQueryExample::Update(float dt)
{
	Eegeo::dv3 ecefPointOfInterest = m_interestPointProvider.GetEcefInterestPoint();

	Eegeo::Streaming::MortonKey lastKey = m_key;

	std::vector<const Eegeo::Rendering::Scene::SceneElement<Eegeo::Rendering::Renderables::PackedRenderable>*> buildings = m_resourceSpatialQueryService.GetBuildingByEcefPoint(ecefPointOfInterest,
	        15,
	        10,
	        m_key);

	if(!(lastKey == m_key) || buildings.size() != m_numBuildings)
	{
		m_numBuildings = buildings.size();

		if(m_numBuildings == 0)
		{
			Eegeo_TTY("No resources detected\n");
		}
		else
		{
			Eegeo_TTY("%d buildings detected at camera focus point --> %s! (LOD %d)\n",
			          m_numBuildings,
			          m_key.ToString().c_str(),
			          m_key.Depth());
		}
	}
}