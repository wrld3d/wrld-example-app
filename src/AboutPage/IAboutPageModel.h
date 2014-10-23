// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace AboutPage
    {
        class IAboutPageModel
        {
        public:
            virtual ~IAboutPageModel() { }
            
            virtual const std::string& GetPlatformVersion() const = 0;
            
            virtual const std::string& GetPlatformHash() const = 0;
            
            virtual const std::string& GetAboutText() const = 0;
        };
    }
}
