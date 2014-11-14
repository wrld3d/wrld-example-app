// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <map>

#include "MyPins.h"
#include "IMyPinsService.h"
#include "WorldPins.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinsService : public IMyPinsService
        {
        public:
            MyPinsService(IMyPinsRepository& myPinsRepository,
                          MyPinsFileIO& myPinsFileIO,
                          Menu::IMenuOptionsModel& menuOptionsModel,
                          Eegeo::Pins::PinRepository& pinRepository,
                          WorldPins::IWorldPinsFactory& pinFactory,
                          Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory);
            
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
            
            void SubmitPinToWebService(const MyPinModel& myPinModel);
            
        private:
            IMyPinsRepository& m_myPinsRepository;
            MyPinsFileIO& m_myPinsFileIO;
            Menu::IMenuOptionsModel& m_menuOptionsModel;
            
            Eegeo::Pins::PinRepository& m_pinRepository;
            WorldPins::IWorldPinsFactory& m_pinFactory;
            Eegeo::Web::IWebLoadRequestFactory& m_webLoadRequestFactory;
            
            Eegeo::Web::TWebLoadRequestCompletionCallback<ExampleApp::MyPins::MyPinsService> m_webRequestCompleteCallback;
            void WebRequestCompleteCallback(Eegeo::Web::IWebLoadRequest& webLoadRequest);
            
            unsigned int m_lastIdUsed;
            
            typedef std::map<const MyPinModel*, Eegeo::Pins::TPinId> TModelToPinIdMap;
            TModelToPinIdMap m_modelToPinIdMap;
            
            
            
            Eegeo::Pins::TPinId GetPinIdForModel(const MyPinModel* model);
        };
    }
}