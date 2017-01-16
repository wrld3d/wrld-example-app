// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReportPinsVisibilityMaskingController.h"

// App includes
#include "MenuSectionExpandedChangedObserver.h"
#include "WorldPinsVisibilityController.h"
#include "WorldPinVisibility.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace ReportPinsVisibilityMasking
    {
        namespace SdkModel
        {
            ReportPinsVisibilityMaskingController::ReportPinsVisibilityMaskingController(
                                                                    WorldPins::SdkModel::IWorldPinsVisibilityController& worldPinsVisibilityController,
                                                                    Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                    MenuSectionExpandedChangedObserver& menuSectionExpandedChangedObserver)
            : m_worldPinsVisibilityController(worldPinsVisibilityController)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_menuSectionExpandedChangedObserver(menuSectionExpandedChangedObserver)
            , m_myReportsSectionExpandedChangedHandler(this, &ReportPinsVisibilityMaskingController::OnMyReportsSectionExpandedChanged)
            , m_visibilityMaskChangedHandler(this, &ReportPinsVisibilityMaskingController::OnVisibilityMaskChanged)
            , m_interactionStateChangedHandler(this, &ReportPinsVisibilityMaskingController::OnInteriorStateChanged)
            , m_interiorModelChangedHandler(this, &ReportPinsVisibilityMaskingController::OnInteriorModelChanged)
            , m_reportPinsExpanded(false)
            {
                m_menuSectionExpandedChangedObserver.InsertReportPinsExpandedChangedCallback(m_myReportsSectionExpandedChangedHandler);
                m_worldPinsVisibilityController.InsertVisibilityMaskChangedCallback(m_visibilityMaskChangedHandler);
                m_interiorInteractionModel.RegisterInteractionStateChangedCallback(m_interactionStateChangedHandler);
                m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorModelChangedHandler);
                UpdateReportPinsVisibility();
            }
            
            ReportPinsVisibilityMaskingController::~ReportPinsVisibilityMaskingController()
            {
                m_interiorInteractionModel.UnregisterModelChangedCallback(m_interiorModelChangedHandler);
                m_interiorInteractionModel.UnregisterInteractionStateChangedCallback(m_interactionStateChangedHandler);
                m_worldPinsVisibilityController.RemoveVisibilityMaskChangedCallback(m_visibilityMaskChangedHandler);
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
            
            void ReportPinsVisibilityMaskingController::OnInteriorStateChanged()
            {
                UpdateReportPinsVisibility();
            }
            
            void ReportPinsVisibilityMaskingController::OnInteriorModelChanged()
            {
                UpdateReportPinsVisibility();
            }
            
            void ReportPinsVisibilityMaskingController::UpdateReportPinsVisibility()
            {
                const int currentVisibilityMask = m_worldPinsVisibilityController.GetVisibilityMask();
                const bool allHidden = (currentVisibilityMask == 0);
                const bool userPinSet = ((currentVisibilityMask & WorldPins::SdkModel::WorldPinVisibility::UserPin) != 0);
                const bool viewingExteriorOrCollapsedInterior = !m_interiorInteractionModel.HasInteriorModel() || m_interiorInteractionModel.IsCollapsed();
                const bool canShowReportPins = m_reportPinsExpanded && viewingExteriorOrCollapsedInterior;
                
                if(!allHidden && (userPinSet != canShowReportPins))
                {
                    if(canShowReportPins)
                    {
                        int visibilityMask = m_worldPinsVisibilityController.GetVisibilityMask();
                        visibilityMask = visibilityMask | (WorldPins::SdkModel::WorldPinVisibility::UserPin);
                        m_worldPinsVisibilityController.SetVisibilityMask(visibilityMask);
                    }
                    else
                    {
                        int visibilityMask = m_worldPinsVisibilityController.GetVisibilityMask();
                        visibilityMask = visibilityMask & (~WorldPins::SdkModel::WorldPinVisibility::UserPin);
                        m_worldPinsVisibilityController.SetVisibilityMask(visibilityMask);
                    }
                }
            }
        }
    }
}