// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "InteriorsLocationAuthorizationChangedMessage.h"
#include "InteriorsLocationChangedMessage.h"
#include "IIndoorAtlasLocationInterop.h"
#include "IndoorAtlasLocationService.h"

#include <jni.h>
#include <map>
#include <string>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationInterop : public IIndoorAtlasLocationInterop, protected Eegeo::NonCopyable
                {
                public:
                    IndoorAtlasLocationInterop(AndroidNativeState& nativeState);

                    ~IndoorAtlasLocationInterop();

                    // non-interface methods
                    void UpdateLocation(
                            const double latitudeDegrees,
                            const double longitudeDegrees,
                            const double horizontalAccuracyInMeters,
                            const std::string& floorId);

                    void UpdateIsAuthorized(const bool isAuthorized);

                    // interface implementation
                    void SetLocationService(IndoorAtlasLocationService* pLocationService) override;

                    void StartUpdating(const std::string& apiKey,
                                       const std::string& apiSecret,
                                       const std::map<int, std::string>& floorMap) override;

                    void StopUpdating() override;


                private:
                    bool TryMapFloorIdToFloorIndex(const std::string floorId, int& wrldFloorId);

                    IndoorAtlasLocationService* m_pIndoorAtlasLocationService;
                    AndroidNativeState& m_nativeState;
                    jclass m_locationManagerClass;
                    jobject m_locationManagerInstance;
                    std::map<int, std::string> m_floorMap;
                };
            }
        }
    }
}
