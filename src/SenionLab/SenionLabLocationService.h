// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ILocationService.h"
#include "LatLongAltitude.h"
#include "InteriorsModel.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SenionLabLocationChangedMessage.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        class SenionLabLocationService : public Eegeo::Location::ILocationService
        {
        public:
            SenionLabLocationService(Eegeo::Location::ILocationService& defaultLocationService,
                                     const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                     const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
									 ExampleApp::ExampleAppMessaging::TMessageBus& messageBus);
            
            ~SenionLabLocationService();
            const bool GetIsAuthorized() const;
            
            bool IsIndoors();
            Eegeo::Resources::Interiors::InteriorId GetInteriorId();
            bool GetLocation(Eegeo::Space::LatLong& latLong);
            bool GetAltitude(double& altitude);
            bool GetFloorIndex(int& floorIndex);
            bool GetHorizontalAccuracy(double& accuracy);
            bool GetHeadingDegrees(double& headingDegrees);
            void StopListening();
            void OnLocationChanged(const ExampleApp::SenionLab::SenionLabLocationChangedMessage& locationChangedMessage);
            void SetIsAuthorized(bool isAuthorized);
            void SetLocation(Eegeo::Space::LatLong& latLong);
            void SetFloorIndex(int floorIndex);
            
        private:
            Eegeo::Location::ILocationService& m_defaultLocationService;
            const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
            const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
            
            bool m_isAuthorized;
            Eegeo::Space::LatLong m_latLong;
            int m_floorIndex;
            ExampleApp::ExampleAppMessaging::TMessageBus& m_messageBus;
            Eegeo::Helpers::TCallback1<SenionLabLocationService, const ExampleApp::SenionLab::SenionLabLocationChangedMessage&> m_LocationChangeCallback;
        };
    }
}
