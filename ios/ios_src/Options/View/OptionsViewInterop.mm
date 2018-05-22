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
            
            void OptionsViewInterop::Open()
            {
                [m_pView setFullyActive];
            }
            
            void OptionsViewInterop::Close()
            {
                [m_pView setFullyInactive];
            }
            
            void OptionsViewInterop::OpenClearCacheWarning()
            {
                [m_pView openClearCacheWarning];
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
            
            void OptionsViewInterop::HandleClearCacheTriggered()
            {
                m_clearCacheTriggeredCallbacks.ExecuteCallbacks();
            }
            
            void OptionsViewInterop::HandleReplayTutorialsSelected()
            {
                m_replayTutorialsCallbacks.ExecuteCallbacks();
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
            
            void OptionsViewInterop::InsertCacheEnabledSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheEnabledCallbacks.AddCallback(callback);
            }
            
            void OptionsViewInterop::RemoveCacheEnabledSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
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
            
            void OptionsViewInterop::InsertClearCacheTriggeredCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheTriggeredCallbacks.AddCallback(callback);
            }
            
            void OptionsViewInterop::RemoveClearCacheTriggeredCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheTriggeredCallbacks.RemoveCallback(callback);
            }
            
            void OptionsViewInterop::InsertReplayTutorialsSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_replayTutorialsCallbacks.AddCallback(callback);
            }
            
            void OptionsViewInterop::RemoveReplayTutorialsSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_replayTutorialsCallbacks.RemoveCallback(callback);
            }
        }
    }
}
