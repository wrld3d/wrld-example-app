// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "AppModeModel.h"
#include "InteriorSelectionModel.h"
#include "AppModeChangedMessage.h"
#include "TourService.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace SdkModel
        {
            AppModeModel::AppModeModel(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus)
            : m_interiorSelectionModel(interiorSelectionModel)
            , m_messageBus(messageBus)
            , m_interiorSelectionModelChangedCallback(this, &AppModeModel::OnInteriorSelectionModelChanged)
            , m_appMode(WorldMode)
            , m_previousAppMode(WorldMode)
            , m_sdkDomainEventBus(sdkDomainEventBus)
            , m_tourStateChangedBinding(this, &AppModeModel::OnTourStateChanged)
            {
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
                m_sdkDomainEventBus.Subscribe(m_tourStateChangedBinding);
            }

            AppModeModel::~AppModeModel()
            {
                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
                m_sdkDomainEventBus.Unsubscribe(m_tourStateChangedBinding);
            }
            
            void AppModeModel::OnTourStateChanged(const Tours::TourStateChangedMessage& message)
            {
                if(message.TourStarted())
                {
                    SetAppMode(TourMode);
                }
                else
                {
                    SetAppMode(m_previousAppMode);
                }
            }

            void AppModeModel::OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                if(m_appMode == TourMode)
                {
                    m_previousAppMode = m_interiorSelectionModel.IsInteriorSelected() ? InteriorMode : WorldMode;
                    return;
                }
                
                AppMode newAppMode = m_interiorSelectionModel.IsInteriorSelected() ? InteriorMode : WorldMode;
                SetAppMode(newAppMode);
            }

            void AppModeModel::RegisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_appModeChangedCallbacks.AddCallback(callback);
            }

            void AppModeModel::UnregisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_appModeChangedCallbacks.RemoveCallback(callback);
            }

            AppMode AppModeModel::GetAppMode() const
            {
                return m_appMode;
            }

            void AppModeModel::SetAppMode(AppMode appMode)
            {
                if (m_appMode != appMode)
                {
                    m_previousAppMode = m_appMode;
                    
                    m_appMode = appMode;
                    m_appModeChangedCallbacks.ExecuteCallbacks();
                    m_messageBus.Publish(AppModeChangedMessage(m_appMode));
                }
            }
        }
    }
}