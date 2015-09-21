// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ITourWebViewModule.h"
#include "Types.h"
#include "TourWebView.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourWeb
            {
                class TourWebViewModule : public ITourWebViewModule, private Eegeo::NonCopyable
                {
                public:
                    
                    TourWebViewModule(const Eegeo::Rendering::ScreenProperties& screenProperties);
                    ~TourWebViewModule();
                    
                    TourWebView& GetTourWebView() const;
                    
                private:
                    
                    TourWebView* m_pView;
                };
            }
        }
    }
}