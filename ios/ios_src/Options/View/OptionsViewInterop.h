// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "OptionsViewIncludes.h"
#include "IOptionsView.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class OptionsViewInterop : public IOptionsView, private Eegeo::NonCopyable
            {
            private:
                OptionsView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_closeCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_wifiOnlyCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_cacheEnabledCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_clearCacheCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_clearCacheTriggeredCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_replayTutorialsCallbacks;
                
            public:
                OptionsViewInterop(OptionsView* pView);
                
                bool IsStreamOverWifiOnlySelected() const;
                
                bool IsCacheEnabledSelected() const;
                
                void SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected);
                
                void SetCacheEnabledSelected(bool isCacheEnabledSelected);
                
                void Open();
                
                void Close();
                
                void OpenClearCacheWarning();
                
                void ConcludeCacheClearCeremony();
                
                void HandleCloseSelected();
                
                void HandleOkSelected();
                
                void HandleStreamOverWifiOnlySelectionStateChanged();
                
                void HandleCacheEnabledSelectionStateChanged();
                
                void HandleClearCacheSelected();
                
                void HandleClearCacheTriggered();
                
                void HandleReplayTutorialsSelected();
                
                void InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertCacheEnabledSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveCacheEnabledSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertClearCacheTriggeredCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveClearCacheTriggeredCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertReplayTutorialsSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveReplayTutorialsSelectedCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
    
}
