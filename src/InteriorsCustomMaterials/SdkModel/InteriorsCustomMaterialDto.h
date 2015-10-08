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
                std::string TextureKey;
                std::string Filename;
            };
            
            struct InteriorsCustomMaterialDto
            {
                std::string MaterialName;
                std::string MaterialType;
                std::vector<InteriorsCustomTextureDto> Textures;
            };
        }
    }
}