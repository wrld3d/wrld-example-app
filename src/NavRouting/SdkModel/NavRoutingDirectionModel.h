// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorId.h"
#include "LatLongAltitude.h"

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
                                         const std::vector<Eegeo::Space::LatLong>& path);

                NavRoutingDirectionModel(const std::string& name,
                                         const std::string& icon,
                                         const std::string& instruction,
                                         const std::string& nextInstruction,
                                         const std::vector<Eegeo::Space::LatLong>& path,
                                         const bool isIndoors,
                                         const Eegeo::Resources::Interiors::InteriorId& indoorMapId,
                                         const int indoorMapFloorId,
                                         const bool isMultiFloor);

                const std::string& GetName() const;
                const std::string& GetIcon() const;
                const std::string& GetInstruction() const;
                const std::string& GetNextInstruction() const;
                const std::vector<Eegeo::Space::LatLong>& GetPath() const;
                const bool GetIsIndoors() const;
                const Eegeo::Resources::Interiors::InteriorId& GetIndoorMapId() const;
                const int GetIndoorMapFloorId() const;
                const bool GetIsMultiFloor() const;

            private:

                std::string m_name;
                std::string m_icon;
                std::string m_instruction;
                std::string m_nextInstruction;
                std::vector<Eegeo::Space::LatLong> m_path;
                bool m_isIndoors;
                Eegeo::Resources::Interiors::InteriorId m_indoorMapId;
                int m_indoorMapFloorId;
                bool m_isMultiFloor;
            };
        }
    }
}
