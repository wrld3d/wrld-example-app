// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class TourStateModel
            {
            public:
                TourStateModel(const std::string& headline,
                               const std::string& description,
                               const std::string& imagePath,
                               const std::string& icon);
                
                const std::string& Headline() const;
                
                const std::string& Description() const;
                
                const std::string& ImagePath() const;
                
                const std::string& Icon() const;
                
            private:
                std::string m_headline;
                std::string m_description;
                std::string m_imagePath;
                std::string m_icon;
            };
        }
    }
}
