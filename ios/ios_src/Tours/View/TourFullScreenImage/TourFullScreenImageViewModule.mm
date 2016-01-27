// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourFullScreenImageViewModule.h"
#include "TourFullScreenImageViewController.h"
#include "TourFullScreenImageView.h"
#include "TourFullScreenImageViewInterop.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                TourFullScreenImageViewModule::TourFullScreenImageViewModule(ITourFullScreenImageViewModel& viewModel,
                                                                             const Eegeo::Rendering::ScreenProperties& screenProperties)
                {
                    m_pView = [[TourFullScreenImageView alloc] initWithParams
                               :screenProperties.GetScreenWidth()
                               :screenProperties.GetScreenHeight()
                               :screenProperties.GetPixelScale()];
                    
                    m_pViewController = Eegeo_NEW(TourFullScreenImageViewController)(viewModel,
                                                                                     *[m_pView getInterop]);
                }
                
                TourFullScreenImageViewModule::~TourFullScreenImageViewModule()
                {
                    Eegeo_DELETE m_pViewController;
                    
                    [m_pView release];
                }
                
                TourFullScreenImageView& TourFullScreenImageViewModule::GetTourFullScreenImageView() const
                {
                    return *m_pView;
                }
            }
        }
    }
}
