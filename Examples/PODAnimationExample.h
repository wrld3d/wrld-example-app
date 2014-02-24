//
//  PODAnimationExample.h
//  ExampleApp
//
//  Created by Scott on 05/08/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__PODAnimationExample__
#define __ExampleApp__PODAnimationExample__

#include "IExample.h"
#include "RenderContext.h"
#include "LatLongAltitude.h"

#include "Model.h"

namespace Examples
{    
    class PODAnimationExample : public IExample
    {
    private:
        
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Helpers::IFileIO& fileIO;
        Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor;
        Eegeo::Lighting::GlobalFogging& globalFogging;
        
        Eegeo::Model* pModel;
        
    public:
        PODAnimationExample(Eegeo::Rendering::RenderContext& renderContext,
                         Eegeo::Helpers::IFileIO& fileIO,
                         Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                         Eegeo::Lighting::GlobalFogging& fogging);
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__PODAnimationExample__) */
