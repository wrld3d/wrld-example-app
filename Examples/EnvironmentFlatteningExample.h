//
//  EnvironmentFlatteningExample.h
//  ExampleApp
//
//  Created by Scott on 04/06/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__EnvironmentFlatteningExample__
#define __ExampleApp__EnvironmentFlatteningExample__

#include "IExample.h"
#include "EnvironmentFlatteningService.h"

namespace Examples
{
    class EnvironmentFlatteningExample : public IExample
    {
    private:
        long long lastToggle;
        bool scaleUp;
        Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService;
        
    public:
        EnvironmentFlatteningExample(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);
        
        void Start() {}
        void Update(float dt);
        void Draw() {}
        void Suspend() {}
    };
}


#endif /* defined(__ExampleApp__EnvironmentFlatteningExample__) */
