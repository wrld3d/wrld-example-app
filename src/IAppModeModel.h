// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CallbackCollection.h"
#include "Types.h"

namespace ExampleApp
{
    // TODO: Sometimes have to take dependencies on platform types not related to some app types
    //       to prohibit/allow behaviour in certain states (for e.g. WorldPinOnMapController needing
    //       InteriorSelectionModel to see if in interiors mode. Trying to circumvent this by adding a model
    //       that indicated what mode our app is currently in. This is thin and represents only interiors/worldmap
    //       at the moment, but should be expanded on (e.g. in menu state by observing modality model etc.)
    enum AppMode
    {
        WorldMode,
        InteriorMode
    };

    class IAppModeModel : protected Eegeo::NonCopyable
    {
    public:
        virtual ~IAppModeModel()
        {

        }

        virtual AppMode GetAppMode() const = 0;

        virtual void RegisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
        virtual void UnregisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
    };
}