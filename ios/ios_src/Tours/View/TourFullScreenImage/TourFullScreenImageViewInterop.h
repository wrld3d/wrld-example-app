// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ITourFullScreenImageView.h"
#include "TourFullScreenImageView.h"
#include "Types.h"
#include <string>

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                class TourFullScreenImageViewInterop : public ITourFullScreenImageView, private Eegeo::NonCopyable
                {
                public:
                    TourFullScreenImageViewInterop(TourFullScreenImageView* pView);
                    
                    void BeginCeremony(const std::string& asset, const std::string& message);
                    
                    void EndCeremony();
                    
                private:
                    
                    TourFullScreenImageView* m_pView;
                };
            }
        }
    }
}
