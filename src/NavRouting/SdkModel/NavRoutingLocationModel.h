// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

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
                NavRoutingLocationModel(const std::string& name,
                                        const Eegeo::Space::LatLong& latLon);

                NavRoutingLocationModel(const std::string& name,
                                        const Eegeo::Space::LatLong& latLon,
                                        const bool isIndoors,
                                        const Eegeo::Resources::Interiors::InteriorId& indoorMapId,
                                        const int indoorMapFloorId);

                const std::string& GetName() const;
                const Eegeo::Space::LatLong& GetLatLon() const;
                const bool GetIsIndoors() const;
                const Eegeo::Resources::Interiors::InteriorId& GetIndoorMapId() const;
                const int GetIndoorMapFloorId() const;

            private:

                const std::string m_name;
                const Eegeo::Space::LatLong m_latLon;
                const bool m_isIndoors;
                const Eegeo::Resources::Interiors::InteriorId m_indoorMapId;
                const int m_indoorMapFloorId;
            };
        }
    }
}
