// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationConfirmationViewModel.h"
#include "ISearchResultMenuModel.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationConfirmationViewModel::PoiCreationConfirmationViewModel(Eegeo::Helpers::TIdentity identity,
                                                                           bool initiallyOnScreen)
        : m_screenControl(initiallyOnScreen, identity)
        {
            
        }
        
        ScreenControlViewModel::IScreenControlViewModel& PoiCreationConfirmationViewModel::GetScreenControlViewModel()
        {
            return m_screenControl;
        }
        
        Eegeo::Helpers::TIdentity PoiCreationConfirmationViewModel::GetIdentity() const
        {
            return m_screenControl.GetIdentity();
        }
        
        void PoiCreationConfirmationViewModel::AddToScreen()
        {
            m_screenControl.AddToScreen();
        }
        
        void PoiCreationConfirmationViewModel::RemoveFromScreen()
        {
            m_screenControl.RemoveFromScreen();
        }
        
        void PoiCreationConfirmationViewModel::UpdateOnScreenState(float onScreenState)
        {
            m_screenControl.UpdateOnScreenState(onScreenState);
        }
        
        void PoiCreationConfirmationViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback)
        {
            m_screenControl.InsertOnScreenStateChangedCallback(callback);
        }
        
        void PoiCreationConfirmationViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback)
        {
            m_screenControl.RemoveOnScreenStateChangedCallback(callback);
        }
        
        bool PoiCreationConfirmationViewModel::IsFullyOffScreen() const
        {
            return m_screenControl.IsFullyOffScreen();
        }
        
        bool PoiCreationConfirmationViewModel::IsFullyOnScreen() const
        {
            return m_screenControl.IsFullyOnScreen();
        }
        
        float PoiCreationConfirmationViewModel::OnScreenState() const
        {
            return m_screenControl.OnScreenState();
        }
    }
}
