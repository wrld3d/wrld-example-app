// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "Types.h"
#include "NavRouting.h"
#include "RouteService.h"
#include "IRoutingWebservice.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingLocationModel
            {
            public:
                NavRoutingLocationModel();

                NavRoutingLocationModel(const std::string& name,
                                        const Eegeo::Space::LatLong& latLon);

                NavRoutingLocationModel(const std::string& name,
                                        const Eegeo::Space::LatLong& latLon,
                                        const bool isIndoors,
                                        const Eegeo::Resources::Interiors::InteriorId& indoorMapId,
                                        const int indoorMapFloorId);

                NavRoutingLocationModel(const std::string& name,
                                        const Eegeo::Space::LatLong& latLon,
                                        const bool isIndoors,
                                        const Eegeo::Resources::Interiors::InteriorId& indoorMapId,
                                        const int indoorMapFloorId,
                                        const std::vector<std::string>& entityIds,
                                        const Eegeo::v4& highlightColor);

                const std::string& GetName() const;
                const Eegeo::Space::LatLong& GetLatLon() const;
                const bool GetIsIndoors() const;
                const Eegeo::Resources::Interiors::InteriorId& GetIndoorMapId() const;
                const int GetIndoorMapFloorId() const;
                const std::vector<std::string>& GetEntityIds() const;
                const Eegeo::v4& GetHighlightColor() const;

            private:

                std::string m_name;
                Eegeo::Space::LatLong m_latLon;
                bool m_isIndoors;
                Eegeo::Resources::Interiors::InteriorId m_indoorMapId;
                int m_indoorMapFloorId;
                std::vector<std::string> m_entityIds;
                Eegeo::v4 m_highlightColor;
            };
        }
    }
}
