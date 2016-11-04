// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuItemModel.h"
#include "Types.h"
#include "DirectionsMenuJsonSerializer.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace SdkModel
        {
            DirectionsMenuItemModel::DirectionsMenuItemModel(const std::string& identifier,
                                         const std::string& name,
                                         const std::string& details,
                                         const std::string& icon,                                                   const std::string& duration,
                                         IMenuOption* pOption)
            : MenuItemModel(identifier, name, details, icon, pOption)
            , m_routeDuration(duration)
            {
            }

            DirectionsMenuItemModel::~DirectionsMenuItemModel()
            {

            }

            std::string DirectionsMenuItemModel::SerializeJson() const
            {
                return SerialiseMenuItemToJson(*this);
            }
            
            const std::string& DirectionsMenuItemModel::Duration() const
            {
                return m_routeDuration;
            }
        }
    }
}
