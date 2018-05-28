// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingCurrentDirectionUpdatedMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingCurrentDirectionUpdatedMessage::NavRoutingCurrentDirectionUpdatedMessage(const SdkModel::NavRoutingDirectionModel& directionModel)
        : m_directionModel(directionModel)
        {

        }

        const SdkModel::NavRoutingDirectionModel& NavRoutingCurrentDirectionUpdatedMessage::GetDirectionModel() const
        {
            return m_directionModel;
        }
    }
}
