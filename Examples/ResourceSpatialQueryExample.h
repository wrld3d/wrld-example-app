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
#include "NewGlobeCamera.h"

namespace Examples
{
    class ResourceSpatialQueryExample : public IExample
    {
    private:
        Eegeo::Resources::ResourceSpatialQueryService& resourceSpatialQueryService;
        Eegeo::Camera::NewGlobeCamera& globeCamera;
        
        Eegeo::Streaming::MortonKeyLong key;
        int numBuildings;
        
    public:
        ResourceSpatialQueryExample(Eegeo::Resources::ResourceSpatialQueryService& resourceSpatialQueryService,
                                    Eegeo::Camera::NewGlobeCamera& globeCamera);
        
        void Start() {}
        void Update();
        void Draw() {}
        void Suspend() {}
    };
}

#endif /* defined(__ExampleApp__SpatialResourceQueryExample__) */
