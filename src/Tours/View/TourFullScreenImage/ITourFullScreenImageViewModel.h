// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "ICallback.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                class ITourFullScreenImageViewModel
                {
                public:
                    virtual ~ITourFullScreenImageViewModel() { }
                    
                    virtual const std::string& GetAsset() const = 0;
                    
                    virtual const std::string& GetMessage() const = 0;
                    
                    virtual void BeginFullScreenImageCeremony(const std::string& image,
                                                              const std::string& message) = 0;
                    
                    virtual void EndFullScreenImageCeremony() = 0;
                    
                    virtual void InsertBeginCeremonyCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    
                    virtual void RemoveBeginCeremonyCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    
                    virtual void InsertEndCeremonyCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    
                    virtual void RemoveEndCeremonyCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    
                };
            }
        }
    }
}
