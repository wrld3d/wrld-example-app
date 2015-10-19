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
                InteriorsCustomMaterialFactory(const IInteriorsCustomMaterialDtoRepository& materialDtoRepository,
                                               Eegeo::Resources::Interiors::IInteriorsMaterialFactory& untexturedMaterialFactory,
                                               Eegeo::Resources::Interiors::IInteriorsMaterialFactory& diffuseTexturedMaterialFactory,
                                               Eegeo::Resources::Interiors::IInteriorsMaterialFactory& diffuseSpecularMaterialFactory,
                                               Eegeo::Resources::Interiors::IInteriorsMaterialFactory& cubeMappedMaterialFactory);

                Eegeo::Rendering::Materials::IMaterial* TryCreate(const Eegeo::Resources::Interiors::InteriorMaterialData& interiorMaterialData);
            private:

                const IInteriorsCustomMaterialDtoRepository& m_materialDtoRepository;
                Eegeo::Resources::Interiors::IInteriorsMaterialFactory& m_untexturedMaterialFactory;
                Eegeo::Resources::Interiors::IInteriorsMaterialFactory& m_diffuseTexturedMaterialFactory;
                Eegeo::Resources::Interiors::IInteriorsMaterialFactory& m_diffuseSpecularMaterialFactory;
                Eegeo::Resources::Interiors::IInteriorsMaterialFactory& m_cubeMappedMaterialFactory;
                
            };
        }
    }
}