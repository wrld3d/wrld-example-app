// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingDirectionModel.h"

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
                                                               const std::vector<Eegeo::Space::LatLong>& path)
            : NavRoutingDirectionModel(name,
                                       icon,
                                       instruction,
                                       nextInstruction,
                                       path,
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
                                                               const bool isIndoors,
                                                               const Eegeo::Resources::Interiors::InteriorId& indoorMapId,
                                                               const int indoorMapFloorId,
                                                               const bool isMultiFloor)
            : m_name(name)
            , m_icon(icon)
            , m_instruction(instruction)
            , m_nextInstruction(nextInstruction)
            , m_path(path)
            , m_isIndoors(isIndoors)
            , m_indoorMapId(indoorMapId)
            , m_indoorMapFloorId(indoorMapFloorId)
            , m_isMultiFloor(isMultiFloor)
            {

            }

            const std::string& NavRoutingDirectionModel::GetName() const
            {
                return m_name;
            }

            const std::string& NavRoutingDirectionModel::GetIcon() const
            {
                return m_icon;
            }

            const std::string& NavRoutingDirectionModel::GetInstruction() const
            {
                return m_instruction;
            }

            const std::string& NavRoutingDirectionModel::GetNextInstruction() const
            {
                return m_nextInstruction;
            }

            const std::vector<Eegeo::Space::LatLong>& NavRoutingDirectionModel::GetPath() const
            {
                return m_path;
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
