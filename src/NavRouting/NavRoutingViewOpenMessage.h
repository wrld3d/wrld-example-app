// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "INavRoutingModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingViewOpenMessage
        {
        private:
            const SdkModel::INavRoutingModel& m_navRoutingModel;

        public:
            NavRoutingViewOpenMessage(const SdkModel::INavRoutingModel& navRoutingModel);

            const SdkModel::INavRoutingModel& GetNavRoutingModel() const;
        };
    }
}
