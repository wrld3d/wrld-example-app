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
            unsigned int m_modelId;
            std::string m_title;
            std::string m_description;
            std::string m_imagePath;
            Eegeo::Space::LatLong m_latLong;
            bool m_shouldShare;
            
        public:
            MyPinModel(unsigned int modelId,
                       std::string title,
                       std::string description,
                       std::string imagePath,
                       Eegeo::Space::LatLong latLong,
                       bool shouldShare);
            
            unsigned int Identifier() const { return m_modelId; }
        };
        
        inline bool operator==(const MyPinModel& lhs, const MyPinModel& rhs){ return lhs.Identifier() == rhs.Identifier(); }
        inline bool operator!=(const MyPinModel& lhs, const MyPinModel& rhs){return !operator==(lhs,rhs);}
        inline bool operator< (const MyPinModel& lhs, const MyPinModel& rhs){return lhs.Identifier() < rhs.Identifier(); }
        inline bool operator> (const MyPinModel& lhs, const MyPinModel& rhs){return  operator< (rhs,lhs);}
        inline bool operator<=(const MyPinModel& lhs, const MyPinModel& rhs){return !operator> (lhs,rhs);}
        inline bool operator>=(const MyPinModel& lhs, const MyPinModel& rhs){return !operator< (lhs,rhs);}
    }
}