// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    namespace PersistentSettings
    {
        class iOSPersistentSettingsModel : public IPersistentSettingsModel, private Eegeo::NonCopyable
        {
        public:
            iOSPersistentSettingsModel();

            ~iOSPersistentSettingsModel();

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

            void Flush();

            NSUserDefaults& m_userDefaults;
        };
    }
}
