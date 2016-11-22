// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapView.h"
#include "WorldPinOnMapViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ImagePathHelpers.h"
#include "IWorldPinsInFocusModel.h"
#include "SearchVendorNames.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinOnMapView::WorldPinOnMapView(const std::shared_ptr<WindowsNativeState>& nativeState, const std::shared_ptr<ApplicationConfig::ApplicationConfiguration>& appConfig)
            {
                m_pImpl = Eegeo_NEW(WorldPinOnMapViewImpl)(nativeState, appConfig);
            }

            WorldPinOnMapView::~WorldPinOnMapView()
            {
                Eegeo_DELETE m_pImpl;   
            }

            void WorldPinOnMapView::Open(const WorldPins::SdkModel::IWorldPinsInFocusModel& worldPinsInFocusModel,
                    float modality)
            {
                m_pImpl->Open(worldPinsInFocusModel, modality);
            }

            void WorldPinOnMapView::Close()
            {
                m_pImpl->Close();
            }

            void WorldPinOnMapView::UpdateScreenLocation(float posX, float posY)
            {
                m_pImpl->UpdateScreenLocation(posX, posY);
            }

            void WorldPinOnMapView::UpdateScreenState(float screenState)
            {
                m_pImpl->UpdateScreenState(screenState);
            }

            void WorldPinOnMapView::OnSelected()
            {
                m_pImpl->OnSelected();
            }

            void WorldPinOnMapView::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertSelectedCallback(callback);
            }

            void WorldPinOnMapView::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveSelectedCallback(callback);
            }
        }
    }
}
