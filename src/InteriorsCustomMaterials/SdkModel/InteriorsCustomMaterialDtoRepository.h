// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once


#include "Interiors.h"
#include "IInteriorsCustomMaterialDtoRepository.h"
#include "Types.h"

#include <string>
#include <map>

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
            class InteriorsCustomMaterialDtoRepository : public IInteriorsCustomMaterialDtoRepository, private Eegeo::NonCopyable
            {
            public:
                typedef std::map<std::string, InteriorsCustomMaterialDto> TMaterialKeyToData;
                
                InteriorsCustomMaterialDtoRepository();
                
                void Add(const InteriorsCustomMaterialDto& interiorMaterialDto);
                bool Contains(const std::string& materialKey) const;
                InteriorsCustomMaterialDto Get(const std::string& materialKey) const;

            private:
                TMaterialKeyToData m_materialKeyToData;
            };
        }
    }
}