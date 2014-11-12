// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "LatLongAltitude.h"
#include "Types.h"
#include "Pins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinModel
        {
        private:
            int m_modelId;
            std::string m_title;
            std::string m_description;
            std::string m_imagePath;
            Eegeo::Space::LatLong m_latLong;
            
        public:
            MyPinModel(int modelId,
                       std::string title,
                       std::string description,
                       std::string imagePath,
                       Eegeo::Space::LatLong latLong);
            
            int Identifier() const { return m_modelId; }
            const std::string& GetTitle() const { return m_title; }
            const std::string& GetDescription() const { return m_description; }
            const std::string& GetImagePath() const { return m_imagePath; }
            const Eegeo::Space::LatLong& GetLatLong() const { return m_latLong; }
        };
        
        inline bool operator==(const MyPinModel& lhs, const MyPinModel& rhs){ return lhs.Identifier() == rhs.Identifier(); }
        inline bool operator!=(const MyPinModel& lhs, const MyPinModel& rhs){return !operator==(lhs,rhs);}
        inline bool operator< (const MyPinModel& lhs, const MyPinModel& rhs){return lhs.Identifier() < rhs.Identifier(); }
        inline bool operator> (const MyPinModel& lhs, const MyPinModel& rhs){return  operator< (rhs,lhs);}
        inline bool operator<=(const MyPinModel& lhs, const MyPinModel& rhs){return !operator> (lhs,rhs);}
        inline bool operator>=(const MyPinModel& lhs, const MyPinModel& rhs){return !operator< (lhs,rhs);}
    }
}