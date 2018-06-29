// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once


#include "ISenionLabLocationInterop.h"
#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "InteriorsLocationAuthorizationChangedMessage.h"
#include "InteriorsLocationChangedMessage.h"
#include "SenionLabLocationService.h"

#include <jni.h>
#include <map>
#include <string>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationInterop : public ISenionLabLocationInterop, private Eegeo::NonCopyable
                {
                public:
                    SenionLabLocationInterop(ExampleAppMessaging::TMessageBus& messageBus,
                                             AndroidNativeState& nativeState);

                    ~SenionLabLocationInterop();

                    // non-interface
                    void UpdateIsAuthorized(bool isAuthorized);

                    void UpdateLocation(
                            double latitudeDegrees,
                            double longtitudeDegrees,
                            double horizontalAccuracyInMeters,
                            int senionFloorNumber);

                    void UpdateHeading(double headingInDegrees);

                    void OnResume();
                    void OnPause();

                    // interface implementation
                    void SetLocationService(SenionLabLocationService* pLocationService);

                    void StartUpdatingLocation(const std::string& apiKey,
                                               const std::string& apiSecret,
                                               const std::map<int, std::string>& floorMap) override;

                    void StopUpdatingLocation() override;
                private:
                    int FloorNumberToFloorIndex(const int senionFloorNumber);

                    void StartLocationUpdates();
                    void StopLocationUpdates();

                    AndroidNativeState& m_nativeState;
                    SenionLabLocationService* m_pSenionLabLocationService;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    jclass m_locationManagerClass;
                    jobject m_locationManagerInstance;
                    std::map<int, std::string> m_floorMap;

                    std::string m_apiKey;
                    std::string m_apiSecret;
                    bool m_isActive;
                };
            }
        }
    }
}
