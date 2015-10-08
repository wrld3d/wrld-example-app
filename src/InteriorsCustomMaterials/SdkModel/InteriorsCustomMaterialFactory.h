// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once



#include "Interiors.h"
#include "IInteriorsMaterialFactory.h"
#include "Types.h"
#include "InteriorsCustomMaterialDto.h"

#include <string>
#include <map>

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
            class InteriorsCustomMaterialFactory : public Eegeo::Resources::Interiors::IInteriorsMaterialFactory, private Eegeo::NonCopyable
            {
            public:
                typedef std::map<std::string, std::string> TMaterialKeyToFactoryType;
                
                InteriorsCustomMaterialFactory(const TMaterialKeyToFactoryType& materialKeyToFactoryType,
                                               Eegeo::Resources::Interiors::IInteriorsMaterialFactory& untexturedMaterialFactory,
                                               Eegeo::Resources::Interiors::IInteriorsMaterialFactory& diffuseTexturedMaterialFactory);

                Eegeo::Rendering::Materials::IMaterial* TryCreate(const Eegeo::Resources::Interiors::InteriorMaterialData& interiorMaterialData);
            private:
                
                Eegeo::Resources::Interiors::IInteriorsMaterialFactory& m_untexturedMaterialFactory;
                Eegeo::Resources::Interiors::IInteriorsMaterialFactory& m_diffuseTexturedMaterialFactory;
                TMaterialKeyToFactoryType m_materialKeyToFactoryType;
            };
        }
    }
}