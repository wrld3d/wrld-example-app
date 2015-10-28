// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// std library includes
#include <string>
// eeGeo SDK includes
#include "ICallback.h"
// App includes
#include "ReportPinsVisibilityMasking.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace ReportPinsVisibilityMasking
    {
        namespace SdkModel
        {
            class ReportPinsVisibilityMaskingController
            {
            private:
                bool m_reportPinsExpanded;
                MenuSectionExpandedChangedObserver& m_menuSectionExpandedChangedObserver;
                WorldPins::SdkModel::IWorldPinsScaleController& m_worldPinsScaleController;
                Eegeo::Helpers::TCallback1<ReportPinsVisibilityMaskingController, bool> m_myReportsSectionExpandedChangedHandler;
                Eegeo::Helpers::TCallback0<ReportPinsVisibilityMaskingController> m_visibilityMaskChangedHandler;
                
            public:
                ReportPinsVisibilityMaskingController(WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController,
                                                      MenuSectionExpandedChangedObserver& menuSectionExpandedChangedObserver);
                
                ~ReportPinsVisibilityMaskingController();
                
            private:
                void OnMyReportsSectionExpandedChanged(bool& expanded);
                
                void OnVisibilityMaskChanged();
                
                void UpdateReportPinsVisibility();
            };
        }
    }
}