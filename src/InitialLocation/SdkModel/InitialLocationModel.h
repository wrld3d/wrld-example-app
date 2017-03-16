// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IInitialLocationModel.h"
#include "Types.h"
#include "PersistentSettings.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace InitialLocation
    {
        namespace SdkModel
        {
            class InitialLocationModel : public IInitialLocationModel, private Eegeo::NonCopyable
            {
            public:
                InitialLocationModel(PersistentSettings::IPersistentSettingsModel& persistentSettingsModel,
                                     const Eegeo::Space::LatLongAltitude& defaultInterestLocation);
                
                void SetInterestLocation(const Eegeo::Space::LatLongAltitude& lla);
                
                Eegeo::Space::LatLongAltitude GetInterestLocation() const;
                
                bool HasPersistedInterestLocation() const;
            private:
                bool TryGetLocationFromPersistentSettings(Eegeo::Space::LatLongAltitude& lla) const;
            
                PersistentSettings::IPersistentSettingsModel& m_persistentSettingsModel;
                Eegeo::Space::LatLongAltitude m_interestLocation;
                bool m_hasPersistedInterestLocation;
            };
            
        }
    }
}