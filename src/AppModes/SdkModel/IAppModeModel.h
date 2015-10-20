// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CallbackCollection.h"
#include "AppModes.h"
#include <vector>
#include "IStateMachineState.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace SdkModel
        {
            // TODO: Sometimes have to take dependencies on platform types not related to some app types
            //       to prohibit/allow behaviour in certain states (for e.g. WorldPinOnMapController needing
            //       InteriorSelectionModel to see if in interiors mode. Trying to circumvent this by adding a model
            //       that indicated what mode our app is currently in. This is thin and represents only interiors/worldmap
            //       at the moment, but should be expanded on (e.g. in menu state by observing modality model etc.)
            enum AppMode
            {
                WorldMode = 0,
                InteriorMode,
                TourMode
            };

            class IAppModeModel : protected Eegeo::NonCopyable
            {
            public:
                virtual ~IAppModeModel()
                {

                }
                
                virtual void InitialiseStateMachine(const std::vector<Helpers::IStateMachineState*>& appStates) = 0;

                virtual AppMode GetAppMode() const = 0;
                
                virtual void SetAppMode(AppMode mode) = 0;
                
                virtual void Update(float dt) = 0;

                virtual void RegisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void UnregisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
