// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorPermissionObserver.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"


namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorPermissionObserver::InteriorPermissionObserver(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                   Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory)
            : m_alertBoxFactory(alertBoxFactory)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorSelectionFailedCallback(this, &InteriorPermissionObserver::OnSelectionFailed)
            , m_failAlertHandler(this, &InteriorPermissionObserver::OnFailAlertBoxDismissed)
            {
                m_interiorSelectionModel.RegisterSelectionFailedCallback(m_interiorSelectionFailedCallback);
            }
            
            InteriorPermissionObserver::~InteriorPermissionObserver()
            {
                m_interiorSelectionModel.UnregisterSelectionFailedCallback(m_interiorSelectionFailedCallback);
            }
            void InteriorPermissionObserver::OnSelectionFailed(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                m_alertBoxFactory.CreateSingleOptionAlertBox("Error", "You do not have permission to view this interior.", m_failAlertHandler);
            }
            
            void InteriorPermissionObserver::OnFailAlertBoxDismissed()
            {
            }
        }
    }
}