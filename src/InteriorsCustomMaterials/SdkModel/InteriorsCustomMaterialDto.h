// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "InteriorsCustomMaterials.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
            struct InteriorsCustomTextureDto
            {
                std::string textureKey;
                std::string filename;
            };
            
            struct InteriorsCustomMaterialDto
            {
                std::string materialName;
                std::string materialType;
                std::vector<InteriorsCustomTextureDto> textures;
            };
        }
    }
}