// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

#include "BidirectionalBus.h"
#include "InteriorsPositionStartUpdatingLocationMessage.h"
#include "InteriorsPositionStopUpdatingLocationMessage.h"
#include "ICallback.h"
#include <map>
#include <string>
#include "AndroidNativeState.h"


namespace ExampleApp
{
    namespace SenionLab
    {
    	class SenionLabLocationService;
    	namespace View
		{
			class SenionLabLocationManager: private Eegeo::NonCopyable
			{
			private:

				ExampleApp::SenionLab::SenionLabLocationService* m_pSenionLabLocationService;
				std::map<int, std::string> m_floorMap;
				int m_floorIndex;

				AndroidNativeState& m_nativeState;
				jclass m_jniApiClass;
				jobject m_jniApiInstance;
				ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;

				int getFloorIndexFromSenionFloorIndex(std::string senionFloorIndex);

			public:

				SenionLabLocationManager(ExampleApp::SenionLab::SenionLabLocationService* pSenionLabLocationService,
										 ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
										 AndroidNativeState& nativeState);

				virtual ~SenionLabLocationManager();

				void StartUpdatingLocation(std::string apiKey,
										   std::string apiSecret,
										   std::map<int, std::string> floorMap);
				void StopUpdatingLocation();
				void OnUpdateLocation(double latitude, double longitude, std::string floorNo);

				void OnStartUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage& startUpdatingLocationMessage);
                void OnStopUpdatingLocation(const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage& stopUpdatingLocationMessage);

				Eegeo::Helpers::TCallback1<SenionLabLocationManager, const ExampleApp::InteriorsPosition::InteriorsPositionStartUpdatingLocationMessage&> m_startUpdatingLocationCallback;
				Eegeo::Helpers::TCallback1<SenionLabLocationManager, const ExampleApp::InteriorsPosition::InteriorsPositionStopUpdatingLocationMessage&> m_stopUpdatingLocationCallback;
    		};
		}
    }
}

