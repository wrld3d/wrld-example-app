// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "ICallback.h"
#include "Types.h"
// App includes
#include "UserInteraction.h"

//TODO: finish implementing Observer

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            class UserInteractionEnabledObserver : Eegeo::NonCopyable
            {
            private:
                UserInteractionModel& m_userInteractionModel;
                
            public:
                UserInteractionEnabledObserver(UserInteractionModel& userInteractionModel);
            };
        }
    }
}
