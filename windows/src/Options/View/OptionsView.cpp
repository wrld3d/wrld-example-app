// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsView.h"
#include "OptionsViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            OptionsView::OptionsView(const std::shared_ptr<WindowsNativeState>& nativeState)
            {
                m_pImpl = Eegeo_NEW(OptionsViewImpl)(nativeState);
            }

            OptionsView::~OptionsView()
            {
                Eegeo_DELETE m_pImpl;
            }

            bool OptionsView::IsStreamOverWifiOnlySelected() const
            {
                return m_pImpl->IsStreamOverWifiOnlySelected();
            }

            bool OptionsView::IsCacheEnabledSelected() const
            {
                return m_pImpl->IsCacheEnabledSelected();
            }

            void OptionsView::SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected)
            {
                m_pImpl->SetStreamOverWifiOnlySelected(isStreamOverWifiOnlySelected);
            }

            void OptionsView::SetCacheEnabledSelected(bool isCacheEnabledSelected)
            {
                m_pImpl->SetCacheEnabledSelected(isCacheEnabledSelected);
            }

            void OptionsView::Open()
            {
                m_pImpl->Open();
            }

            void OptionsView::Close()
            {
                m_pImpl->Close();
            }

            void OptionsView::ConcludeCacheClearCeremony()
            {
                m_pImpl->ConcludeCacheClearCeremony();
            }

            void OptionsView::HandleCloseSelected()
            {
                m_pImpl->HandleCloseSelected();
            }

            void OptionsView::HandleStreamOverWifiOnlySelectionStateChanged()
            {
                m_pImpl->HandleStreamOverWifiOnlySelectionStateChanged();
            }

            void OptionsView::HandleCacheEnabledSelectionStateChanged()
            {
                m_pImpl->HandleCacheEnabledSelectionStateChanged();
            }

            void OptionsView::HandleClearCacheSelected()
            {
                m_pImpl->HandleClearCacheSelected();
            }

            void OptionsView::InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertCloseSelectedCallback(callback);
            }

            void OptionsView::RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveCloseSelectedCallback(callback);
            }

            void OptionsView::InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertStreamOverWifiOnlySelectionChangedCallback(callback);
            }

            void OptionsView::RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveStreamOverWifiOnlySelectionChangedCallback(callback);
            }

            void OptionsView::InsertCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertCacheEnabledSelectionCallback(callback);
            }

            void OptionsView::RemoveCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveCacheEnabledSelectionCallback(callback);
            }

            void OptionsView::InsertClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertClearCacheSelectedCallback(callback);
            }

            void OptionsView::RemoveClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveClearCacheSelectedCallback(callback);
            }
        }
    }
}
