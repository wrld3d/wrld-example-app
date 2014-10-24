// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationButtonViewModel.h"
#include "ISearchResultMenuModel.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationButtonViewModel::PoiCreationButtonViewModel(Eegeo::Helpers::TIdentity identity,
                                                               bool initiallyOnScreen)
        : m_screenControl(initiallyOnScreen, identity)
        , m_shouldOffsetViewButton(false)
        {
            
        }
        
        ScreenControlViewModel::IScreenControlViewModel& PoiCreationButtonViewModel::GetScreenControlViewModel()
        {
            return m_screenControl;
        }
        
        Eegeo::Helpers::TIdentity PoiCreationButtonViewModel::GetIdentity() const
        {
            return m_screenControl.GetIdentity();
        }
        
        void PoiCreationButtonViewModel::AddToScreen()
        {
            m_screenControl.AddToScreen();
        }
        
        void PoiCreationButtonViewModel::RemoveFromScreen()
        {
            m_screenControl.RemoveFromScreen();
        }
        
        void PoiCreationButtonViewModel::UpdateOnScreenState(float onScreenState)
        {
            m_screenControl.UpdateOnScreenState(onScreenState);
        }
        
        void PoiCreationButtonViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback)
        {
            m_screenControl.InsertOnScreenStateChangedCallback(callback);
        }
        
        void PoiCreationButtonViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback)
        {
            m_screenControl.RemoveOnScreenStateChangedCallback(callback);
        }
        
        bool PoiCreationButtonViewModel::IsFullyOffScreen() const
        {
            return m_screenControl.IsFullyOffScreen();
        }
        
        bool PoiCreationButtonViewModel::IsFullyOnScreen() const
        {
            return m_screenControl.IsFullyOnScreen();
        }
        
        float PoiCreationButtonViewModel::OnScreenState() const
        {
            return m_screenControl.OnScreenState();
        }
        
        bool PoiCreationButtonViewModel::ShouldOffsetViewButton() const
        {
            return m_shouldOffsetViewButton;
        }
        
        void PoiCreationButtonViewModel::SetShouldOffsetViewButton(bool shouldOffset)
        {
            m_shouldOffsetViewButton = shouldOffset;
        }
    }
}
