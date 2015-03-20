// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationReader.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationConfigurationReader::ApplicationConfigurationReader(Eegeo::Helpers::IFileIO& fileIO)
            : m_fileIO(fileIO)
            {
                
            }
            
            std::string ApplicationConfigurationReader::ReadApplicationConfiguration(const std::string& pathToConfiguration)
            {
                size_t size;
                std::fstream stream;
                std::string result;
                
                if(m_fileIO.OpenFile(stream, size, pathToConfiguration))
                {
                    result = std::string((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));
                }
                
                return result;
            }
        }
    }
}
