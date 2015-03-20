// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "IApplicationConfigurationReader.h"
#include "Types.h"
#include "IFileIO.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationReader : public IApplicationConfigurationReader, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::IFileIO& m_fileIO;
                
            public:
                ApplicationConfigurationReader(Eegeo::Helpers::IFileIO& fileIO);
                
                std::string ReadApplicationConfiguration(const std::string& pathToConfiguration);
            };
        }
    }
}
