// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "DirectionsMenuInitiationViewModule.h"
#include "RenderContext.h"
#include "DirectionsMenuInitiationView.h"
#include "DirectionsMenuInitiationController.h"
#include "DirectionsMenuInitiationViewInterop.h"
#include "ScreenProperties.h"
#include "DirectionInitiationStateChangedObserver.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            DirectionsMenuInitiationViewModule::DirectionsMenuInitiationViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                                                                 IDirectionsMenuInitiationViewModel& viewModel,
                                                                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                                 Metrics::IMetricsService& metricsService)
            {
                m_pView = [[DirectionsMenuInitiationView alloc]
                           initWithParams:screenProperties.GetScreenWidth() :screenProperties.GetScreenHeight() :screenProperties.GetPixelScale()];


                m_pController = Eegeo_NEW(DirectionsMenuInitiationController)(viewModel, *[m_pView getInterop], messageBus, metricsService);
                
                m_pObserver =  Eegeo_NEW(DirectionInitiationStateChangedObserver)(m_pView,messageBus);
            }

            DirectionsMenuInitiationViewModule::~DirectionsMenuInitiationViewModule()
            {
                Eegeo_DELETE m_pController;

                [m_pView release];
            }

            DirectionsMenuInitiationController& DirectionsMenuInitiationViewModule::GetDirectionsMenuInitiationController() const
            {
                return *m_pController;
            }

            DirectionsMenuInitiationView& DirectionsMenuInitiationViewModule::GetDirectionsMenuInitiationView() const
            {
                return *m_pView;
            }
        }
    }
}
