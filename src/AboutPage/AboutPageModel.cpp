// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageModel.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageModel::AboutPageModel(const std::string& platformVersion,
                                       const std::string& platformHash,
                                       const std::string& aboutText)
        : m_platformVersion(platformVersion)
        , m_platformHash(platformHash)
        , m_aboutText(aboutText)
        {
            
        }
        
        AboutPageModel::~AboutPageModel()
        {
            
        }
        
        const std::string& AboutPageModel::GetPlatformVersion() const
        {
            return m_platformVersion;
        }
        
        const std::string& AboutPageModel::GetPlatformHash() const
        {
            return m_platformHash;
        }
        
        const std::string& AboutPageModel::GetAboutText() const
        {
            return m_aboutText;
        }
    }
}
