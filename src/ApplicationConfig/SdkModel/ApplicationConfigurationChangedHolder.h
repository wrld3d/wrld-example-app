// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationChangedHolder
            {
            public:
                ApplicationConfigurationChangedHolder();
                ~ApplicationConfigurationChangedHolder();
                void SetNewApplicationConfiguration(const ApplicationConfiguration& applicationConfiguration);
                bool HasConfigurationChanged() const;
                const ApplicationConfiguration& GetNewApplicationConfiguration() const;
                void Clear();
                
            private:
                bool m_hasConfigurationChanged;
                ApplicationConfiguration* m_pNewApplicationConfiguration;
            };
        }
    }
}
