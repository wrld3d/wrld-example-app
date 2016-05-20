// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationModule.h"
#include "ApplicationConfigurationService.h"
#include "ApplicationConfigurationBuilder.h"
#include "ApplicationConfigurationJsonParser.h"
#include "ApplicationConfigurationReader.h"
#include "ApplicationConfigurationXorCipher.h"

#include "base64.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationConfigurationModule::ApplicationConfigurationModule(Eegeo::Helpers::IFileIO& fileIO,
                                                                           const std::string& productVersion,
                                                                           const std::string& buildNumber,
                                                                           const std::string& configKeyBase64)
            {
                const std::string& configKey = base64_decode(configKeyBase64);
                m_pApplicationConfigurationEncryption = Eegeo_NEW(ApplicationConfigurationXorCipher)(configKey);
                m_pApplicationConfigurationBuilder = Eegeo_NEW(ApplicationConfigurationBuilder)(*m_pApplicationConfigurationEncryption, configKey);
                m_pApplicationConfigurationReader = Eegeo_NEW(ApplicationConfigurationReader)(fileIO);
                m_pApplicationConfigurationParser = Eegeo_NEW(ApplicationConfigurationJsonParser)(*m_pApplicationConfigurationBuilder);
                m_pApplicationConfigurationService = Eegeo_NEW(ApplicationConfigurationService)(*m_pApplicationConfigurationParser,
                                                                                                *m_pApplicationConfigurationReader,
                                                                                                productVersion,
                                                                                                buildNumber);
            }
            
            ApplicationConfigurationModule::~ApplicationConfigurationModule()
            {
                Eegeo_DELETE m_pApplicationConfigurationService;
                Eegeo_DELETE m_pApplicationConfigurationParser;
                Eegeo_DELETE m_pApplicationConfigurationReader;
                Eegeo_DELETE m_pApplicationConfigurationBuilder;
                Eegeo_DELETE m_pApplicationConfigurationEncryption;
            }
            
            IApplicationConfigurationService& ApplicationConfigurationModule::GetApplicationConfigurationService()
            {
                return *m_pApplicationConfigurationService;
            }
        }
    }
}
