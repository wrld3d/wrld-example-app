// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

#include "IndoorAtlasLocationService.h"
#include "IIndoorAtlasLocationManager.h"
#include <string>
#include <map>
#include "AndroidNativeState.h"

namespace ExampleApp
{
    namespace IndoorAtlas
	{
    	namespace View
		{
			class IndoorAtlasLocationManager: public IIndoorAtlasLocationManager, private Eegeo::NonCopyable
			{
			private:
				ExampleApp::IndoorAtlas::IndoorAtlasLocationService* m_pIndoorAtlasLocationService;
				std::map<int, std::string> m_floorMap;
				int m_floorIndex;

				AndroidNativeState& m_nativeState;
				jclass m_jniApiClass;
				jobject m_jniApiInstance;
				ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;

				std::string GetFloorPlanIdFromFloorIndex(int floorIndex);

			public:
				IndoorAtlasLocationManager(ExampleApp::IndoorAtlas::IndoorAtlasLocationService* indoorAtlasLocationService
										   , AndroidNativeState& nativeState
										   , ExampleApp::ExampleAppMessaging::TMessageBus& messageBus);
				virtual ~IndoorAtlasLocationManager();

				void StartUpdatingLocation(std::string apiKey,
										   std::string apiSecret,
										   std::map<int, std::string> floorMap,
										   int floorIndex);

				void StopUpdatingLocation();
				void SetFloorIndex(int floorIndex);
				void OnUpdateLocation(double latitude, double longitude);
			};
		}
    }
}

