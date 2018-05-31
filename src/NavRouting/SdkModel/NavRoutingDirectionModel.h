// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorId.h"
#include "LatLongAltitude.h"

#include <unordered_map>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingDirectionModel
            {
            public:
                NavRoutingDirectionModel(const std::string& name,
                                         const std::string& icon,
                                         const std::string& instruction,
                                         const std::string& nextInstruction,
                                         const std::vector<Eegeo::Space::LatLong>& path,
                                         const double distance);

                NavRoutingDirectionModel(const std::string& name,
                                         const std::string& icon,
                                         const std::string& instruction,
                                         const std::string& nextInstruction,
                                         const std::vector<Eegeo::Space::LatLong>& path,
                                         const double distance,
                                         const bool isIndoors,
                                         const Eegeo::Resources::Interiors::InteriorId& indoorMapId,
                                         const int indoorMapFloorId,
                                         const std::string& indoorMapFloorName,
                                         const bool isMultiFloor,
                                         const int nextIndoorMapFloorId,
                                         const std::string& nextIndoorMapFloorName,
                                         const bool isUsingPlaceHolders = true);

                const std::string GetName() const;
                const std::string& GetIcon() const;
                const std::string GetInstruction() const;
                const std::string GetNextInstruction() const;
                const std::vector<Eegeo::Space::LatLong>& GetPath() const;
                const double GetDistance() const;
                void SetDistance(double distance);
                const bool GetIsIndoors() const;
                const Eegeo::Resources::Interiors::InteriorId& GetIndoorMapId() const;
                const int GetIndoorMapFloorId() const;
                void SetIndoorMapFloorName(const std::string& indoorMapFloorName);
                const std::string& GetIndoorMapFloorName() const;
                const bool GetIsMultiFloor() const;
                const int GetNextIndoorMapFloorId() const;
                void SetNextIndoorMapFloorName(const std::string& indoorMapFloorName);
                const std::string& GetNextIndoorMapFloorName() const;
                void SetIsUsingPlaceHolders(bool isUsingPlaceHolders);
                const bool GetIsUsingPlaceHolders() const;

            private:

                std::string m_name;
                std::string m_icon;
                std::string m_instruction;
                std::string m_nextInstruction;
                std::vector<Eegeo::Space::LatLong> m_path;
                double m_distance;
                bool m_isIndoors;
                Eegeo::Resources::Interiors::InteriorId m_indoorMapId;
                int m_indoorMapFloorId;
                std::string m_indoorMapFloorName;
                bool m_isMultiFloor;
                int m_nextIndoorMapFloorId;
                std::string m_nextIndoorMapFloorName;
                bool m_isUsingPlaceHolders;

                std::unordered_map<std::string, std::string> m_keyMappings;
                std::string GetReadableString(const std::string& formatString) const;
            };
        }
    }
}
