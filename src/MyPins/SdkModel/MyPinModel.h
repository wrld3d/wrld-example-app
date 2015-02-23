// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "LatLongAltitude.h"
#include "Types.h"
#include "MyPinsSemanticPinType.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinModel
            {
            private:
                int m_modelId;
                std::string m_title;
                std::string m_description;
                int m_sdkMapPinIconIndex;
                Eegeo::Space::LatLong m_latLong;
                MyPinsSemanticPinType m_semanticPinType;
                std::string m_pinTypeMetadata;

            public:
                MyPinModel();

                MyPinModel(int modelId,
                           const std::string& title,
                           const std::string& description,
                           int sdkMapPinIconIndex,
                           const Eegeo::Space::LatLong& latLong,
                           const MyPinsSemanticPinType& semanticPinType,
                           const std::string& pinTypeMetadata);

                int Identifier() const
                {
                    return m_modelId;
                }
                
                const std::string& GetTitle() const
                {
                    return m_title;
                }
                
                const std::string& GetDescription() const
                {
                    return m_description;
                }
                
                int GetSdkMapPinIconIndexIcon() const
                {
                    return m_sdkMapPinIconIndex;
                }
                
                const MyPinsSemanticPinType& GetSemanticPinType() const
                {
                    return m_semanticPinType;
                }
                
                const std::string& GetTypeMetadata() const
                {
                    return m_pinTypeMetadata;
                }
                
                const Eegeo::Space::LatLong& GetLatLong() const
                {
                    return m_latLong;
                }
            };

            inline bool operator==(const MyPinModel& lhs, const MyPinModel& rhs)
            {
                return lhs.Identifier() == rhs.Identifier();
            }
            
            inline bool operator!=(const MyPinModel& lhs, const MyPinModel& rhs)
            {
                return !operator==(lhs,rhs);
            }
            
            inline bool operator< (const MyPinModel& lhs, const MyPinModel& rhs)
            {
                return lhs.Identifier() < rhs.Identifier();
            }
            
            inline bool operator> (const MyPinModel& lhs, const MyPinModel& rhs)
            {
                return  operator< (rhs,lhs);
            }
            
            inline bool operator<=(const MyPinModel& lhs, const MyPinModel& rhs)
            {
                return !operator> (lhs,rhs);
            }
            
            inline bool operator>=(const MyPinModel& lhs, const MyPinModel& rhs)
            {
                return !operator< (lhs,rhs);
            }
        }
    }
}
