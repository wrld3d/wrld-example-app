// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinsInFocusModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        WorldPinsInFocusModel::WorldPinsInFocusModel()
        : m_worldPinItemModelId(-1)
        {
            
        }
        
        WorldPinsInFocusModel::WorldPinsInFocusModel(int worldPinItemModelId,
                                                     const std::string& title,
                                                     const std::string& subtitle)
        
        : m_worldPinItemModelId(worldPinItemModelId)
        , m_title(title)
        , m_subtitle(subtitle)
        {
            
        }
        
        const std::string& WorldPinsInFocusModel::GetTitle() const
        {
            return m_title;
        }
        
        const std::string& WorldPinsInFocusModel::GetSubtitle() const
        {
            return m_subtitle;
        }
        
        const int WorldPinsInFocusModel::GetPinId() const
        {
            return m_worldPinItemModelId;
        }
    }
}