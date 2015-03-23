// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassModeObserver.h"
#include "CompassModeUnauthorizedMessage.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            CompassModeObserver::CompassModeObserver(ICompassModel& model,
                    ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
                : m_model(model)
                , m_messageBus(messageBus)
                , m_callback(this, &CompassModeObserver::OnGpsModeChanged)
                , m_unauthorizedCallback(this, &CompassModeObserver::OnGpsModeDeniedBecauseUnauthorized)
            {
                m_model.InsertGpsModeChangedCallback(m_callback);
                m_model.InsertGpsModeUnauthorizedCallback(m_unauthorizedCallback);
            }

            CompassModeObserver::~CompassModeObserver()
            {
                m_model.RemoveGpsModeChangedCallback(m_callback);
                m_model.RemoveGpsModeUnauthorizedCallback(m_unauthorizedCallback);
            }

            void CompassModeObserver::OnGpsModeChanged()
            {
                m_messageBus.Publish(CompassModeChangedMessage(m_model.GetGpsMode()));
            }
            
            void CompassModeObserver::OnGpsModeDeniedBecauseUnauthorized()
            {
                m_messageBus.Publish(CompassModeUnauthorizedMessage());
            }
        }
    }
}
