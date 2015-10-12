// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "WorldPins.h"
#include "Pins.h"
#include "IWorldPinSelectionHandler.h"
#include "IWorldPinVisibilityStateChangedHandler.h"
#include "WorldPinsInFocusModel.h"
#include "WorldPinFocusData.h"
#include "WorldPinInteriorData.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            
            class WorldPinItemModel
            {
                enum TransitionState
                {
                    StableHidden,
                    TransitionToVisible,
                    StableVisible,
                    TransitionToHidden
                };
                
            public:
                typedef Eegeo::Pins::TPinId WorldPinItemModelId;

            private:
                WorldPinItemModelId m_id;
                IWorldPinSelectionHandler* m_pSelectionHandler;
                IWorldPinVisibilityStateChangedHandler* m_pVisibilityStateChangedHandler;
                WorldPinsInFocusModel m_focusModel;
                TransitionState m_transitionState;
                float m_transitionStateValue;
                float m_floorHeight;
                bool m_hasFloorHeight;
                bool m_focusable;
                bool m_interior;
                WorldPinInteriorData m_worldPinInteriorData;
                int m_visibilityMask;

            public:
                WorldPinItemModel(const WorldPinItemModelId& id,
                                  IWorldPinSelectionHandler* pSelectionHandler,
                                  IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                  const WorldPinFocusData& worldPinFocusData,
                                  bool interior,
                                  const WorldPinInteriorData& worldPinInteriorData,
                                  int visibilityMask);

                ~WorldPinItemModel();

                const WorldPinItemModelId& Id() const;

                void Select();

                bool IsHidden() const;

                bool IsVisible() const;

                bool IsTransitioning() const;

                float TransitionStateValue() const;
                
                bool NeedsFloorHeight() const;
                
                void SetFloorHeight(float floorHeight);

                void Hide();

                void Show();

                void Update(float deltaSeconds);
                
                void Refresh(const std::string& title, const std::string& description, const std::string& ratingsImage, const int reviewCount);

                const IWorldPinsInFocusModel& GetInFocusModel() const;
                
                bool IsInterior() const;
                
                const WorldPinInteriorData& GetInteriorData() const;
                
                int VisibilityMask() const;
                
                void SetVisibilityMask(int visibilityMask);
            };

            inline bool operator==(const WorldPinItemModel& lhs, const WorldPinItemModel& rhs)
            {
                return lhs.Id() == rhs.Id();
            }
            inline bool operator!=(const WorldPinItemModel& lhs, const WorldPinItemModel& rhs)
            {
                return !operator==(lhs,rhs);
            }
            inline bool operator< (const WorldPinItemModel& lhs, const WorldPinItemModel& rhs)
            {
                return lhs.Id() < rhs.Id();
            }
            inline bool operator> (const WorldPinItemModel& lhs, const WorldPinItemModel& rhs)
            {
                return  operator< (rhs,lhs);
            }
            inline bool operator<=(const WorldPinItemModel& lhs, const WorldPinItemModel& rhs)
            {
                return !operator> (lhs,rhs);
            }
            inline bool operator>=(const WorldPinItemModel& lhs, const WorldPinItemModel& rhs)
            {
                return !operator< (lhs,rhs);
            }
        }
    }
}
