// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinOnMapView.h"
#include "TourHovercardView.h"
#include "CallbackCollection.h"
#include "ICallback.h"
#include "ITourHovercardView.h"
#include "TourModel.h"
#include <string>

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourHovercard
            {
                class TourHovercardViewInterop : public WorldPins::View::IWorldPinOnMapView, public Tours::View::TourHovercard::ITourHovercardView
                {
                public:
                    
                    TourHovercardViewInterop(TourHovercardView* pView)
                    : m_pView(pView)
                    {
                    }
                    
                    void SetCurrentTour(const SdkModel::TourModel& tourModel);
                    
                    void Open(const std::string& title,
                              const std::string& subtitle,
                              const std::string& ratingsImage,
                              const int reviewCount,
                              float modality);
                    void Close();
                    void UpdateScreenLocation(float posX, float posY);
                    void UpdateScreenState(float screenState);
                    
                    void OnSelected();
                    void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                                        
                private:
                    
                    TourHovercardView* m_pView;
                    Eegeo::Helpers::CallbackCollection0 m_selectedCallbacks;
                };
            }
        }
    }
}
