// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "PersistentSettings.h"

namespace ExampleApp
{
    namespace PersistentSettings
    {
        class IPersistentSettingsModel
        {
        public:
            virtual ~IPersistentSettingsModel() {}

            virtual bool TryGetValue(const std::string& name, bool& out_value) const = 0;

            virtual bool TryGetValue(const std::string& name, int& out_value) const = 0;

            virtual bool TryGetValue(const std::string& name, double& out_value) const = 0;

            virtual bool TryGetValue(const std::string& name, std::string& out_value) const = 0;

            virtual void SetValue(const std::string& name, bool value) = 0;

            virtual void SetValue(const std::string& name, int value) = 0;

            virtual void SetValue(const std::string& name, double value) = 0;

            virtual void SetValue(const std::string& name, const std::string& value) = 0;

            virtual void ClearAll() = 0;
        };
    }
}
