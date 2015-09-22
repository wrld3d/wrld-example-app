// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourFullScreenImageCeremonyBeganMessage.h"

namespace ExampleApp
{
    namespace Tours
    {
        TourFullScreenImageCeremonyBeganMessage::TourFullScreenImageCeremonyBeganMessage(const std::string& image,
                                                                                         const std::string& message)
        : m_image(image)
        , m_message(message)
        {
            
        }
        
        const std::string& TourFullScreenImageCeremonyBeganMessage::GetImage() const
        {
            return m_image;
        }
        
        const std::string& TourFullScreenImageCeremonyBeganMessage::GetMessage() const
        {
            return m_message;
        }
    }
}
