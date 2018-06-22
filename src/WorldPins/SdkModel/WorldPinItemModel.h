// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "WorldPins.h"
#include "Types.h"
//#include "Pins.h"
#include "IWorldPinSelectionHandler.h"
#include "IWorldPinVisibilityStateChangedHandler.h"
#include "WorldPinsInFocusModel.h"
#include "WorldPinFocusData.h"
#include "WorldPinInteriorData.h"
#include "IMarker.h"
#include "SdkModelDomainEventBus.h"


namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            
            class WorldPinItemModel : private Eegeo::NonCopyable
            {
                enum TransitionState
                {
                    StableHidden,
                    TransitionToVisible,
                    StableVisible,
                    TransitionToHidden
                };
                
            public:
                typedef int WorldPinItemModelId;

            private:
                Eegeo::Markers::IMarker* m_pMarker;
                IWorldPinSelectionHandler* m_pSelectionHandler;
                IWorldPinVisibilityStateChangedHandler* m_pVisibilityStateChangedHandler;
                WorldPinsInFocusModel m_focusModel;
                TransitionState m_transitionState;
                float m_transitionStateValue;
                bool m_focusable;
                bool m_interior;
                WorldPinInteriorData m_worldPinInteriorData;
                int m_visibilityMask;
                std::string m_identifier;

            public:
                WorldPinItemModel(Eegeo::Markers::IMarker* pMarker,
                                  IWorldPinSelectionHandler* pSelectionHandler,
                                  IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                  const WorldPinFocusData& worldPinFocusData,
                                  bool interior,
                                  const WorldPinInteriorData& worldPinInteriorData,
                                  int visibilityMask,
                                  std::string identifier);

                ~WorldPinItemModel();

                const WorldPinItemModelId Id() const;

                void SetMarker(Eegeo::Markers::IMarker* pMarker);

                void Select();

                bool IsHidden() const;

                bool IsVisible() const;

                bool IsTransitioning() const;

                float TransitionStateValue() const;

                void Hide();

                void Show();

                void Update(float deltaSeconds);
                
                void Refresh(const std::string& title, const std::string& description, const std::string& ratingsImage, const int reviewCount);

                const IWorldPinsInFocusModel& GetInFocusModel() const;
                
                void SetFocusable(bool focusable);
                
                bool IsFocusable() const;
                
                bool IsInterior() const;
                
                const WorldPinInteriorData& GetInteriorData() const;
                
                int VisibilityMask() const;
                
                void SetVisibilityMask(int visibilityMask);
                
                std::string GetIdentifier() const;
                
            private:
                void SetTransitionState(TransitionState transitionState);
                void UpdateMarkerState();
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
