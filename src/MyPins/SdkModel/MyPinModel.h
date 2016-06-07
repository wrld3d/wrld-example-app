// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "InteriorId.h"
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
                std::string m_vendor;
                std::string m_ratingsImage;
                std::string m_pinIconKey;
                int m_reviewCount;
                Eegeo::Space::LatLong m_latLong;
                float m_heightAboveTerrainMetres;
                bool m_interior;
                Eegeo::Resources::Interiors::InteriorId m_buildingId;
                int m_floor;

            public:
                const static int CurrentVersion;
                
                MyPinModel();

                MyPinModel(int version,
                           TPinIdType modelId,
                           const std::string& title,
                           const std::string& description,
                           const std::string& vendor,
                           const std::string& ratingsImage,
                           const std::string& pinIconKey,
                           int reviewCount,
                           const Eegeo::Space::LatLong& latLong,
                           float heightAboveTerrainMetresbool,
                           bool interior,
                           const Eegeo::Resources::Interiors::InteriorId& buildingId,
                           int floor);
                
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
                
                const std::string& GetVendor() const
                {
                    return m_vendor;
                }
                
                const std::string& GetRatingsImage() const
                {
                    return m_ratingsImage;
                }
                
                const int GetReviewsCount() const
                {
                    return m_reviewCount;
                }
                
                std::string GetPinIconKey() const
                {
                    return m_pinIconKey;
                }
                
                const Eegeo::Space::LatLong& GetLatLong() const
                {
                    return m_latLong;
                }
                
                const float GetHeightAboveTerrainMetres() const
                {
                    return m_heightAboveTerrainMetres;
                }
                
                bool IsInterior() const
                {
                    return m_interior;
                }
                
                const Eegeo::Resources::Interiors::InteriorId& GetBuildingId() const
                {
                    return m_buildingId;
                }
                
                int GetFloor() const
                {
                    return m_floor;
                }
                
                void Update(const std::string& title,
                            const std::string& description,
                            const std::string& ratingsImage,
                            int reviewCount)
                {
                    m_version = CurrentVersion;
                    m_title = title;
                    m_description = description;
                    m_ratingsImage = ratingsImage;
                    m_reviewCount = reviewCount;
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
