//
//  WebRequestExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__WebRequestExampleFactory__
#define __ExampleApp__WebRequestExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class WebRequestExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
        
    public:
        WebRequestExampleFactory(Eegeo::EegeoWorld& world,
                                 Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}

#endif /* defined(__ExampleApp__WebRequestExampleFactory__) */
