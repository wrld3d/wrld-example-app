// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "Types.h"
#include "ApplicationConfigurationChangedHolder.h"
#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationConfigurationChangedHolder::ApplicationConfigurationChangedHolder()
            : m_hasConfigurationChanged(false)
            , m_pNewApplicationConfiguration(NULL)
            {
                
            }
            
            ApplicationConfigurationChangedHolder::~ApplicationConfigurationChangedHolder()
            {
                Eegeo_DELETE m_pNewApplicationConfiguration;
                m_pNewApplicationConfiguration = NULL;
            }
            
            void ApplicationConfigurationChangedHolder::SetNewApplicationConfiguration(const ApplicationConfiguration& applicationConfiguration)
            {
                m_pNewApplicationConfiguration = ApplicationConfiguration::Clone(applicationConfiguration);
                m_hasConfigurationChanged = true;
            }
            
            bool ApplicationConfigurationChangedHolder::HasConfigurationChanged() const
            {
                return m_hasConfigurationChanged;
            }
            
            const ApplicationConfiguration& ApplicationConfigurationChangedHolder::GetNewApplicationConfiguration() const
            {
                return *m_pNewApplicationConfiguration;
            }
            
            void ApplicationConfigurationChangedHolder::Clear()
            {
                m_hasConfigurationChanged = false;
                Eegeo_DELETE m_pNewApplicationConfiguration;
                m_pNewApplicationConfiguration = NULL;
            }
        }
    }
}
