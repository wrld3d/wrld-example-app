// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "ApplicationConfig.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        class ApplicationConfiguration
        {
            std::string m_name;
            Eegeo::Space::LatLongAltitude m_interestLocation;
            float m_distanceToInterestMetres;
            float m_orientationDegrees;
            bool m_tryStartAtGpsLocation;
            std::string m_googleAnalyticsReferrerToken;
            
        public:
            
            ApplicationConfiguration(const std::string& name,
                                     const Eegeo::Space::LatLongAltitude& interestLocation,
                                     float distanceToInterestMetres,
                                     float orientationDegrees,
                                     bool tryStartAtGpsLocation,
                                     const std::string& googleAnalyticsReferrerToken);
            
            const std::string& Name() const;
            
            const Eegeo::Space::LatLongAltitude& InterestLocation() const;
            
            float DistanceToInterestMetres() const;
            
            float OrientationDegrees() const;
            
            bool TryStartAtGpsLocation() const;
            
            const std::string& GoogleAnalyticsReferrerToken() const;
        };
    }
}
