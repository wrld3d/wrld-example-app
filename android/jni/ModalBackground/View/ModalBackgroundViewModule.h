// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

//#include "IModalBackgroundViewModule.h"
//#include "AndroidNativeState.h"
//#include "Types.h"
//#include "Modality.h"
//#include "ModalBackgroundViewIncludes.h"
//#include "BidirectionalBus.h"
#include "Module.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            class ModalBackgroundViewModule: public Module
            {
            public:
            	void Register(const TContainerBuilder& builder);
            };
        }
    }
}
