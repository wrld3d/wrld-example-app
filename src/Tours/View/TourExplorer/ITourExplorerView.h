// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"
#include "Tours.h"
#include <string>

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class ITourExplorerView : public ScreenControl::View::IScreenControlView
                {
                public:
                    
                    virtual ~ITourExplorerView() { }
                    
                    virtual void SetCurrentTour(const SdkModel::TourModel& tourModel) = 0;
                    virtual const SdkModel::TourModel& GetCurrentTour() = 0;
                    virtual void SetInitialCard(const int initialCard) = 0;
                    
                    virtual void OnDismissed() = 0;
                    virtual void OnStateSelected(int activeStateIndex) = 0;
                    virtual void OnChangeTourRequested(const std::string& name) = 0;
                    
                    virtual void OnCurrentTourCardTapped() = 0;
                    
                    virtual void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void InsertStateChangedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                    virtual void RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<int>& callback) = 0;
                    virtual void InsertChangeTourRequestCallback(Eegeo::Helpers::ICallback1<std::string>& callback) = 0;
                    virtual void RemoveChangeTourRequestCallback(Eegeo::Helpers::ICallback1<std::string>& callback) = 0;
                    
                    virtual void InsertCurrentTourCardTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                    virtual void RemoveCurrentTourCardTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                };
            }
        }
    }
}
