// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingViewOpenMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingViewOpenMessage::NavRoutingViewOpenMessage(const SdkModel::INavRoutingModel& navRoutingModel)
        : m_navRoutingModel(navRoutingModel)
        {

        }

        const SdkModel::INavRoutingModel& NavRoutingViewOpenMessage::GetNavRoutingModel() const
        {
            return m_navRoutingModel;
        }
    }
}
