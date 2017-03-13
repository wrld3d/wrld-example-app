// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsViewInterop.h"
#include "OptionsView.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            OptionsViewInterop::OptionsViewInterop(OptionsView* pView) : m_pView(pView)
            {
            }
            
            bool OptionsViewInterop::IsStreamOverWifiOnlySelected() const
            {
                return [m_pView isStreamOverWifiOnlySelected];
            }
            
            bool OptionsViewInterop::IsCacheEnabledSelected() const
            {
                return [m_pView isCacheEnabledSelected];
            }
            
            void OptionsViewInterop::SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected)
            {
                [m_pView setStreamOverWifiOnlySelected:isStreamOverWifiOnlySelected];
            }
            
            void OptionsViewInterop::SetCacheEnabledSelected(bool isCacheEnabledSelected)
            {
                [m_pView setCacheEnabledSelected:isCacheEnabledSelected];
            }
            
            void OptionsViewInterop::SetReplayTutorialsSelected(bool isReplayTutorialsSelected)
            {
                [m_pView setReplayTutorialsSelected:isReplayTutorialsSelected];
            }

            void OptionsViewInterop::Open()
            {
                [m_pView setFullyActive];
            }

            void OptionsViewInterop::Close()
            {
                [m_pView setFullyInactive];
            }
            
            void OptionsViewInterop::ConcludeCacheClearCeremony()
            {
                [m_pView concludeCacheClearCeremony];
            }
            
            void OptionsViewInterop::HandleCloseSelected()
            {
                m_closeCallbacks.ExecuteCallbacks();
            }
            
            void OptionsViewInterop::HandleStreamOverWifiOnlySelectionStateChanged()
            {
                m_wifiOnlyCallbacks.ExecuteCallbacks();
            }
            
            void OptionsViewInterop::HandleCacheEnabledSelectionStateChanged()
            {
                m_cacheEnabledCallbacks.ExecuteCallbacks();
            }
            
            void OptionsViewInterop::HandleClearCacheSelected()
            {
                m_clearCacheCallbacks.ExecuteCallbacks();
            }

            void OptionsViewInterop::InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeCallbacks.AddCallback(callback);
            }

            void OptionsViewInterop::RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeCallbacks.RemoveCallback(callback);
            }
            
            void OptionsViewInterop::InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_wifiOnlyCallbacks.AddCallback(callback);
            }
            
            void OptionsViewInterop::RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_wifiOnlyCallbacks.RemoveCallback(callback);
            }
            
            void OptionsViewInterop::InsertCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheEnabledCallbacks.AddCallback(callback);
            }
            
            void OptionsViewInterop::RemoveCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheEnabledCallbacks.RemoveCallback(callback);
            }
            
            void OptionsViewInterop::InsertClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheCallbacks.AddCallback(callback);
            }
            
            void OptionsViewInterop::RemoveClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheCallbacks.RemoveCallback(callback);
            }

            void OptionsViewInterop::InsertReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_replayTutorialsToggledCallbacks.AddCallback(callback);
            }

            void OptionsViewInterop::RemoveReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_replayTutorialsToggledCallbacks.RemoveCallback(callback);
            }
        }
    }
}
