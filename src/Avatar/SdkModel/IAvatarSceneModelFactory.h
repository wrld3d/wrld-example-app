// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include <string>
#include "Rendering.h"
#include "LayerIds.h"
#include "IAnimatedSceneModel.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            
            
            class IAvatarSceneModelFactory
            {
            public:
                
                virtual ~IAvatarSceneModelFactory() {}
                
                virtual IAnimatedSceneModel* CreateModel(const std::string& fileName,
                                                       const Eegeo::Rendering::LayerIds::Values& renderingLayer) = 0;
            };
        }
    }
}