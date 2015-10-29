// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "CallbackCollection.h"
#include "ICallback.h"
#include "Types.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorExplorerUserInteractionModel : private Eegeo::NonCopyable
            {
            private:
                bool m_enabled;
                Eegeo::Helpers::CallbackCollection0 m_enabledChangedCallbacks;
            public:
                InteriorExplorerUserInteractionModel();
                
                void SetEnabled(bool enabled);
                
                bool IsEnabled() const;
                
                void InsertEnabledChangedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void RemoveEnabledChangedCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
