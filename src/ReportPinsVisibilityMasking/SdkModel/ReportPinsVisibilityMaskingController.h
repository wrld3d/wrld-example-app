// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// std library includes
#include <string>
// eeGeo SDK includes
#include "ICallback.h"
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
            class ReportPinsVisibilityMaskingController
            {
            private:
                bool m_reportPinsExpanded;
                MenuSectionExpandedChangedObserver& m_menuSectionExpandedChangedObserver;
                WorldPins::SdkModel::IWorldPinsScaleController& m_worldPinsScaleController;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                Eegeo::Helpers::TCallback1<ReportPinsVisibilityMaskingController, bool> m_myReportsSectionExpandedChangedHandler;
                Eegeo::Helpers::TCallback0<ReportPinsVisibilityMaskingController> m_visibilityMaskChangedHandler;
                Eegeo::Helpers::TCallback0<ReportPinsVisibilityMaskingController> m_interactionStateChangedHandler;
                Eegeo::Helpers::TCallback0<ReportPinsVisibilityMaskingController> m_interiorModelChangedHandler;
                
            public:
                ReportPinsVisibilityMaskingController(WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController,
                                                      Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                      MenuSectionExpandedChangedObserver& menuSectionExpandedChangedObserver);
                
                ~ReportPinsVisibilityMaskingController();
                
            private:
                void OnMyReportsSectionExpandedChanged(bool& expanded);
                
                void OnVisibilityMaskChanged();
                void OnInteriorStateChanged();
                void OnInteriorModelChanged();
                
                void UpdateReportPinsVisibility();
            };
        }
    }
}