// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "ScreenProperties.h"
#include "iOSFlurryMetricsService.h"
#include "ApplicationConfiguration.h"
#include "ViewController.h"

namespace ExampleApp
{
    namespace iOS
    {
        class iOSAppModule : public ExampleApp::Module
        {
        public:
            iOSAppModule(
                         Eegeo::Rendering::ScreenProperties screenProperties,
                         ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                         ExampleApp::Metrics::iOSFlurryMetricsService& metricsService,
                         ViewController& viewController);
            
            void Register(const ExampleApp::TContainerBuilder& builder);
        
        private:
            Eegeo::Rendering::ScreenProperties m_screenProperties;
            ExampleApp::ApplicationConfig::ApplicationConfiguration& m_applicationConfiguration;
            ExampleApp::Metrics::iOSFlurryMetricsService& m_metricsService;
            ViewController& m_viewController;
        };
    }
}