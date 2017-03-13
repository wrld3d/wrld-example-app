// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsView.h"
#include "WindowsAppThreadAssertionMacros.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;
using namespace System::Reflection;
using namespace System;

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            OptionsView::OptionsView(WindowsNativeState& nativeState, const std::string& adminPassword, bool isInKioskMode)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.OptionsView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid, System::String::typeid, System::Boolean::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this), gcnew System::String(adminPassword.c_str()), gcnew System::Boolean(isInKioskMode)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mIsCacheEnabledSelected.SetupMethod(m_uiViewClass, m_uiView, "IsCacheEnabledSelected");
                mOpenOptions.SetupMethod(m_uiViewClass, m_uiView, "OpenOptions");
                mCloseOptions.SetupMethod(m_uiViewClass, m_uiView, "CloseOptions");
                mConcludeCacheClearCeremony.SetupMethod(m_uiViewClass, m_uiView, "ConcludeCacheClearCeremony");
                mSetCacheEnabledSelected.SetupMethod(m_uiViewClass, m_uiView, "SetCacheEnabledSelected");
                mSetReplayTutorialsSelected.SetupMethod(m_uiViewClass, m_uiView, "SetReplayTutorialsSelected");
            }

            OptionsView::~OptionsView()
            {
                mDestroy();
            }

            bool OptionsView::IsStreamOverWifiOnlySelected() const
            {
                return false;
            }

            bool OptionsView::IsCacheEnabledSelected() const
            {
                return (bool)mIsCacheEnabledSelected.Call<System::Boolean^>();
            }

            void OptionsView::SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected)
            {
                // doesn't make any sense for windows, so just stubbing out implementation
            }

            void OptionsView::SetCacheEnabledSelected(bool isCacheEnabledSelected)
            {
                mSetCacheEnabledSelected(isCacheEnabledSelected);
            }

            void OptionsView::SetReplayTutorialsSelected(bool isReplayTutorialsSelected)
            {
                mSetReplayTutorialsSelected(isReplayTutorialsSelected);
            }

            void OptionsView::Open()
            {
                mOpenOptions();
            }

            void OptionsView::Close()
            {
                mCloseOptions();
            }

            void OptionsView::ConcludeCacheClearCeremony()
            {
                mConcludeCacheClearCeremony();
            }

            void OptionsView::HandleCloseSelected()
            {
                m_closeCallbacks.ExecuteCallbacks();
            }

            void OptionsView::HandleStreamOverWifiOnlySelectionStateChanged()
            {
                m_wifiOnlyCallbacks.ExecuteCallbacks();
            }

            void OptionsView::HandleCacheEnabledSelectionStateChanged()
            {
                m_cacheEnabledCallbacks.ExecuteCallbacks();
            }

            void OptionsView::HandleClearCacheSelected()
            {
                m_clearCacheCallbacks.ExecuteCallbacks();
            }

            void OptionsView::HandleReplayTutorialsToggled(bool enableTutorials)
            {
                m_replayTutorialsCallbacks.ExecuteCallbacks(enableTutorials);
            }

            void OptionsView::InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_wifiOnlyCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_wifiOnlyCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheEnabledCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheEnabledCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_replayTutorialsCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveReplayTutorialsToggledCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_replayTutorialsCallbacks.RemoveCallback(callback);
            }
        }
    }
}
