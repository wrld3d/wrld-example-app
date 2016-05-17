// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidApplicationConfigurationVersionProvider.h"
#include "Types.h"
#include <sstream>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {

        	AndroidApplicationConfigurationVersionProvider::AndroidApplicationConfigurationVersionProvider(const AndroidNativeState& nativeState)
            {
        		// these are as as specified in AndroidManifest.xml
                // m_buildNumber <- android:versionCode
        		// m_productVersion <- android:versionName
        		m_productVersion = nativeState.versionName;
        		std::stringstream s;
        		s << nativeState.versionCode;
                m_buildNumber = s.str();
            }
            
            std::string AndroidApplicationConfigurationVersionProvider::GetProductVersionString() const
            {
                return m_productVersion;
            }
            
            std::string AndroidApplicationConfigurationVersionProvider::GetBuildNumberString() const
            {
                return m_buildNumber;
            }
        }
    }
}
