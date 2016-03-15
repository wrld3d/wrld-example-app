// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExpandedModeObserver.h"
#include "InteriorInteractionModel.h"
#include "IWorldPinsScaleController.h"
#include "WorldPinVisibility.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace
            {
                const int WorldPinVisibilityMaskInExpandedMode = WorldPins::SdkModel::WorldPinVisibility::MeetingRoom;
            }
            
            InteriorExpandedModeObserver::InteriorExpandedModeObserver(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                       WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController)
            : m_interiorInteractionModel(interiorInteractionModel)
            , m_worldPinsScaleController(worldPinsScaleController)
            , m_expanded(!m_interiorInteractionModel.IsCollapsed())
            , m_interactionStateChangedCallback(this, &InteriorExpandedModeObserver::OnInteractionStateChanged)
            , m_previouslyCachedVisibilityMask(0)
            {
                m_interiorInteractionModel.RegisterInteractionStateChangedCallback(m_interactionStateChangedCallback);
            }
            
            InteriorExpandedModeObserver::~InteriorExpandedModeObserver()
            {
                m_interiorInteractionModel.UnregisterInteractionStateChangedCallback(m_interactionStateChangedCallback);
            }
            
            void InteriorExpandedModeObserver::OnInteractionStateChanged()
            {
                bool isExpanded = !m_interiorInteractionModel.IsCollapsed();
                SetExpanded(isExpanded);
            }
            
            void InteriorExpandedModeObserver::SetExpanded(bool isExpanded)
            {
                if(isExpanded != m_expanded)
                {
                    if(isExpanded)
                    {
                        m_previouslyCachedVisibilityMask = m_worldPinsScaleController.GetVisibilityMask();
                        m_worldPinsScaleController.SetVisibilityMask(WorldPinVisibilityMaskInExpandedMode);
                    }
                    else
                    {
                        m_worldPinsScaleController.SetVisibilityMask(m_previouslyCachedVisibilityMask);
                    }
                    
                    m_expanded = isExpanded;
                }
            }
            
            
        }
    }
}