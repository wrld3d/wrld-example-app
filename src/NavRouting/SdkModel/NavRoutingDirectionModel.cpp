// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingDirectionModel.h"

#include <sstream>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            std::string GetStringWithDistance(const std::string& formatString, double distance)
            {
                std::string distFormat = "<dist>";
                std::size_t pos = formatString.find(distFormat);
                if (pos == std::string::npos)
                {
                    return formatString;
                }
                else
                {
                    std::ostringstream oss;
                    oss << (int) distance;
                    std::string stringWithDistance = formatString;
                    stringWithDistance.replace(pos, distFormat.length(), oss.str());
                    return stringWithDistance;
                }
            }

            NavRoutingDirectionModel::NavRoutingDirectionModel(const std::string& name,
                                                               const std::string& icon,
                                                               const std::string& instruction,
                                                               const std::string& nextInstruction,
                                                               const std::vector<Eegeo::Space::LatLong>& path,
                                                               const double distance)
            : NavRoutingDirectionModel(name,
                                       icon,
                                       instruction,
                                       nextInstruction,
                                       path,
                                       distance,
                                       false,
                                       Eegeo::Resources::Interiors::InteriorId(),
                                       0,
                                       false)
            {

            }

            NavRoutingDirectionModel::NavRoutingDirectionModel(const std::string& name,
                                                               const std::string& icon,
                                                               const std::string& instruction,
                                                               const std::string& nextInstruction,
                                                               const std::vector<Eegeo::Space::LatLong>& path,
                                                               const double distance,
                                                               const bool isIndoors,
                                                               const Eegeo::Resources::Interiors::InteriorId& indoorMapId,
                                                               const int indoorMapFloorId,
                                                               const bool isMultiFloor)
            : m_name(name)
            , m_icon(icon)
            , m_instruction(instruction)
            , m_nextInstruction(nextInstruction)
            , m_path(path)
            , m_distance(distance)
            , m_isIndoors(isIndoors)
            , m_indoorMapId(indoorMapId)
            , m_indoorMapFloorId(indoorMapFloorId)
            , m_isMultiFloor(isMultiFloor)
            {

            }

            const std::string NavRoutingDirectionModel::GetName() const
            {
                return GetStringWithDistance(m_name, m_distance);
            }

            const std::string& NavRoutingDirectionModel::GetIcon() const
            {
                return m_icon;
            }

            const std::string NavRoutingDirectionModel::GetInstruction() const
            {
                return GetStringWithDistance(m_instruction, m_distance);
            }

            const std::string NavRoutingDirectionModel::GetNextInstruction() const
            {
                return GetStringWithDistance(m_nextInstruction, m_distance);
            }

            const std::vector<Eegeo::Space::LatLong>& NavRoutingDirectionModel::GetPath() const
            {
                return m_path;
            }

            const double NavRoutingDirectionModel::GetDistance() const
            {
                return m_distance;
            }

            void NavRoutingDirectionModel::SetDistance(double distance)
            {
                m_distance = distance;
            }

            const bool NavRoutingDirectionModel::GetIsIndoors() const
            {
                return m_isIndoors;
            }

            const Eegeo::Resources::Interiors::InteriorId& NavRoutingDirectionModel::GetIndoorMapId() const
            {
                return m_indoorMapId;
            }

            const int NavRoutingDirectionModel::GetIndoorMapFloorId() const
            {
                return m_indoorMapFloorId;
            }

            const bool NavRoutingDirectionModel::GetIsMultiFloor() const
            {
                return m_isMultiFloor;
            }
        }
    }
}
