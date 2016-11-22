// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsViewImpl.h"
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
            OptionsViewImpl::OptionsViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.OptionsView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mIsCacheEnabledSelected.SetupMethod(m_uiViewClass, m_uiView, "IsCacheEnabledSelected");
                mOpenOptions.SetupMethod(m_uiViewClass, m_uiView, "OpenOptions");
                mCloseOptions.SetupMethod(m_uiViewClass, m_uiView, "CloseOptions");
                mConcludeCacheClearCeremony.SetupMethod(m_uiViewClass, m_uiView, "ConcludeCacheClearCeremony");
                mSetCacheEnabledSelected.SetupMethod(m_uiViewClass, m_uiView, "SetCacheEnabledSelected");
            }

            OptionsViewImpl::~OptionsViewImpl()
            {
                mDestroy();
            }

            bool OptionsViewImpl::IsStreamOverWifiOnlySelected() const
            {
                return false;
            }

            bool OptionsViewImpl::IsCacheEnabledSelected() const
            {
                return (bool)mIsCacheEnabledSelected.Call<System::Boolean^>();
            }

            void OptionsViewImpl::SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected)
            {
                // doesn't make any sense for windows, so just stubbing out implementation
            }

            void OptionsViewImpl::SetCacheEnabledSelected(bool isCacheEnabledSelected)
            {
                mSetCacheEnabledSelected(isCacheEnabledSelected);
            }

            void OptionsViewImpl::Open()
            {
                mOpenOptions();
            }

            void OptionsViewImpl::Close()
            {
                mCloseOptions();
            }

            void OptionsViewImpl::ConcludeCacheClearCeremony()
            {
                mConcludeCacheClearCeremony();
            }

            void OptionsViewImpl::HandleCloseSelected()
            {
                m_closeCallbacks.ExecuteCallbacks();
            }

            void OptionsViewImpl::HandleStreamOverWifiOnlySelectionStateChanged()
            {
                m_wifiOnlyCallbacks.ExecuteCallbacks();
            }

            void OptionsViewImpl::HandleCacheEnabledSelectionStateChanged()
            {
                m_cacheEnabledCallbacks.ExecuteCallbacks();
            }

            void OptionsViewImpl::HandleClearCacheSelected()
            {
                m_clearCacheCallbacks.ExecuteCallbacks();
            }

            void OptionsViewImpl::InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeCallbacks.AddCallback(callback);
            }

            void OptionsViewImpl::RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closeCallbacks.RemoveCallback(callback);
            }

            void OptionsViewImpl::InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_wifiOnlyCallbacks.AddCallback(callback);
            }

            void OptionsViewImpl::RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_wifiOnlyCallbacks.RemoveCallback(callback);
            }

            void OptionsViewImpl::InsertCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheEnabledCallbacks.AddCallback(callback);
            }

            void OptionsViewImpl::RemoveCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheEnabledCallbacks.RemoveCallback(callback);
            }

            void OptionsViewImpl::InsertClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheCallbacks.AddCallback(callback);
            }

            void OptionsViewImpl::RemoveClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_clearCacheCallbacks.RemoveCallback(callback);
            }
        }
    }
}
