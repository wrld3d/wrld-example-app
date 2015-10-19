// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "InteriorsCustomMaterials.h"
#include "VectorMath.h"

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
            
            
            struct InteriorsCustomCubeMapTextureDto
            {
                std::string textureKey;
                std::string positiveXFilename;
                std::string negativeXFilename;
                std::string positiveYFilename;
                std::string negativeYFilename;
                std::string positiveZFilename;
                std::string negativeZFilename;
            };
            
            struct InteriorsCustomMaterialDto
            {
                std::string materialName;
                std::vector<std::pair<std::string, std::string> > keyValueStrings;
                std::vector<std::pair<std::string, Eegeo::v4> >  keyValueColors;
                std::vector<std::pair<std::string, float> > keyValueScalars;
            };
        }
    }
}