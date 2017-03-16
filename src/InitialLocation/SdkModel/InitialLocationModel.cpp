// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InitialLocationModel.h"
#include "LatLongAltitude.h"
#include "IPersistentSettingsModel.h"

#include "TimeHelpers.h"

namespace ExampleApp
{
    namespace InitialLocation
    {
        namespace SdkModel
        {
        
            namespace
            {
                const std::string InitialLocation_LatitudeDegrees_Key = "InitialLocation_LatitudeDegrees_Key";
                const std::string InitialLocation_LongitudeDegrees_Key = "InitialLocation_LongitudeDegrees_Key";
                const std::string InitialLocation_InterestAltitdue_Key = "InitialLocation_InterestAltitdue_Key";
            }
            

            
            
            
            InitialLocationModel::InitialLocationModel(PersistentSettings::IPersistentSettingsModel& persistentSettingsModel,
                                                       const Eegeo::Space::LatLongAltitude& defaultInterestLocation)
            : m_persistentSettingsModel(persistentSettingsModel)
            , m_interestLocation(defaultInterestLocation)
            , m_hasPersistedInterestLocation(false)
            {
                Eegeo::Space::LatLongAltitude lla(0.0, 0.0, 0.0);
                if (TryGetLocationFromPersistentSettings(lla))
                {
                    m_hasPersistedInterestLocation = true;
                    m_interestLocation = lla;
                }
            }
                
            void InitialLocationModel::SetInterestLocation(const Eegeo::Space::LatLongAltitude& lla)
            {
                m_interestLocation = lla;
                
                m_persistentSettingsModel.SetValue("InitialLocation_LatitudeDegrees_Key", m_interestLocation.GetLatitudeInDegrees());
                m_persistentSettingsModel.SetValue("InitialLocation_LongitudeDegrees_Key", m_interestLocation.GetLongitudeInDegrees());
                m_persistentSettingsModel.SetValue("InitialLocation_InterestAltitdue_Key", m_interestLocation.GetAltitude());
            }
                
            Eegeo::Space::LatLongAltitude InitialLocationModel::GetInterestLocation() const
            {
                return m_interestLocation;
            }
            
            bool InitialLocationModel::HasPersistedInterestLocation() const
            {
                return m_hasPersistedInterestLocation;
            }
            
            bool InitialLocationModel::TryGetLocationFromPersistentSettings(Eegeo::Space::LatLongAltitude& lla) const
            {
                double latDegrees;
                double longDegrees;
                double interestAltitude;
                bool error = false;
                if (!m_persistentSettingsModel.TryGetValue("InitialLocation_LatitudeDegrees_Key", latDegrees))
                {
                    error = true;
                }
                if (!m_persistentSettingsModel.TryGetValue("InitialLocation_LongitudeDegrees_Key", longDegrees))
                {
                    error = true;
                }
                if (!m_persistentSettingsModel.TryGetValue("InitialLocation_InterestAltitdue_Key", interestAltitude))
                {
                    error = true;
                }
                
                if (!error)
                {
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(latDegrees, longDegrees, interestAltitude);
                }
                else
                {
                    lla = Eegeo::Space::LatLongAltitude(0.0, 0.0, 0.0);
                }
                
                return !error;
            }

            
        }
    }
}