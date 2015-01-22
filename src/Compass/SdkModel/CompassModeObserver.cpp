// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassModeObserver.h"

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
            {
                m_model.InsertGpsModeChangedCallback(m_callback);
            }

            CompassModeObserver::~CompassModeObserver()
            {
                m_model.RemoveGpsModeChangedCallback(m_callback);
            }

            void CompassModeObserver::OnGpsModeChanged()
            {
                m_messageBus.Publish(CompassModeChangedMessage(m_model.GetGpsMode()));
            }
        }
    }
}
