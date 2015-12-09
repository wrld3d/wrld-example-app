// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "Types.h"
#include "IPersistentSettingsModel.h"
#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace PersistentSettings
    {
        class WindowsPersistentSettingsModel : public IPersistentSettingsModel, private Eegeo::NonCopyable
        {
            WindowsNativeState& m_nativeState;

			gcroot<System::Type^> m_persistentSettingsClass;
			gcroot<System::Object^> m_persistentSettings;

			Helpers::ReflectionHelpers::Method<System::String^, bool> m_SetBool;
			Helpers::ReflectionHelpers::Method<System::String^, int> m_SetInt;
			Helpers::ReflectionHelpers::Method<System::String^, double> m_SetDouble;
			Helpers::ReflectionHelpers::Method<System::String^, System::String^> m_SetString;

			Helpers::ReflectionHelpers::Method<System::String^> m_GetBool;
			Helpers::ReflectionHelpers::Method<System::String^> m_GetInt;
			Helpers::ReflectionHelpers::Method<System::String^> m_GetDouble;
			Helpers::ReflectionHelpers::Method<System::String^> m_GetString;

			Helpers::ReflectionHelpers::Method<void> m_ClearAll;

			Helpers::ReflectionHelpers::Method<System::String^> m_ContainsKey;

        public:
            WindowsPersistentSettingsModel(WindowsNativeState& nativeState);

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

        private:
            bool HasValue(const std::string& name) const;
        };
    }
}
