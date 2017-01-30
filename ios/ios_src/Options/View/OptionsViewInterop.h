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
                Eegeo::Helpers::CallbackCollection1<bool> m_replayTutorialsToggledCallbacks;

            public:
                OptionsViewInterop(OptionsView* pView);
                
                bool IsStreamOverWifiOnlySelected() const;
                
                bool IsCacheEnabledSelected() const;
                
                void SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected);
                
                void SetCacheEnabledSelected(bool isCacheEnabledSelected);
                
                void SetReplayTutorialsSelected(bool isReplayTutorialsSelected);

                void Open();

                void Close();
                
                void ConcludeCacheClearCeremony();
                
                void HandleCloseSelected();
                
                void HandleStreamOverWifiOnlySelectionStateChanged();
                
                void HandleCacheEnabledSelectionStateChanged();
                
                void HandleClearCacheSelected();

                void InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback);
                
                void InsertClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback);
                void RemoveReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback);
            };
        }
    }

}
