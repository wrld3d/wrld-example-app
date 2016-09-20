// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Module.h"
#include "AndroidNativeState.h"
#include "ScreenProperties.h"
#include "Graphics.h"

namespace ExampleApp
{
    namespace Android
    {
        class AndroidAppModule : public Module
        {
        public:
        	AndroidAppModule(AndroidNativeState& nativeState,
        					 Eegeo::Rendering::ScreenProperties& screenProperties,
        					 EGLDisplay& display,
        			         EGLSurface& shareSurface,
        			         EGLContext& resourceBuildShareContext);

            void Register(const TContainerBuilder& builder);
        private:
            AndroidNativeState& m_nativeState;
            Eegeo::Rendering::ScreenProperties m_screenProperties;
            EGLDisplay m_display;
            EGLSurface m_shareSurface;
            EGLContext m_resourceBuildShareContext;
        };
    }
}
