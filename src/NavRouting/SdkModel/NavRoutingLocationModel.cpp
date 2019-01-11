// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingLocationModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingLocationModel::NavRoutingLocationModel()
            : m_name("")
            , m_latLon(Eegeo::Space::LatLong(0,0))
            , m_isIndoors(false)
            , m_indoorMapId(Eegeo::Resources::Interiors::InteriorId())
            , m_indoorMapFloorId(0)
            {

            }

            NavRoutingLocationModel::NavRoutingLocationModel(const std::string& name,
                                                             const Eegeo::Space::LatLong& latLon)
            : NavRoutingLocationModel(name, latLon, false, Eegeo::Resources::Interiors::InteriorId(), 0)
            {

            }

            NavRoutingLocationModel::NavRoutingLocationModel(const std::string& name,
                                                             const Eegeo::Space::LatLong& latLon,
                                                             const bool isIndoors,
                                                             const Eegeo::Resources::Interiors::InteriorId& indoorMapId,
                                                             const int indoorMapFloorId)
            : m_name(name)
            , m_latLon(latLon)
            , m_isIndoors(isIndoors)
            , m_indoorMapId(indoorMapId)
            , m_indoorMapFloorId(indoorMapFloorId)
            {

            }

            NavRoutingLocationModel::NavRoutingLocationModel(const std::string& name,
                                                             const Eegeo::Space::LatLong& latLon,
                                                             const bool isIndoors,
                                                             const Eegeo::Resources::Interiors::InteriorId& indoorMapId,
                                                             const int indoorMapFloorId,
                                                             const std::vector<std::string>& entityIds,
                                                             const Eegeo::v4& highlightColor)
            : m_name(name)
            , m_latLon(latLon)
            , m_isIndoors(isIndoors)
            , m_indoorMapId(indoorMapId)
            , m_indoorMapFloorId(indoorMapFloorId)
            , m_entityIds(entityIds)
            , m_highlightColor(highlightColor)
            {

            }

            const std::string& NavRoutingLocationModel::GetName() const
            {
                return m_name;
            }

            const Eegeo::Space::LatLong& NavRoutingLocationModel::GetLatLon() const
            {
                return m_latLon;
            }

            const bool NavRoutingLocationModel::GetIsIndoors() const
            {
                return m_isIndoors;
            }

            const Eegeo::Resources::Interiors::InteriorId& NavRoutingLocationModel::GetIndoorMapId() const
            {
                return m_indoorMapId;
            }

            const int NavRoutingLocationModel::GetIndoorMapFloorId() const
            {
                return m_indoorMapFloorId;
            }

            const std::vector<std::string>& NavRoutingLocationModel::GetEntityIds() const
            {
                return m_entityIds;
            }

            const Eegeo::v4& NavRoutingLocationModel::GetHighlightColor() const
            {
                return m_highlightColor;
            }
        }
    }
}
