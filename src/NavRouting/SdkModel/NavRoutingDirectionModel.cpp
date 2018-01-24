// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingDirectionModel.h"
#include "NavRouting.h"

#include <sstream>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
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
                                       "",
                                       false,
                                       0,
                                       "")
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
                                                               const std::string& indoorMapFloorName,
                                                               const bool isMultiFloor,
                                                               const int nextIndoorMapFloorId,
                                                               const std::string& nextIndoorMapFloorName,
                                                               const bool isUsingPlaceHolders)
            : m_name(name)
            , m_icon(icon)
            , m_instruction(instruction)
            , m_nextInstruction(nextInstruction)
            , m_path(path)
            , m_distance(distance)
            , m_isIndoors(isIndoors)
            , m_indoorMapId(indoorMapId)
            , m_indoorMapFloorId(indoorMapFloorId)
            , m_indoorMapFloorName(indoorMapFloorName)
            , m_isMultiFloor(isMultiFloor)
            , m_nextIndoorMapFloorId(nextIndoorMapFloorId)
            , m_nextIndoorMapFloorName(nextIndoorMapFloorName)
            , m_isUsingPlaceHolders(isUsingPlaceHolders)
            {
                std::ostringstream oss;
                oss << (int) m_distance;
                m_keyMappings[InstructionTokens::Distance] = oss.str();
                m_keyMappings[InstructionTokens::FloorName] = m_indoorMapFloorName;
                m_keyMappings[InstructionTokens::NextFloorName] = m_nextIndoorMapFloorName;
            }

            const std::string NavRoutingDirectionModel::GetName() const
            {
                return GetReadableString(m_name);
            }

            const std::string& NavRoutingDirectionModel::GetIcon() const
            {
                return m_icon;
            }

            const std::string NavRoutingDirectionModel::GetInstruction() const
            {
                return GetReadableString(m_instruction);
            }

            const std::string NavRoutingDirectionModel::GetNextInstruction() const
            {
                return GetReadableString(m_nextInstruction);
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
                std::ostringstream oss;
                oss << (int) m_distance;
                m_keyMappings[InstructionTokens::Distance] = oss.str();
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

            void NavRoutingDirectionModel::SetIndoorMapFloorName(const std::string& indoorMapFloorName)
            {
                m_indoorMapFloorName = indoorMapFloorName;
                m_keyMappings[InstructionTokens::FloorName] = m_indoorMapFloorName;
            }

            const std::string& NavRoutingDirectionModel::GetIndoorMapFloorName() const
            {
                return m_indoorMapFloorName;
            }

            const bool NavRoutingDirectionModel::GetIsMultiFloor() const
            {
                return m_isMultiFloor;
            }

            const int NavRoutingDirectionModel::GetNextIndoorMapFloorId() const
            {
                return m_nextIndoorMapFloorId;
            }

            void NavRoutingDirectionModel::SetNextIndoorMapFloorName(const std::string& indoorMapFloorName)
            {
                m_nextIndoorMapFloorName = indoorMapFloorName;
                m_keyMappings[InstructionTokens::NextFloorName] = m_nextIndoorMapFloorName;
            }

            const std::string& NavRoutingDirectionModel::GetNextIndoorMapFloorName() const
            {
                return m_nextIndoorMapFloorName;
            }

            void NavRoutingDirectionModel::SetIsUsingPlaceHolders(bool isUsingPlaceHolders)
            {
                m_isUsingPlaceHolders = isUsingPlaceHolders;
            }

            const bool NavRoutingDirectionModel::GetIsUsingPlaceHolders() const
            {
                return m_isUsingPlaceHolders;
            }

            std::string NavRoutingDirectionModel::GetReadableString(const std::string& formatString) const
            {
                std::string readableString = formatString;
                for (auto it = m_keyMappings.begin(); it != m_keyMappings.end(); ++it)
                {
                    const std::string& token = it->first;
                    const std::string& value = it->second;

                    std::size_t pos = readableString.find(token);
                    if (pos != std::string::npos)
                    {
                        readableString.replace(pos, token.length(), value);
                    }
                }

                return readableString;
            }
        }
    }
}
