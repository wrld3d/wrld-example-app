// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "BidirectionalBus.h"
// App includes
#include "ReportPinsVisibilityMasking.h"
#include "WorldPins.h"
#include "Interiors.h"

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
                ReportPinsVisibilityMaskingModule(WorldPins::SdkModel::IWorldPinsVisibilityController& worldPinsVisibilityController,
                                                  Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                  ExampleAppMessaging::TMessageBus& messageBus);
                
                ~ReportPinsVisibilityMaskingModule();
            };
        }
    }
}