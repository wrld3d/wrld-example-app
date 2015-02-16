// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InitialExperienceDialogs.h"
#include "InitialExperienceDialogsViewIncludes.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace Dialogs
        {
            namespace View
            {
                class IInitialExperienceDialogsViewModule
                {
                public:
                    virtual ~IInitialExperienceDialogsViewModule() {}
                    
                    virtual InitialExperienceDialogsView& GetDialogsView() const = 0;
                    virtual InitialExperienceDialogsController& GetDialogsController() const = 0;
                    
                };
            }
        }
    }
}
