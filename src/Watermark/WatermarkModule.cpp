// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkModule.h"
#include "WatermarkViewModel.h"

namespace ExampleApp
{
    namespace Watermark
    {
        WatermarkModule::WatermarkModule(Eegeo::Helpers::IIdentityProvider& identityProvider)
        {
            m_pViewModel = Eegeo_NEW(View::WatermarkViewModel)(identityProvider.GetNextIdentity(), false);
        }
        
        WatermarkModule::~WatermarkModule()
        {
            Eegeo_DELETE m_pViewModel;
        }
        
        View::IWatermarkViewModel& WatermarkModule::GetWatermarkViewModel() const
        {
            return *m_pViewModel;
        }
        
        ScreenControl::View::IScreenControlViewModel& WatermarkModule::GetScreenControlViewModel() const
        {
            return m_pViewModel->GetScreenControlViewModel();
        }
    }
}
