// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "BidirectionalBus.h"
// App includes
#include "ReportPinsVisibilityMasking.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace ReportPinsVisibilityMasking
    {
        namespace SdkModel
        {
            class ReportPinsVisibilityMaskingModule
            {
            private:
                MenuSectionExpandedChangedObserver* m_pMenuSectionExpandedChangedObserver;
                ReportPinsVisibilityMaskingController* m_pReportPinsVisibilityMaskingController;
            public:
                ReportPinsVisibilityMaskingModule(WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController,
                                                  ExampleAppMessaging::TMessageBus& messageBus);
                
                ~ReportPinsVisibilityMaskingModule();
            };
        }
    }
}