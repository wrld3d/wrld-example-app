// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "Pins.h"
#include "IWorldPinSelectionHandler.h"

namespace ExampleApp
{
    namespace WorldPins
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
            TransitionState m_transitionState;
            float m_transitionStateValue;
            
        public:
            WorldPinItemModel(const WorldPinItemModelId& id,
                              IWorldPinSelectionHandler* pSelectionHandler);
            
            ~WorldPinItemModel();
            
            const WorldPinItemModelId& Id() const;
            
            void Select();
            
            bool IsHidden() const;
            
            bool IsVisible() const;
            
            bool IsTransitioning() const;
            
            float TransitionStateValue() const;
            
            void Hide();
            
            void Show();
            
            void Update(float deltaSeconds);
        };
        
        inline bool operator==(const WorldPinItemModel& lhs, const WorldPinItemModel& rhs){ return lhs.Id() == rhs.Id(); }
        inline bool operator!=(const WorldPinItemModel& lhs, const WorldPinItemModel& rhs){return !operator==(lhs,rhs);}
        inline bool operator< (const WorldPinItemModel& lhs, const WorldPinItemModel& rhs){return lhs.Id() < rhs.Id(); }
        inline bool operator> (const WorldPinItemModel& lhs, const WorldPinItemModel& rhs){return  operator< (rhs,lhs);}
        inline bool operator<=(const WorldPinItemModel& lhs, const WorldPinItemModel& rhs){return !operator> (lhs,rhs);}
        inline bool operator>=(const WorldPinItemModel& lhs, const WorldPinItemModel& rhs){return !operator< (lhs,rhs);}
    }
}
