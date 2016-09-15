// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace iOS
    {
        class iOSAbstractionIoCModule : public ExampleApp::Module
        {
        public:
            void Register(const ExampleApp::TContainerBuilder& builder);
        };
    }
}