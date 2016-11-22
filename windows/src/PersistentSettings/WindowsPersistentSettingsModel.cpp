// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsPersistentSettingsModel.h"
#include "WindowsPersistentSettingsModelImpl.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace PersistentSettings
    {
        WindowsPersistentSettingsModel::WindowsPersistentSettingsModel(const std::shared_ptr<WindowsNativeState>& nativeState)
        {
            m_pImpl = Eegeo_NEW(WindowsPersistentSettingsModelImpl)(nativeState);
        }

        WindowsPersistentSettingsModel::~WindowsPersistentSettingsModel()
        {
            Eegeo_DELETE m_pImpl;
        }

        bool WindowsPersistentSettingsModel::TryGetValue(const std::string& name, bool& out_value) const
        {
            return m_pImpl->TryGetValue(name, out_value);
        }

        bool WindowsPersistentSettingsModel::TryGetValue(const std::string& name, int& out_value) const
        {
            return m_pImpl->TryGetValue(name, out_value);

        }

        bool WindowsPersistentSettingsModel::TryGetValue(const std::string& name, double& out_value) const
        {
            return m_pImpl->TryGetValue(name, out_value);

        }

        bool WindowsPersistentSettingsModel::TryGetValue(const std::string& name, std::string& out_value) const
        {
            return m_pImpl->TryGetValue(name, out_value);
        }

        void WindowsPersistentSettingsModel::SetValue(const std::string& name, bool value)
        {
            m_pImpl->SetValue(name, value);
        }

        void WindowsPersistentSettingsModel::SetValue(const std::string& name, int value)
        {
            m_pImpl->SetValue(name, value);
        }

        void WindowsPersistentSettingsModel::SetValue(const std::string& name, double value)
        {
            m_pImpl->SetValue(name, value);
        }

        void WindowsPersistentSettingsModel::SetValue(const std::string& name, const std::string& value)
        {
            m_pImpl->SetValue(name, value);
        }

        void WindowsPersistentSettingsModel::ClearAll()
        {
            m_pImpl->ClearAll();
        }
    }
}
