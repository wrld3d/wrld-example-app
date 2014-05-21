//
//  SingleCityExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__SingleCityExampleFactory__
#define __ExampleApp__SingleCityExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class SingleCityExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
        
    public:
        SingleCityExampleFactory(Eegeo::EegeoWorld& world,
                                 Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);
        
        IExample* CreateExample() const;
    };
}

#endif /* defined(__ExampleApp__SingleCityExampleFactory__) */
