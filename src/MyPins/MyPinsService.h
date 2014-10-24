// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <map>

#include "MyPins.h"
#include "IMyPinsService.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinsService : public IMyPinsService
        {
        public:
            MyPinsService(IMyPinsRepository& myPinsRepository,
                          MyPinsFileIO& myPinsFileIO,
                          Eegeo::Pins::PinRepository& pinRepository,
                          WorldPins::IWorldPinsFactory& pinFactory);
            
            void AddPin(const std::string& title,
                        const std::string& description,
                        const Eegeo::Space::LatLong& latLong,
                        Byte* imageData,
                        size_t imageSize,
                        bool shouldShare);
            
            void RemovePin(const MyPinModel& myPinModel);
            
            void SavePin(const std::string& title,
                         const std::string& description,
                         const Eegeo::Space::LatLong& latLong,
                         Byte* imageData,
                         size_t imageSize,
                         bool shouldShare);
            
        private:
            IMyPinsRepository& m_myPinsRepository;
            MyPinsFileIO& m_myPinsFileIO;
            
            Eegeo::Pins::PinRepository& m_pinRepository;
            WorldPins::IWorldPinsFactory& m_pinFactory;
            
            unsigned int m_lastIdUsed;
            
            typedef std::map<const MyPinModel*, Eegeo::Pins::TPinId> TModelToPinIdMap;
            TModelToPinIdMap m_modelToPinIdMap;
            
            Eegeo::Pins::TPinId GetPinIdForModel(const MyPinModel* model);
        };
    }
}