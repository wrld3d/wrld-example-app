// Copyright Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include <string>

namespace ExampleApp
{
    namespace WifiInfo
    {
        class IRestrictedBuildingService:public Eegeo::NonCopyable
        {
        public:
            
            virtual ~IRestrictedBuildingService() { };
            
            virtual bool CanAccessBuildingWithCurrentNetwork(std::string interior_id) = 0;
            virtual void ShowAlertMessage() = 0;

        };
    }
}
