// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinInFocusViewModel.h"
#include "LatLongAltitude.h"
#include "IWorldPinsService.h"
#include "IWorldPinSelectionHandler.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinInFocusViewModel::WorldPinInFocusViewModel(Eegeo::Helpers::TIdentity identity,
                    SdkModel::IWorldPinsService& worldPinsService)
                : m_isOpen(false)
                , m_screenControl(identity)
                , m_worldPinsService(worldPinsService)
            {

            }

            WorldPinInFocusViewModel::~WorldPinInFocusViewModel()
            {

            }

            const SdkModel::WorldPinsInFocusModel& WorldPinInFocusViewModel::GetWorldPinsInFocusModel() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
                return m_worldPinInFocusModel;
            }

            bool WorldPinInFocusViewModel::IsOpen() const
            {
                return m_isOpen;
            }

            const Eegeo::v2& WorldPinInFocusViewModel::ScreenLocation() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read ScreenLocation when view model is not open.\n");
                return m_screenPos;
            }

            void WorldPinInFocusViewModel::SelectFocussedResult()
            {
                SdkModel::IWorldPinSelectionHandler* pSelectionHandler = m_worldPinsService.GetSelectionHandlerForPin(m_worldPinInFocusModel.GetPinId());

                if (pSelectionHandler)
                {
                    pSelectionHandler->SelectPin();
                }
            }

            void WorldPinInFocusViewModel::Open(const SdkModel::WorldPinsInFocusModel& worldPinsInFocusModel, const Eegeo::v2& screenPos)
            {
                m_worldPinInFocusModel = worldPinsInFocusModel;
                m_isOpen = true;
                m_screenPos = screenPos;
                m_screenControl.AddToScreen();
                m_openedCallbacks.ExecuteCallbacks();
            }

            void WorldPinInFocusViewModel::Close()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot close SearchResultModel when view model when already closed.\n");
                m_isOpen = false;
                m_screenControl.RemoveFromScreen();
                m_closedCallbacks.ExecuteCallbacks();
            }

            void WorldPinInFocusViewModel::UpdateScreenLocation(const Eegeo::v2 &screenPos)
            {
                Eegeo_ASSERT(IsOpen(), "Cannot UpdateScreenLocation when view model is not open.\n");
                m_screenPos = screenPos;
                m_updateCallbacks.ExecuteCallbacks();
            }

            ScreenControl::View::IScreenControlViewModel& WorldPinInFocusViewModel::GetScreenControlViewModel()
            {
                return m_screenControl;
            }

            void WorldPinInFocusViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void WorldPinInFocusViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void WorldPinInFocusViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void WorldPinInFocusViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }

            void WorldPinInFocusViewModel::InsertUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback)
            {
                m_updateCallbacks.AddCallback(updateCallback);
            }

            void WorldPinInFocusViewModel::RemoveUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback)
            {
                m_updateCallbacks.RemoveCallback(updateCallback);
            }
        }
    }
}
