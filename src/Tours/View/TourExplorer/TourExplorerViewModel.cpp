// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourExplorerViewModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                TourExplorerViewModel::TourExplorerViewModel(Eegeo::Helpers::TIdentity identity,
                                                             bool initiallyOnScreen)
                : m_screenControl(initiallyOnScreen, identity)
                , m_shouldOffsetViewButton(false)
                , m_tourModel(SdkModel::TourModel::Empty())
                , m_initialCard(-1)
                {
                    
                }
                
                void TourExplorerViewModel::SetCurrentTour(const SdkModel::TourModel& tourModel)
                {
                    m_tourModel = tourModel;
                }
                
                void TourExplorerViewModel::SetInitialCard(const int card)
                {
                    m_initialCard = card;
                }
                
                const SdkModel::TourModel& TourExplorerViewModel::GetCurrentTour() const
                {
                    return m_tourModel;
                }
                
                const int TourExplorerViewModel::GetInitialCard() const
                {
                    return m_initialCard;
                }
                
                ScreenControl::View::IScreenControlViewModel& TourExplorerViewModel::GetScreenControlViewModel()
                {
                    return m_screenControl;
                }
                
                Eegeo::Helpers::TIdentity TourExplorerViewModel::GetIdentity() const
                {
                    return m_screenControl.GetIdentity();
                }
                
                void TourExplorerViewModel::AddToScreen()
                {
                    m_screenControl.AddToScreen();
                }
                
                void TourExplorerViewModel::RemoveFromScreen()
                {
                    m_screenControl.RemoveFromScreen();
                }
                
                void TourExplorerViewModel::UpdateOnScreenState(float onScreenState)
                {
                    m_screenControl.UpdateOnScreenState(onScreenState);
                }
                
                void TourExplorerViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
                {
                    m_screenControl.InsertOnScreenStateChangedCallback(callback);
                }
                
                void TourExplorerViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
                {
                    m_screenControl.RemoveOnScreenStateChangedCallback(callback);
                }
                
                bool TourExplorerViewModel::IsFullyOffScreen() const
                {
                    return m_screenControl.IsFullyOffScreen();
                }
                
                bool TourExplorerViewModel::IsFullyOnScreen() const
                {
                    return m_screenControl.IsFullyOnScreen();
                }
                
                float TourExplorerViewModel::OnScreenState() const
                {
                    return m_screenControl.OnScreenState();
                }
                
                bool TourExplorerViewModel::IsAddedToScreen() const
                {
                    return m_screenControl.IsAddedToScreen();
                }
                
                bool TourExplorerViewModel::ShouldOffsetViewButton() const
                {
                    return m_shouldOffsetViewButton;
                }
                
                void TourExplorerViewModel::SetShouldOffsetViewButton(bool shouldOffset)
                {
                    m_shouldOffsetViewButton = shouldOffset;
                }
            }
        }
    }
}
