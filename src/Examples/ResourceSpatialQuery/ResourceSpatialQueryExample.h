//
//  SpatialResourceQueryExample.h
//  ExampleApp
//
//  Created by eeGeo on 14/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__SpatialResourceQueryExample__
#define __ExampleApp__SpatialResourceQueryExample__

#include "IExample.h"
#include "ResourceSpatialQueryService.h"
#include "Location.h"

namespace Examples
{
class ResourceSpatialQueryExample : public IExample
{
private:
	Eegeo::Resources::ResourceSpatialQueryService& m_resourceSpatialQueryService;
	Eegeo::Location::IInterestPointProvider& m_interestPointProvider;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	Eegeo::Streaming::MortonKey m_key;
	int m_numBuildings;

public:
	ResourceSpatialQueryExample(Eegeo::Resources::ResourceSpatialQueryService& resourceSpatialQueryService,
	                            Eegeo::Location::IInterestPointProvider& interestPointProvider,
	                            Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "ResourceSpatialQueryExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend() {}
};
}

#endif /* defined(__ExampleApp__SpatialResourceQueryExample__) */
