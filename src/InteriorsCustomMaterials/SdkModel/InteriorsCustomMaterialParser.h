// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "InteriorsCustomMaterials.h"
#include "Types.h"

#include <vector>
#include <string>


namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
        
            struct InteriorsCustomMaterialParserResult
            {
                std::vector<InteriorsCustomTextureDto> textureDtos;
                std::vector<InteriorsCustomCubeMapTextureDto> cubeMapTextureDtos;
                std::vector<InteriorsCustomMaterialDto> materialDtos;
            };
            
            class InteriorsCustomMaterialParser : private Eegeo::NonCopyable
            {
            public:
                InteriorsCustomMaterialParserResult Parse(const std::string& materialsJson) const;
            };
            
            
        }
    }
}
