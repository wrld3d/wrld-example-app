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
                                                         Eegeo::Location::IInterestPointProvider& interestPointProvider)
:resourceSpatialQueryService(resourceSpatialQueryService)
,interestPointProvider(interestPointProvider)
,numBuildings(0)
{
    
}

void ResourceSpatialQueryExample::Update()
{
    Eegeo::dv3 ecefPointOfInterest = interestPointProvider.GetEcefInterestPoint();

    Eegeo::Streaming::MortonKeyLong lastKey = key;
    
    std::vector<Eegeo::Rendering::RenderableItem*> buildings = resourceSpatialQueryService.GetBuildingByEcefPoint(ecefPointOfInterest,
                                                                                                                 15,
                                                                                                                 10,
                                                                                                                 key);
    
    if(!(lastKey == key) || buildings.size() != numBuildings)
    {
        numBuildings = buildings.size();
        
        if(numBuildings == 0)
        {
            Eegeo_TTY("No resources detected\n");
        }
        else
        {
            Eegeo_TTY("%d buildings detected at camera focus point --> %s! (LOD %d)\n",
                      numBuildings,
                      key.ToString().c_str(),
                      key.Depth());
        }
    }
}