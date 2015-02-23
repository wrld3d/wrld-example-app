// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSPersistentSettingsModel.h"

namespace
{
    NSString* ToNSString(const std::string& s)
    {
        return [NSString stringWithUTF8String:s.c_str()];
    }
}

namespace ExampleApp
{
    namespace PersistentSettings
    {
        iOSPersistentSettingsModel::iOSPersistentSettingsModel()
            : m_userDefaults(*[NSUserDefaults standardUserDefaults])
        {

        }

        iOSPersistentSettingsModel::~iOSPersistentSettingsModel()
        {

        }

        bool iOSPersistentSettingsModel::TryGetValue(const std::string& name, bool& out_value) const
        {
            id value = [&m_userDefaults objectForKey:ToNSString(name)];

            if(value != nil)
            {
                out_value = [&m_userDefaults boolForKey:ToNSString(name)];
                return true;
            }

            return false;
        }

        bool iOSPersistentSettingsModel::TryGetValue(const std::string& name, int& out_value) const
        {
            id value = [&m_userDefaults objectForKey:ToNSString(name)];

            if(value != nil)
            {
                out_value = static_cast<int>([&m_userDefaults integerForKey:ToNSString(name)]);
                return true;
            }

            return false;
        }

        bool iOSPersistentSettingsModel::TryGetValue(const std::string& name, double& out_value) const
        {
            id value = [&m_userDefaults objectForKey:ToNSString(name)];

            if(value != nil)
            {
                out_value = [&m_userDefaults doubleForKey:ToNSString(name)];
                return true;
            }

            return false;
        }

        bool iOSPersistentSettingsModel::TryGetValue(const std::string& name, std::string& out_value) const
        {
            id value = [&m_userDefaults objectForKey:ToNSString(name)];

            if(value != nil)
            {
                out_value = [value UTF8String];
            }

            return false;
        }

        void iOSPersistentSettingsModel::SetValue(const std::string& name, bool value)
        {
            [&m_userDefaults setBool:value forKey:ToNSString(name)];
            Flush();
        }

        void iOSPersistentSettingsModel::SetValue(const std::string& name, int value)
        {
            [&m_userDefaults setInteger:value forKey:ToNSString(name)];
            Flush();
        }

        void iOSPersistentSettingsModel::SetValue(const std::string& name, double value)
        {
            [&m_userDefaults setDouble:value forKey:ToNSString(name)];
            Flush();
        }

        void iOSPersistentSettingsModel::SetValue(const std::string& name, const std::string& value)
        {
            [&m_userDefaults setObject:ToNSString(name) forKey:ToNSString(name)];
            Flush();
        }

        void iOSPersistentSettingsModel::ClearAll()
        {
            NSString *appDomain = [[NSBundle mainBundle] bundleIdentifier];
            [[NSUserDefaults standardUserDefaults] removePersistentDomainForName:appDomain];
            Flush();
        }

        void iOSPersistentSettingsModel::Flush()
        {
            [&m_userDefaults synchronize];
        }
    }
}
