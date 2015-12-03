// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"
#include "Tours.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class ITourExplorerViewModel : public ScreenControl::View::IScreenControlViewModel
                {
                public:
                    virtual ~ITourExplorerViewModel() { }
                    
                    virtual void SetCurrentTour(const SdkModel::TourModel& tourModel) = 0;
                    
                    virtual void SetInitialCard(const int card) = 0;
                    
                    virtual void SetShowBackButton(bool showBackButton) = 0;
                    
                    virtual const SdkModel::TourModel& GetCurrentTour() const = 0;
                    
                    virtual const int GetInitialCard() const = 0;
                    
                    virtual bool GetShowBackButton() const = 0;
                };
            }
        }
    }
}
