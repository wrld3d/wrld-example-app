// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserInteractionEnabledObserver.h"

// App includes
#include "UserInteractionModel.h"

//TODO: finish implementing Observer

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            UserInteractionEnabledObserver::UserInteractionEnabledObserver(UserInteractionModel& userInteractionModel)
            : m_userInteractionModel(userInteractionModel)
            {
                
            }
        }
    }
}