// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorSelectionModel.h"
#include "IAlertBoxFactory.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorPermissionObserver : private Eegeo::NonCopyable
            {
            public:
                InteriorPermissionObserver(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                           Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory);
                ~InteriorPermissionObserver();
                
                void OnSelectionFailed(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                
            private:
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<InteriorPermissionObserver> m_failAlertHandler;
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Helpers::TCallback1<InteriorPermissionObserver, const Eegeo::Resources::Interiors::InteriorId> m_interiorSelectionFailedCallback;
                void OnFailAlertBoxDismissed();
                
            };
        }
    }
}