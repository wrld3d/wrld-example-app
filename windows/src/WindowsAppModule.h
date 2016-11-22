// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Module.h"
#include "WindowsNativeState.h"
#include "ScreenProperties.h"
#include "Graphics.h"

namespace ExampleApp
{
    namespace Windows
    {
        class WindowsAppModule : public Module
        {
        public:
            WindowsAppModule(WindowsNativeState& nativeState,
                Eegeo::Rendering::ScreenProperties& screenProperties,
                EGLDisplay& display,
                EGLSurface& shareSurface,
                EGLContext& resourceBuildShareContext,
                bool hasNativeTouchInput,
                int maxDeviceTouchCount);

            void Register(const TContainerBuilder& builder);
            void RegisterLeaves();
        private:
            WindowsNativeState& m_nativeState;
            Eegeo::Rendering::ScreenProperties m_screenProperties;
            std::set<std::string> m_customApplicationAssetDirectories;
            EGLDisplay m_display;
            EGLSurface m_shareSurface;
            EGLContext m_resourceBuildShareContext;
            bool m_hasNativeTouchInput;
            int m_maxDeviceTouchCount;
        };
    }
}