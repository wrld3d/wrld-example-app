// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinItemModel.h"
#include "Types.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            namespace
            {
                const float TransitionSeconds = 0.25f;
                const float TransitionDeltaPerSeconds = 1.f / TransitionSeconds;
            }

            WorldPinItemModel::WorldPinItemModel(const WorldPinItemModelId& id,
                                                 IWorldPinSelectionHandler* pSelectionHandler,
                                                 IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                                 const WorldPinFocusData& worldPinFocusData,
                                                 bool interior,
                                                 const WorldPinInteriorData& worldPinInteriorData,
                                                 int visibilityMask)
                : m_id(id)
                , m_pSelectionHandler(pSelectionHandler)
                , m_pVisibilityStateChangedHandler(pVisibilityStateChangedHandler)
                , m_focusModel(m_id, worldPinFocusData.title, worldPinFocusData.subtitle, worldPinFocusData.ratingsImage, worldPinFocusData.reviewCount)
                , m_transitionState(StableHidden)
                , m_transitionStateValue(0.f)
                , m_interior(interior)
                , m_worldPinInteriorData(worldPinInteriorData)
                , m_floorHeight(0.0f)
                , m_hasFloorHeight(false)
                , m_visibilityMask(visibilityMask)
            {
                Eegeo_ASSERT(m_pSelectionHandler != NULL, "WorldPinItemModel must be provided with a non-null selection handler.")
            }

            WorldPinItemModel::~WorldPinItemModel()
            {
            }

            const WorldPinItemModel::WorldPinItemModelId& WorldPinItemModel::Id() const
            {
                return m_id;
            }

            void WorldPinItemModel::Select()
            {
                m_pSelectionHandler->SelectPin();
            }

            bool WorldPinItemModel::IsHidden() const
            {
                return m_transitionState == StableHidden;
            }

            bool WorldPinItemModel::IsVisible() const
            {
                return m_transitionState == StableVisible;
            }

            bool WorldPinItemModel::IsTransitioning() const
            {
                return !IsHidden() && !IsVisible();
            }

            void WorldPinItemModel::Hide()
            {
                if(m_transitionState != StableHidden)
                {
                    m_transitionState = TransitionToHidden;
                }
            }

            void WorldPinItemModel::Show()
            {
                if(m_transitionState != StableVisible)
                {
                    m_transitionState = TransitionToVisible;
                }
            }

            float WorldPinItemModel::TransitionStateValue() const
            {
                return m_transitionStateValue;
            }
            
            bool WorldPinItemModel::NeedsFloorHeight() const
            {
                return m_interior && (!m_hasFloorHeight);
            }
            
            void WorldPinItemModel::SetFloorHeight(float floorHeight)
            {
                m_floorHeight = floorHeight;
                m_hasFloorHeight = true;
            }
            
            void WorldPinItemModel::Refresh(const std::string& title, const std::string& description, const std::string& ratingsImage, const int reviewCount)
            {
                m_focusModel.Refresh(title, description, ratingsImage, reviewCount);
            }

            void WorldPinItemModel::Update(float deltaSeconds)
            {
                if(m_transitionState == TransitionToHidden)
                {
                    m_transitionStateValue -= (deltaSeconds * TransitionDeltaPerSeconds);

                    if(m_transitionStateValue <= 0.f)
                    {
                        if(m_transitionState != StableHidden && m_pVisibilityStateChangedHandler != NULL)
                        {
                            m_pVisibilityStateChangedHandler->HandlePinBecameFullyInvisible();
                        }
                        
                        m_transitionStateValue = 0.f;
                        m_transitionState = StableHidden;
                    }
                }
                else if(m_transitionState == TransitionToVisible)
                {
                    m_transitionStateValue += (deltaSeconds * TransitionDeltaPerSeconds);

                    if(m_transitionStateValue >= 1.f)
                    {
                        if(m_transitionState != StableVisible && m_pVisibilityStateChangedHandler != NULL)
                        {
                            m_pVisibilityStateChangedHandler->HandlePinBecameFullyVisible();
                        }
                        
                        m_transitionStateValue = 1.f;
                        m_transitionState = StableVisible;
                    }
                }
            }

            const IWorldPinsInFocusModel& WorldPinItemModel::GetInFocusModel() const
            {
                return m_focusModel;
            }
            
            bool WorldPinItemModel::IsInterior() const
            {
                return m_interior;
            }
            
            const WorldPinInteriorData& WorldPinItemModel::GetInteriorData() const
            {
                return m_worldPinInteriorData;
            }
            
            int WorldPinItemModel::VisibilityMask() const
            {
                return m_visibilityMask;
            }
            
            void WorldPinItemModel::SetVisibilityMask(int visibilityMask)
            {
                m_visibilityMask = visibilityMask;
            }
        }
    }
}
