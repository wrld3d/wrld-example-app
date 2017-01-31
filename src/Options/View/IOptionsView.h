// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class IOptionsView
            {
            public:
                virtual ~IOptionsView() { };
                
                virtual bool IsStreamOverWifiOnlySelected() const = 0;
                virtual bool IsCacheEnabledSelected() const = 0;
                
                virtual void SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected) = 0;
                virtual void SetCacheEnabledSelected(bool isCacheEnabledSelected) = 0;
                virtual void SetReplayTutorialsSelected(bool isReplayTutorialsSelected) = 0;
                
                virtual void Open() = 0;
                virtual void Close() = 0;
                virtual void ConcludeCacheClearCeremony() = 0;

                virtual void InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void InsertCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void InsertClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback) = 0;
                virtual void RemoveReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback) = 0;
            };
        }
    }
}
