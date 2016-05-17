// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>
#include "AndroidNativeState.h"
#include "Types.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    namespace PersistentSettings
    {
        class AndroidPersistentSettingsModel : public IPersistentSettingsModel, private Eegeo::NonCopyable
        {
            AndroidNativeState& m_nativeState;
            jclass m_jniApiClass;
            jobject m_jniApiInstance;

        public:
            AndroidPersistentSettingsModel(AndroidNativeState& nativeState);

            ~AndroidPersistentSettingsModel();

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

            template <typename TValue>
            void SetValue(const std::string& name, TValue value, const std::string& method, const std::string& signature);
        };
    }
}
