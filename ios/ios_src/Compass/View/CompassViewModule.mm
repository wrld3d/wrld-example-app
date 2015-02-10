// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "CompassViewModule.h"
#include "RenderContext.h"
#include "CompassView.h"
#include "ScreenProperties.h"
#include "CompassViewInterop.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            CompassViewModule::CompassViewModule(ICompassViewModel& viewModel,
                                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                 ExampleAppMessaging::TMessageBus& messageBus)
            {

                m_pView = [[CompassView alloc] initWithParams
                            :screenProperties.GetScreenWidth()
                            :screenProperties.GetScreenHeight()
                            :screenProperties.GetPixelScale()];

                m_pController = Eegeo_NEW(CompassController)(*[m_pView getInterop], viewModel, messageBus);
            }

            CompassViewModule::~CompassViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pView release];
            }

            CompassController& CompassViewModule::GetCompassController() const
            {
                return *m_pController;
            }

            CompassView& CompassViewModule::GetCompassView() const
            {
                return *m_pView;
            }
        }
    }
}
