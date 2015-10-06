// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IIdentity.h"
#include "ITourExplorerViewModel.h"
#include "Tours.h"
#include "CallbackCollection.h"
#include "TourExplorerScreenControl.h"
#include "TourModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class TourExplorerViewModel : public ITourExplorerViewModel, private Eegeo::NonCopyable
                {
                    SdkModel::TourModel m_tourModel;
                    int m_initialCard;
                    
                    
                public:
                    TourExplorerViewModel(Eegeo::Helpers::TIdentity identity,
                                          bool isInitiallyOnScreen);
                    
                    void SetCurrentTour(const SdkModel::TourModel& tourModel);
                    
                    const SdkModel::TourModel& GetCurrentTour() const;
                    
                    void SetInitialCard(const int card);
                    
                    const int GetInitialCard() const;
                    
                    Eegeo::Helpers::TIdentity GetIdentity() const;
                    
                    void AddToScreen();
                    
                    void RemoveFromScreen();
                    
                    void UpdateOnScreenState(float onScreenState);
                    
                    void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback);
                    
                    void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback);
                    
                    bool IsFullyOffScreen() const;
                    
                    bool IsFullyOnScreen() const;
                    
                    float OnScreenState() const;
                    
                    bool IsAddedToScreen() const;
                    
                    ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel();
                    
                    bool ShouldOffsetViewButton() const;
                    
                    void SetShouldOffsetViewButton(bool shouldOffset);
                    
                private:
                    TourExplorerScreenControl m_screenControl;
                    bool m_shouldOffsetViewButton;
                };
            }
        }
    }
}
