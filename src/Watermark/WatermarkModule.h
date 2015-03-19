// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Watermark.h"
#include "IWatermarkModule.h"
#include "IIdentity.h"
#include "WatermarkViewModel.h"

namespace ExampleApp
{
    namespace Watermark
    {
        class WatermarkModule : public IWatermarkModule, private Eegeo::NonCopyable
        {
        private:
            View::WatermarkViewModel* m_pViewModel;
            
        public:
            WatermarkModule(Eegeo::Helpers::IIdentityProvider& identityProvider);
            
            ~WatermarkModule();
            
            View::IWatermarkViewModel& GetWatermarkViewModel() const;
            
            ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
        };
    }
}
