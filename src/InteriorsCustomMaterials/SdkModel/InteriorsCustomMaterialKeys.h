// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "InteriorsCustomMaterials.h"


#include <string>

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
            namespace InteriorsCustomMaterialKeys
            {
                const static std::string Textures = "Textures";
                const static std::string CubeMapTextures = "CubeMapTextures";
                const static std::string Materials = "Materials";
                const static std::string TextureKey = "TextureKey";
                const static std::string Filename = "Filename";
                const static std::string MaterialType = "MaterialType";
                const static std::string MaterialName = "MaterialName"; 
                const static std::string InteriorsDiffuseUntexturedMaterial = "InteriorsDiffuseUntexturedMaterial";
                const static std::string InteriorsDiffuseTexturedMaterial = "InteriorsDiffuseTexturedMaterial";
                const static std::string InteriorsSpecularMaterial = "InteriorsSpecularMaterial";
                const static std::string InteriorsCubeMappedMaterial = "InteriorsCubeMappedMaterial";
            }
        }
    }
}