// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRoutingDirectionModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingCurrentDirectionUpdatedMessage
        {
        private:
            SdkModel::NavRoutingDirectionModel m_directionModel;

        public:
            NavRoutingCurrentDirectionUpdatedMessage(const SdkModel::NavRoutingDirectionModel& directionModel);

            const SdkModel::NavRoutingDirectionModel& GetDirectionModel() const;
        };
    }
}
