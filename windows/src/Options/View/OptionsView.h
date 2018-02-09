// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IOptionsView.h"
#include "WindowsNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "ReflectionHelpers.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class OptionsView : public IOptionsView, private Eegeo::NonCopyable
            {
            private:
                WindowsNativeState& m_nativeState;
                
                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mIsCacheEnabledSelected;
				Helpers::ReflectionHelpers::Method<void> mIsClearCacheSelected;
				Helpers::ReflectionHelpers::Method<void> mOpenOptions;
                Helpers::ReflectionHelpers::Method<void> mCloseOptions;
				Helpers::ReflectionHelpers::Method<void> mOpenClearCacheWarning;
				Helpers::ReflectionHelpers::Method<void> mConcludeCacheClearCeremony;
                Helpers::ReflectionHelpers::Method<bool> mSetCacheEnabledSelected;
				Helpers::ReflectionHelpers::Method<bool> mSetClearCacheSelected;
				Helpers::ReflectionHelpers::Method<bool> mSetReplayTutorialsSelected;
                
				Eegeo::Helpers::CallbackCollection0 m_closeCallbacks;
				Eegeo::Helpers::CallbackCollection0 m_okCallbacks;
				Eegeo::Helpers::CallbackCollection0 m_wifiOnlyCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_cacheEnabledCallbacks;
				Eegeo::Helpers::CallbackCollection0 m_clearCacheCallbacks;
				Eegeo::Helpers::CallbackCollection0 m_clearCacheTriggeredCallbacks;
				Eegeo::Helpers::CallbackCollection1<bool> m_replayTutorialsCallbacks;

            public:
                OptionsView(WindowsNativeState& nativeState, const std::string& adminPassword, bool isInKioskMode);

                ~OptionsView();

                bool IsStreamOverWifiOnlySelected() const;

				bool IsCacheEnabledSelected() const;

				bool IsClearCacheSelected() const;

                void SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected);

				void SetCacheEnabledSelected(bool isCacheEnabledSelected);

				void SetClearCacheSelected(bool isClearCacheSelected);

                void SetReplayTutorialsSelected(bool isReplayTutorialsSelected);

				void Open();

                void Close();

				void OpenClearCacheWarning();

                void ConcludeCacheClearCeremony();

				void HandleCloseSelected();

				void HandleOkSelected();

                void HandleStreamOverWifiOnlySelectionStateChanged();

                void HandleCacheEnabledSelectionStateChanged();

				void HandleClearCacheSelectionStateChanged();

				void HandleClearCacheTriggered();

                void HandleReplayTutorialsToggled(bool enableTutorials);

				void InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback);
				void RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback);

				void InsertOkSelectedCallback(Eegeo::Helpers::ICallback0& callback);
				void RemoveOkSelectedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertCacheEnabledSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveCacheEnabledSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertClearCacheSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveClearCacheSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);

				void InsertClearCacheTriggeredCallback(Eegeo::Helpers::ICallback0& callback);
				void RemoveClearCacheTriggeredCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback);
                void RemoveReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback);
            };
        }
    }
}
