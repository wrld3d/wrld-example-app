// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsCustomMaterialFactory.h"
#include "InteriorMaterialData.h"

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {

            InteriorsCustomMaterialFactory::InteriorsCustomMaterialFactory(const TMaterialKeyToFactoryType& materialKeyToFactoryType,
                                                                           Eegeo::Resources::Interiors::IInteriorsMaterialFactory& untexturedMaterialFactory,
                                                                           Eegeo::Resources::Interiors::IInteriorsMaterialFactory& diffuseTexturedMaterialFactory)
            : m_untexturedMaterialFactory(untexturedMaterialFactory)
            , m_diffuseTexturedMaterialFactory(diffuseTexturedMaterialFactory)
            , m_materialKeyToFactoryType(materialKeyToFactoryType)
            {
                
            }

            Eegeo::Rendering::Materials::IMaterial* InteriorsCustomMaterialFactory::TryCreate(const Eegeo::Resources::Interiors::InteriorMaterialData& interiorMaterialData)
            {
                const std::string& key = interiorMaterialData.MaterialName();
                
                if (m_materialKeyToFactoryType.find(key) == m_materialKeyToFactoryType.end())
                {
                    return NULL;
                }
                
                const std::string& factoryType = m_materialKeyToFactoryType.at(key);
                
                if (factoryType == "InteriorsDiffuseTexturedMaterial")
                {
                    return m_diffuseTexturedMaterialFactory.TryCreate(interiorMaterialData);
                }
                else if (factoryType == "InteriorsDiffuseUntexturedMaterial")
                {
                    return m_untexturedMaterialFactory.TryCreate(interiorMaterialData);
                }
                
                return NULL;
            }
        }
    }
}