// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationModule.h"
#include "ApplicationConfigurationService.h"
#include "ApplicationConfigurationBuilder.h"
#include "ApplicationConfigurationJsonParser.h"
#include "ApplicationConfigurationReader.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationConfigurationModule::ApplicationConfigurationModule(Eegeo::Helpers::IFileIO& fileIO,
                                                                           const std::string& productVersion,
                                                                           const std::string& buildNumber)
            {
                m_pApplicationConfigurationBuilder = Eegeo_NEW(ApplicationConfigurationBuilder);
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
            }
            
            IApplicationConfigurationService& ApplicationConfigurationModule::GetApplicationConfigurationService()
            {
                return *m_pApplicationConfigurationService;
            }
        }
    }
}
