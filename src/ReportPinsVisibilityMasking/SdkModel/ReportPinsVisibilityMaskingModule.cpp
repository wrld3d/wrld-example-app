// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReportPinsVisibilityMaskingModule.h"

//eeGeo SDK includes
#include "Types.h"
//App includes
#include "MenuSectionExpandedChangedObserver.h"
#include "ReportPinsVisibilityMaskingController.h"

namespace ExampleApp
{
    namespace ReportPinsVisibilityMasking
    {
        namespace SdkModel
        {
            ReportPinsVisibilityMaskingModule::ReportPinsVisibilityMaskingModule(WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController,
                                                                                 Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                 ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pMenuSectionExpandedChangedObserver = Eegeo_NEW(MenuSectionExpandedChangedObserver)(messageBus);
                m_pReportPinsVisibilityMaskingController = Eegeo_NEW(ReportPinsVisibilityMaskingController)(worldPinsScaleController,
                                                                                                            interiorInteractionModel,
                                                                                                            *m_pMenuSectionExpandedChangedObserver);
            }
            
            ReportPinsVisibilityMaskingModule::~ReportPinsVisibilityMaskingModule()
            {
                Eegeo_DELETE m_pReportPinsVisibilityMaskingController;
                Eegeo_DELETE m_pMenuSectionExpandedChangedObserver;
            }
        }
    }
}