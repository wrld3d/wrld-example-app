// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Tours
    {
        class TourFullScreenImageCeremonyBeganMessage
        {
            std::string m_image;
            std::string m_message;
            
        public:
            TourFullScreenImageCeremonyBeganMessage(const std::string& image,
                                                    const std::string& message);
            
            const std::string& GetImage() const;
            
            const std::string& GetMessage() const;
        };
    }
}
