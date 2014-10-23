// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "CompassViewController.h"
#include "CompassViewModel.h"
#include "Types.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace Compass
    {
        class CompassViewControllerInterop : private Eegeo::NonCopyable
        {
            CompassViewController* m_pController;
            ICompassModel& m_model;
            ICompassViewModel& m_viewModel;
            
            Eegeo::Helpers::ICallback0* m_pGpsModelChangedCallback;
            Eegeo::Helpers::ICallback1<float>* m_pUpdateCallback;
            Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;
            
            void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                [m_pController handleScreenStateChanged:m_viewModel.OnScreenState()];
            }
            
            void OnHeadingUpdated(float& heading)
            {
                [m_pController updateHeading:heading];
            }
            
            void OnGpsModeChanged()
            {
                [m_pController handleGpsModeChanged];
            }
            
        public:
            
            CompassViewControllerInterop(CompassViewController* pController,
                                         ICompassModel& model,
                                         ICompassViewModel& viewModel)
            : m_pController(pController)
            , m_model(model)
            , m_viewModel(viewModel)
            , m_pGpsModelChangedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<CompassViewControllerInterop>)(this, &CompassViewControllerInterop::OnGpsModeChanged))
            , m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<CompassViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &CompassViewControllerInterop::OnScreenStateChangedCallback))
            , m_pUpdateCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<CompassViewControllerInterop, float>))(this, &CompassViewControllerInterop::OnHeadingUpdated))
            {
                m_model.InsertGpsModeChangedCallback(*m_pGpsModelChangedCallback);
                m_viewModel.InsertUpdateCallback(*m_pUpdateCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
            }
            
            ~CompassViewControllerInterop()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
                m_viewModel.RemoveUpdateCallback(*m_pUpdateCallback);
                m_model.RemoveGpsModeChangedCallback(*m_pGpsModelChangedCallback);
                
                Eegeo_DELETE m_pOnScreenStateChangedCallback;
                Eegeo_DELETE m_pUpdateCallback;
                Eegeo_DELETE m_pGpsModelChangedCallback;
            }
        };
        
    }
}
