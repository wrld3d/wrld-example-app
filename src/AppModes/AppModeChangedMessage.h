// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace AppModes
    {
        class AppModeChangedMessage
        {
        public:
            AppModeChangedMessage(SdkModel::AppMode appMode)
            : m_appMode(appMode)
            {}
            
            SdkModel::AppMode GetAppMode() const { return m_appMode; }
            
        private:
            const SdkModel::AppMode m_appMode;
        };
    }
}