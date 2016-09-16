// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace Android
    {
        class AndroidAppModule : public Module
        {
        public:
            AndroidAppModule(
//                         Eegeo::Rendering::ScreenProperties screenProperties,
//                         ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
//                         ExampleApp::Metrics::AndroidFlurryMetricsService& metricsService,
            			 Eegeo::Android::AndroidLocationService& androidLocationService,
            		   	 Eegeo::Android::AndroidConnectivityService& androidConnectivityService,
						 Eegeo::Android::Input::AndroidInputProcessor& inputProcessor);

            void Register(const TContainerBuilder& builder);

        private:
//            Eegeo::Rendering::ScreenProperties m_screenProperties;
//            ExampleApp::ApplicationConfig::ApplicationConfiguration& m_applicationConfiguration;
//            ExampleApp::Metrics::AndroidFlurryMetricsService& m_metricsService;
			Eegeo::Android::AndroidLocationService* m_pAndroidLocationService;
			Eegeo::Android::AndroidConnectivityService* m_pAndroidConnectivityService;
			Eegeo::Android::Input::AndroidInputProcessor* m_pAndroidInputProcessor;
        };
    }
}
