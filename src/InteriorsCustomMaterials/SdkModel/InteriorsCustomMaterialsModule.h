// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "InteriorsCustomMaterials.h"
#include "IInteriorsCustomMaterialsModule.h"
#include "Modules.h"
#include "Helpers.h"

#include "Types.h"

#include <vector>

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
            
            class InteriorsCustomMaterialsModule : public IInteriorsCustomMaterialsModule, private Eegeo::NonCopyable
            {
            public:
                InteriorsCustomMaterialsModule(Eegeo::Modules::Map::Layers::InteriorsStreamingModule& interiorsStreamingModule,
                                               Eegeo::Helpers::IFileIO& fileIO);
                
                ~InteriorsCustomMaterialsModule();
                
            private:
                Eegeo::Resources::Interiors::IInteriorsMaterialFactory* m_pInteriorsCustomMaterialFactory;
                IInteriorsCustomMaterialDtoRepository* m_pInteriorsCustomMaterialDtoRepository;

            };
            
            
        }
    }
}