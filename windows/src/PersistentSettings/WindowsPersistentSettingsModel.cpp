// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsPersistentSettingsModel.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace PersistentSettings
    {
        WindowsPersistentSettingsModel::WindowsPersistentSettingsModel(WindowsNativeState& nativeState)
            : m_nativeState(nativeState)
        {
            ASSERT_NATIVE_THREAD

			m_persistentSettingsClass = Helpers::ReflectionHelpers::GetTypeFromEntryAssembly("ExampleAppWPF.PersistentSettings");
			System::Reflection::ConstructorInfo^ ctor = m_persistentSettingsClass->GetConstructor(Helpers::ReflectionHelpers::CreateTypes(System::IntPtr::typeid));
			m_persistentSettings = ctor->Invoke(Helpers::ReflectionHelpers::CreateObjects(gcnew System::IntPtr(this)));

			m_SetBool.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "SetBool");
			m_SetInt.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "SetInt");
			m_SetDouble.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "SetDouble");
			m_SetString.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "SetString");

			m_GetBool.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "GetBool");
			m_GetInt.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "GetInt");
			m_GetDouble.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "GetDouble");
			m_GetString.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "GetString");

			m_ClearAll.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "ClearAll");

			m_ContainsKey.SetupMethod(m_persistentSettingsClass, m_persistentSettings, "ContainsKey");
        }

        WindowsPersistentSettingsModel::~WindowsPersistentSettingsModel()
        {
            ASSERT_NATIVE_THREAD
        }

        bool WindowsPersistentSettingsModel::TryGetValue(const std::string& name, bool& out_value) const
        {
			ASSERT_NATIVE_THREAD

            if(HasValue(name))
            {
				out_value = m_GetBool.Call<bool>(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(name));

                return true;
            }

            return false;
        }

        bool WindowsPersistentSettingsModel::TryGetValue(const std::string& name, int& out_value) const
        {
            ASSERT_NATIVE_THREAD

            if(HasValue(name))
            {
				out_value = m_GetInt.Call<int>(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(name));

                return true;
            }

            return false;
        }

        bool WindowsPersistentSettingsModel::TryGetValue(const std::string& name, double& out_value) const
        {
            ASSERT_NATIVE_THREAD

            if(HasValue(name))
            {
				out_value = m_GetDouble.Call<double>(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(name));

                return true;
            }

            return false;
        }

        bool WindowsPersistentSettingsModel::TryGetValue(const std::string& name, std::string& out_value) const
        {
            ASSERT_NATIVE_THREAD

            if(HasValue(name))
            {
				out_value = Helpers::ReflectionHelpers::ConvertManagedStringToUTF8(
					m_GetString.Call<System::String^>(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(name)));

                return true;
            }

            return false;
        }

        void WindowsPersistentSettingsModel::SetValue(const std::string& name, bool value)
        {
			ASSERT_NATIVE_THREAD

			m_SetBool(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(name), value);
        }

        void WindowsPersistentSettingsModel::SetValue(const std::string& name, int value)
        {
            ASSERT_NATIVE_THREAD

            m_SetInt(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(name), value);
        }

        void WindowsPersistentSettingsModel::SetValue(const std::string& name, double value)
        {
            ASSERT_NATIVE_THREAD

			m_SetDouble(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(name), value);
        }

        void WindowsPersistentSettingsModel::SetValue(const std::string& name, const std::string& value)
        {
            ASSERT_NATIVE_THREAD

			m_SetString(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(name), Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(value));
        }

        void WindowsPersistentSettingsModel::ClearAll()
        {
			ASSERT_NATIVE_THREAD

			m_ClearAll();
        }

        bool WindowsPersistentSettingsModel::HasValue(const std::string& name) const
        {
			return m_ContainsKey.Call<bool>(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(name));
        }
    }
}
