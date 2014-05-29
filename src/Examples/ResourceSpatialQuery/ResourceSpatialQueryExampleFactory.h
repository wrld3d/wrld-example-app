//
//  ResourceSpatialQueryExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__ResourceSpatialQueryExampleFactory__
#define __ExampleApp__ResourceSpatialQueryExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class ResourceSpatialQueryExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
        
    public:
        ResourceSpatialQueryExampleFactory(Eegeo::EegeoWorld& world,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}

#endif /* defined(__ExampleApp__ResourceSpatialQueryExampleFactory__) */
