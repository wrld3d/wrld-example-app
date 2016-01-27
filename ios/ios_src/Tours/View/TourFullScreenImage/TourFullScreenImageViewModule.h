// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Tours.h"
#include "ITourFullScreenImageViewModule.h"
#include "TourFullScreenImageViewIncludes.h"
#include "ScreenProperties.h"
#include "TourFullScreenImageViewController.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                class TourFullScreenImageViewModule : public ITourFullScreenImageViewModule, private Eegeo::NonCopyable
                {
                private:
                    TourFullScreenImageView* m_pView;
                    TourFullScreenImageViewController* m_pViewController;
                    
                public:
                    TourFullScreenImageViewModule(ITourFullScreenImageViewModel& viewModel,
                                                  const Eegeo::Rendering::ScreenProperties& screenProperties);
                    
                    ~TourFullScreenImageViewModule();
                    
                    TourFullScreenImageView& GetTourFullScreenImageView() const;
                };
            }
        }
    }
}
