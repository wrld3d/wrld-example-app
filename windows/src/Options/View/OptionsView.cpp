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
				mIsClearCacheSelected.SetupMethod(m_uiViewClass, m_uiView, "IsClearCacheSelected");
                mOpenOptions.SetupMethod(m_uiViewClass, m_uiView, "OpenOptions");
                mCloseOptions.SetupMethod(m_uiViewClass, m_uiView, "CloseOptions");
				mOpenClearCacheWarning.SetupMethod(m_uiViewClass, m_uiView, "OpenClearCacheWarning");
                mConcludeCacheClearCeremony.SetupMethod(m_uiViewClass, m_uiView, "ConcludeCacheClearCeremony");
				mSetCacheEnabledSelected.SetupMethod(m_uiViewClass, m_uiView, "SetCacheEnabledSelected");
				mSetClearCacheSelected.SetupMethod(m_uiViewClass, m_uiView, "SetClearCacheSelected");
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

			bool OptionsView::IsClearCacheSelected() const
			{
				return (bool)mIsClearCacheSelected.Call<System::Boolean^>();
			}

            void OptionsView::SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected)
            {
                // doesn't make any sense for windows, so just stubbing out implementation
            }

            void OptionsView::SetCacheEnabledSelected(bool isCacheEnabledSelected)
            {
                mSetCacheEnabledSelected(isCacheEnabledSelected);
            }

			void OptionsView::SetClearCacheSelected(bool isClearCacheSelected)
			{
				mSetClearCacheSelected(isClearCacheSelected);
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

			void OptionsView::OpenClearCacheWarning()
			{
				mOpenClearCacheWarning();
			}

            void OptionsView::ConcludeCacheClearCeremony()
            {
                mConcludeCacheClearCeremony();
            }

			void OptionsView::HandleCloseSelected()
			{
				m_closeCallbacks.ExecuteCallbacks();
			}

			void OptionsView::HandleOkSelected()
			{
				m_okCallbacks.ExecuteCallbacks();
			}

            void OptionsView::HandleStreamOverWifiOnlySelectionStateChanged()
            {
                m_wifiOnlyCallbacks.ExecuteCallbacks();
            }

            void OptionsView::HandleCacheEnabledSelectionStateChanged()
            {
                m_cacheEnabledCallbacks.ExecuteCallbacks();
            }

			void OptionsView::HandleClearCacheSelectionStateChanged()
			{
				m_clearCacheCallbacks.ExecuteCallbacks();
			}

			void OptionsView::HandleClearCacheTriggered()
			{
				m_clearCacheTriggeredCallbacks.ExecuteCallbacks();
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

			void OptionsView::InsertOkSelectedCallback(Eegeo::Helpers::ICallback0& callback)
			{
				m_okCallbacks.AddCallback(callback);
			}

			void OptionsView::RemoveOkSelectedCallback(Eegeo::Helpers::ICallback0& callback)
			{
				m_okCallbacks.RemoveCallback(callback);
			}

            void OptionsView::InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_wifiOnlyCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_wifiOnlyCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertCacheEnabledSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheEnabledCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveCacheEnabledSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheEnabledCallbacks.RemoveCallback(callback);
            }

            void OptionsView::InsertClearCacheSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheCallbacks.AddCallback(callback);
            }

            void OptionsView::RemoveClearCacheSelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheCallbacks.RemoveCallback(callback);
            }

			void OptionsView::InsertClearCacheTriggeredCallback(Eegeo::Helpers::ICallback0& callback)
			{
				m_clearCacheTriggeredCallbacks.AddCallback(callback);
			}

			void OptionsView::RemoveClearCacheTriggeredCallback(Eegeo::Helpers::ICallback0& callback)
			{
				m_clearCacheTriggeredCallbacks.RemoveCallback(callback);
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
