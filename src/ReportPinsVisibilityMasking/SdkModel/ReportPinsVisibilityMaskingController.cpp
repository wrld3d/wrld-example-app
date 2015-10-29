// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReportPinsVisibilityMaskingController.h"

// App includes
#include "MenuSectionExpandedChangedObserver.h"
#include "WorldPinsScaleController.h"
#include "WorldPinVisibility.h"

namespace ExampleApp
{
    namespace ReportPinsVisibilityMasking
    {
        namespace SdkModel
        {
            ReportPinsVisibilityMaskingController::ReportPinsVisibilityMaskingController(
                                                                    WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController,
                                                                    MenuSectionExpandedChangedObserver& menuSectionExpandedChangedObserver)
            : m_worldPinsScaleController(worldPinsScaleController)
            , m_menuSectionExpandedChangedObserver(menuSectionExpandedChangedObserver)
            , m_myReportsSectionExpandedChangedHandler(this, &ReportPinsVisibilityMaskingController::OnMyReportsSectionExpandedChanged)
            , m_visibilityMaskChangedHandler(this, &ReportPinsVisibilityMaskingController::OnVisibilityMaskChanged)
            , m_reportPinsExpanded(false)
            {
                m_menuSectionExpandedChangedObserver.InsertReportPinsExpandedChangedCallback(m_myReportsSectionExpandedChangedHandler);
                m_worldPinsScaleController.InsertVisibilityMaskChangedCallback(m_visibilityMaskChangedHandler);
                UpdateReportPinsVisibility();
            }
            
            ReportPinsVisibilityMaskingController::~ReportPinsVisibilityMaskingController()
            {
                m_worldPinsScaleController.RemoveVisibilityMaskChangedCallback(m_visibilityMaskChangedHandler);
                m_menuSectionExpandedChangedObserver.RemoveReportPinsExpandedChangedCallback(m_myReportsSectionExpandedChangedHandler);
            }
            
            void ReportPinsVisibilityMaskingController::OnMyReportsSectionExpandedChanged(bool& expanded)
            {
                m_reportPinsExpanded = expanded;
                UpdateReportPinsVisibility();
            }
            
            void ReportPinsVisibilityMaskingController::OnVisibilityMaskChanged()
            {
                UpdateReportPinsVisibility();
            }
            
            void ReportPinsVisibilityMaskingController::UpdateReportPinsVisibility()
            {
                const int currentVisibilityMask = m_worldPinsScaleController.GetVisibilityMask();
                const bool allHidden = (currentVisibilityMask == 0);
                const bool userPinSet = ((currentVisibilityMask & WorldPins::SdkModel::WorldPinVisibility::UserPin) != 0);
                if(!allHidden && (userPinSet != m_reportPinsExpanded))
                {
                    if(m_reportPinsExpanded)
                    {
                        int visibilityMask = m_worldPinsScaleController.GetVisibilityMask();
                        visibilityMask = visibilityMask | (WorldPins::SdkModel::WorldPinVisibility::UserPin);
                        m_worldPinsScaleController.SetVisibilityMask(visibilityMask);
                    }
                    else
                    {
                        int visibilityMask = m_worldPinsScaleController.GetVisibilityMask();
                        visibilityMask = visibilityMask & (~WorldPins::SdkModel::WorldPinVisibility::UserPin);
                        m_worldPinsScaleController.SetVisibilityMask(visibilityMask);
                    }
                }
            }
        }
    }
}