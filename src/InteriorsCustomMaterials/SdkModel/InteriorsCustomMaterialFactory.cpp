// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsCustomMaterialFactory.h"
#include "InteriorMaterialData.h"
#include "IInteriorsCustomMaterialDtoRepository.h"
#include "InteriorsCustomMaterialKeys.h"

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {

            InteriorsCustomMaterialFactory::InteriorsCustomMaterialFactory(const IInteriorsCustomMaterialDtoRepository& materialDtoRepository,
                                                                           Eegeo::Resources::Interiors::IInteriorsMaterialFactory& untexturedMaterialFactory,
                                                                           Eegeo::Resources::Interiors::IInteriorsMaterialFactory& diffuseTexturedMaterialFactory,
                                                                           Eegeo::Resources::Interiors::IInteriorsMaterialFactory& diffuseSpecularMaterialFactory,
                                                                           Eegeo::Resources::Interiors::IInteriorsMaterialFactory& cubeMappedMaterialFactory,
                                                                           Eegeo::Resources::Interiors::IInteriorsMaterialFactory& chromeMaterialFactory,
                                                                           Eegeo::Resources::Interiors::IInteriorsMaterialFactory& reflectionMaterialFactory)
            : m_materialDtoRepository(materialDtoRepository)
            , m_untexturedMaterialFactory(untexturedMaterialFactory)
            , m_diffuseTexturedMaterialFactory(diffuseTexturedMaterialFactory)
            , m_diffuseSpecularMaterialFactory(diffuseSpecularMaterialFactory)
            , m_cubeMappedMaterialFactory(cubeMappedMaterialFactory)
            , m_chromeMaterialFactory(chromeMaterialFactory)
            , m_reflectionMaterialFactory(reflectionMaterialFactory)
            {
                
            }

            Eegeo::Rendering::Materials::IMaterial* InteriorsCustomMaterialFactory::TryCreate(const Eegeo::Resources::Interiors::InteriorMaterialData& interiorMaterialData)
            {
                const std::string& key = interiorMaterialData.MaterialName();
                
                if (!m_materialDtoRepository.Contains(key))
                {
                    return NULL;
                }
                
                const InteriorsCustomMaterialDto& materialDto = m_materialDtoRepository.Get(key);
                
                const Eegeo::Resources::Interiors::InteriorMaterialData& customInteriorMaterialData =
                    Eegeo::Resources::Interiors::InteriorMaterialData::Make(materialDto.materialName,
                                                                            materialDto.keyValueStrings,
                                                                            materialDto.keyValueColors,
                                                                            materialDto.keyValueScalars,
                                                                            materialDto.keyValueBooleans);
                
                const std::string& materialFactoryType = customInteriorMaterialData.GetStringOrDefault(InteriorsCustomMaterialKeys::MaterialType, InteriorsCustomMaterialKeys::InteriorsDiffuseUntexturedMaterial);

                

                if (materialFactoryType == InteriorsCustomMaterialKeys::InteriorsDiffuseUntexturedMaterial)
                {
                    return m_untexturedMaterialFactory.TryCreate(customInteriorMaterialData);
                }
                else if (materialFactoryType == InteriorsCustomMaterialKeys::InteriorsDiffuseTexturedMaterial)
                {
                    return m_diffuseTexturedMaterialFactory.TryCreate(customInteriorMaterialData);
                }
                else if (materialFactoryType == InteriorsCustomMaterialKeys::InteriorsSpecularMaterial)
                {
                    return m_diffuseSpecularMaterialFactory.TryCreate(customInteriorMaterialData);
                }
                else if (materialFactoryType == InteriorsCustomMaterialKeys::InteriorsCubeMappedMaterial)
                {
                    return m_cubeMappedMaterialFactory.TryCreate(customInteriorMaterialData);
                }
                else if (materialFactoryType == InteriorsCustomMaterialKeys::InteriorsChromeMaterial)
                {
                    return m_chromeMaterialFactory.TryCreate(customInteriorMaterialData);
                }
                else if (materialFactoryType == InteriorsCustomMaterialKeys::InteriorsReflectionMaterial)
                {
                    return m_reflectionMaterialFactory.TryCreate(customInteriorMaterialData);
                }
                
                return NULL;
            }

        }
    }
}