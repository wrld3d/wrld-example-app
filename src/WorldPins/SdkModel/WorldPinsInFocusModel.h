// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IWorldPinsInFocusModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        class WorldPinsInFocusModel : public IWorldPinsInFocusModel
        {
        public:
            WorldPinsInFocusModel();
            
            WorldPinsInFocusModel(int worldPinItemModelId,
                                  const std::string& title,
                                  const std::string& subtitle);
            
            const std::string& GetTitle() const;
            const std::string& GetSubtitle() const;
            const int GetPinId() const;
            
        private:
            
            int m_worldPinItemModelId;
            std::string m_title;
            std::string m_subtitle;
        };
    }
}