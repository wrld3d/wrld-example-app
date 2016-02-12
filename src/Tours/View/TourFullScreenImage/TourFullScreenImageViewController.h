// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Tours.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                class TourFullScreenImageViewController : private Eegeo::NonCopyable
                {
                public:
                    
                    TourFullScreenImageViewController(ITourFullScreenImageViewModel& viewModel,
                                                      ITourFullScreenImageView& view);
                    
                    ~TourFullScreenImageViewController();
                    
                private:
                    
                    void OnCeremonyBegin();
                    void OnCeremonyEnd();
                    
                    ITourFullScreenImageViewModel& m_viewModel;
                    ITourFullScreenImageView& m_view;
                    
                    Eegeo::Helpers::TCallback0<TourFullScreenImageViewController> m_beginFullScreenImageCeremonyCallback;
                    Eegeo::Helpers::TCallback0<TourFullScreenImageViewController> m_endFullScreenImageCeremonyCallback;
                };
            }
        }
    }
}
