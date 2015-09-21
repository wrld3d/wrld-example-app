// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourHovercardViewInterop.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourHovercard
            {
                void TourHovercardViewInterop::OnSelected()
                {
                    m_selectedCallbacks.ExecuteCallbacks();
                }
                
                void TourHovercardViewInterop::InsertSelectedCallback(Eegeo::Helpers::ICallback0 &callback)
                {
                    m_selectedCallbacks.AddCallback(callback);
                }
                
                void TourHovercardViewInterop::RemoveSelectedCallback(Eegeo::Helpers::ICallback0 &callback)
                {
                    m_selectedCallbacks.RemoveCallback(callback);
                }
                
                void TourHovercardViewInterop::Open(const std::string& title,
                                                    const std::string& subtitle,
                                                    const std::string& ratingsImage,
                                                    const int reviewCount,
                                                    float modality)
                {
                    [m_pView setFullyActive:modality];
                    [m_pView setContent:title :subtitle];
                }
                
                void TourHovercardViewInterop::Close()
                {
                    [m_pView setFullyInactive];
                }
                
                void TourHovercardViewInterop::UpdateScreenLocation(float posX, float posY)
                {
                    [m_pView updatePosition:posX :posY];
                }
                
                void TourHovercardViewInterop::UpdateScreenState(float screenState)
                {
                    [m_pView setAlpha:screenState];
                }
                
                void TourHovercardViewInterop::SetCurrentTour(const SdkModel::TourModel& tourModel)
                {
                    [m_pView setPresentationColors:tourModel.HoverCardBaseColor() :tourModel.HoverCardTextColor()];
                }
            }
        }
    }
}