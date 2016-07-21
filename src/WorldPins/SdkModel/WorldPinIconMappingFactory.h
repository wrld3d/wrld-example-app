// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "IWorldPinIconMappingFactory.h"
#include "Types.h"
#include "Helpers.h"
#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinIconMappingFactory : public IWorldPinIconMappingFactory, private Eegeo::NonCopyable
            {
            public:
                WorldPinIconMappingFactory(Eegeo::Helpers::IFileIO& fileIO, const std::string& sheetManifestFile);
                virtual ~WorldPinIconMappingFactory() { }
                
                virtual IWorldPinIconMapping* Create() const;
                
            private:
                Eegeo::Helpers::IFileIO& m_fileIO;
                const std::string m_sheetManifestFile;
                
            };
        }
    }
}