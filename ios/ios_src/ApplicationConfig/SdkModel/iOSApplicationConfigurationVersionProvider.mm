// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSApplicationConfigurationVersionProvider.h"
#include "Types.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {

            iOSApplicationConfigurationVersionProvider::iOSApplicationConfigurationVersionProvider()
            {
                NSDictionary *infoDictionary = [[NSBundle mainBundle]infoDictionary];
                Eegeo_ASSERT(infoDictionary != NULL, "could not find plist info");
                NSString *appProductVersion = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
                if (appProductVersion != NULL)
                {
                    m_productVersion = std::string([appProductVersion UTF8String]);
                }
                else
                {
                    m_productVersion = "0.0.1-alpha";
                }

                NSString *appBuildNumber = [infoDictionary objectForKey:@"CFBundleVersion"];
                if (appProductVersion != NULL)
                {
                    m_buildNumber = std::string([appBuildNumber UTF8String]);
                }
                else
                {
                    m_buildNumber = "devbuild";
                }
            }
            
            std::string iOSApplicationConfigurationVersionProvider::GetProductVersionString() const
            {
                return m_productVersion;
            }
            
            std::string iOSApplicationConfigurationVersionProvider::GetBuildNumberString() const
            {
                return m_buildNumber;
            }
        }
    }
}