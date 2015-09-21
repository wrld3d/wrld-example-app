// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourWebViewModule.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourWeb
            {
                TourWebViewModule::TourWebViewModule(const Eegeo::Rendering::ScreenProperties& screenProperties)
                {
                    m_pView = [[TourWebView alloc] initWithParams
                                : screenProperties.GetScreenWidth()
                                : screenProperties.GetScreenHeight()
                                : screenProperties.GetPixelScale()];
                }
                
                TourWebViewModule::~TourWebViewModule()
                {
                    [m_pView release];
                }
                
                TourWebView& TourWebViewModule::GetTourWebView() const
                {
                    return *m_pView;
                }
            }
        }
    }
}