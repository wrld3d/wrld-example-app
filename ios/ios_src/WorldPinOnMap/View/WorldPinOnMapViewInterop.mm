// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapViewInterop.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            void WorldPinOnMapViewInterop::OnSelected()
            {
                m_selectedCallbacks.ExecuteCallbacks();
            }

            void WorldPinOnMapViewInterop::InsertSelectedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_selectedCallbacks.AddCallback(callback);
            }

            void WorldPinOnMapViewInterop::RemoveSelectedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_selectedCallbacks.RemoveCallback(callback);
            }

            void WorldPinOnMapViewInterop::Open(const std::string& title,
                                                const std::string& subtitle,
                                                float modality)
            {
                [m_pView setFullyActive:modality];
                [m_pView setLabel:title :subtitle];
            }

            void WorldPinOnMapViewInterop::Close()
            {
                [m_pView setFullyInactive];
            }

            void WorldPinOnMapViewInterop::UpdateScreenLocation(float posX, float posY)
            {
                [m_pView updatePosition:posX :posY];
            }

            void WorldPinOnMapViewInterop::UpdateScreenState(float screenState)
            {
                [m_pView setAlpha:screenState];
            }
        }
    }
}