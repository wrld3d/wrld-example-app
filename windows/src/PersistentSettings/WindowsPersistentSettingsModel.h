// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "Types.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    namespace PersistentSettings
    {
        class WindowsPersistentSettingsModelImpl;

        class WindowsPersistentSettingsModel : public IPersistentSettingsModel, private Eegeo::NonCopyable
        {
            WindowsPersistentSettingsModelImpl* m_pImpl;

        public:
            WindowsPersistentSettingsModel(const std::shared_ptr<WindowsNativeState>& nativeState);

            ~WindowsPersistentSettingsModel();

            bool TryGetValue(const std::string& name, bool& out_value) const;

            bool TryGetValue(const std::string& name, int& out_value) const;

            bool TryGetValue(const std::string& name, double& out_value) const;

            bool TryGetValue(const std::string& name, std::string& out_value) const;

            void SetValue(const std::string& name, bool value);

            void SetValue(const std::string& name, int value);

            void SetValue(const std::string& name, double value);

            void SetValue(const std::string& name, const std::string& value);

            void ClearAll();
        };
    }
}
