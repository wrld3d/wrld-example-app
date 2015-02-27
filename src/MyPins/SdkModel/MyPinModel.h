// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "LatLongAltitude.h"
#include "Types.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinModel
            {
            public:
                typedef int TPinIdType;
            
            private:
                int m_version;
                TPinIdType m_modelId;
                std::string m_title;
                std::string m_description;
                int m_sdkMapPinIconIndex;
                Eegeo::Space::LatLong m_latLong;

            public:
                const static int CurrentVersion;
                
                MyPinModel();

                MyPinModel(int version,
                           TPinIdType modelId,
                           const std::string& title,
                           const std::string& description,
                           int sdkMapPinIconIndex,
                           const Eegeo::Space::LatLong& latLong);
                
                int Version() const
                {
                    return m_version;
                }
                
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
