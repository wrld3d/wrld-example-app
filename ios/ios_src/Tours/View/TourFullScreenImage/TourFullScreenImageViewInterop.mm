// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourFullScreenImageViewInterop.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                TourFullScreenImageViewInterop::TourFullScreenImageViewInterop(TourFullScreenImageView* pView)
                : m_pView(pView)
                {
                }
                
                void TourFullScreenImageViewInterop::BeginCeremony(const std::string& asset, const std::string& message)
                {
                    [m_pView beginCeremony :asset :message];
                }
                
                void TourFullScreenImageViewInterop::EndCeremony()
                {
                    [m_pView endCeremony];
                }
            }
        }
    }
}
