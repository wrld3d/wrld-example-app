// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <map>

#include "MyPins.h"
#include "IMyPinsService.h"
#include "WorldPins.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"
#include "Menu.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinsService : public IMyPinsService
        {
        public:
            MyPinsService(IMyPinsRepository& myPinsRepository,
                          MyPinsFileIO& myPinsFileIO,
                          IMyPinSelectionHandlerFactory& myPinSelectionHandlerFactory,
                          WorldPins::IWorldPinsService& worldPinsService,
                          Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory);

            
            void RemovePin(MyPinModel* myPinModel);
            
            void SavePin(const std::string& title,
                         const std::string& description,
                         const Eegeo::Space::LatLong& latLong,
                         Byte* imageData,
                         size_t imageSize,
                         bool shouldShare);
            

            
        private:
            IMyPinsRepository& m_myPinsRepository;
            MyPinsFileIO& m_myPinsFileIO;
            IMyPinSelectionHandlerFactory& m_myPinSelectionHandlerFactory;
            
            WorldPins::IWorldPinsService& m_worldPinsService;
            
            Eegeo::Web::IWebLoadRequestFactory& m_webLoadRequestFactory;
            
            Eegeo::Web::TWebLoadRequestCompletionCallback<ExampleApp::MyPins::MyPinsService> m_webRequestCompleteCallback;
            void WebRequestCompleteCallback(Eegeo::Web::IWebLoadRequest& webLoadRequest);
            
            unsigned int m_lastIdUsed;
            
            typedef std::map<const MyPinModel*, WorldPins::WorldPinItemModel*> TMyPinToWorldPinMap;
            TMyPinToWorldPinMap m_myPinToWorldPinMap;
            
            void AddPinToMap(MyPinModel* pMyPinModel);
            
            void SubmitPinToWebService(const MyPinModel& myPinModel);
        };
    }
}