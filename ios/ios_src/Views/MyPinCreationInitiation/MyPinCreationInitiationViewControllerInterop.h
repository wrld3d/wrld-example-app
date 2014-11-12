// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreationInitiationViewController.h"
#include "MyPinCreationModel.h"
#include "Types.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationInitiationViewControllerInterop : private Eegeo::NonCopyable
        {
            MyPinCreationInitiationViewController* m_pController;
            IMyPinCreationModel& m_model;
            IMyPinCreationInitiationViewModel& m_viewModel;

            Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;
            
            void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                [m_pController handleScreenStateChanged:m_viewModel.OnScreenState()];
            }
            
        public:
            
            MyPinCreationInitiationViewControllerInterop(MyPinCreationInitiationViewController* pController,
                                                   IMyPinCreationModel& model,
                                                   IMyPinCreationInitiationViewModel& viewModel)
            : m_pController(pController)
            , m_model(model)
            , m_viewModel(viewModel)
            , m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<MyPinCreationInitiationViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &MyPinCreationInitiationViewControllerInterop::OnScreenStateChangedCallback))
            {
                m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
            }
            
            ~MyPinCreationInitiationViewControllerInterop()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
    
                Eegeo_DELETE m_pOnScreenStateChangedCallback;
            }
        };
        
    }
}
