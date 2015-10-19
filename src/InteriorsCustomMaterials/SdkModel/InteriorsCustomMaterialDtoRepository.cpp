// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsCustomMaterialDtoRepository.h"
#include "InteriorsCustomMaterialDto.h"

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {

                
            InteriorsCustomMaterialDtoRepository::InteriorsCustomMaterialDtoRepository()
            {
                
            }

            
            void InteriorsCustomMaterialDtoRepository::Add(const InteriorsCustomMaterialDto& interiorMaterialDto)
            {
                Eegeo_ASSERT(!Contains(interiorMaterialDto.materialName));
                
                m_materialKeyToData.insert(std::make_pair(interiorMaterialDto.materialName, interiorMaterialDto));
            }
            
            bool InteriorsCustomMaterialDtoRepository::Contains(const std::string& materialKey) const
            {
                return m_materialKeyToData.find(materialKey) != m_materialKeyToData.end();
            }
            
            InteriorsCustomMaterialDto InteriorsCustomMaterialDtoRepository::Get(const std::string& materialKey) const
            {
                return m_materialKeyToData.at(materialKey);
            }

        }
    }
}