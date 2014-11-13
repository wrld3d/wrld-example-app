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
            IMyPinCreationInitiationViewModel& m_viewModel;

            Eegeo::Helpers::TCallback2<MyPinCreationInitiationViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float> m_onScreenStateChangedCallback;
            
            void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                [m_pController handleScreenStateChanged:m_viewModel.OnScreenState()];
            }
            
        public:
            
            MyPinCreationInitiationViewControllerInterop(MyPinCreationInitiationViewController* pController,
                                                         IMyPinCreationInitiationViewModel& viewModel)
            : m_pController(pController)
            , m_viewModel(viewModel)
            , m_onScreenStateChangedCallback(this, &MyPinCreationInitiationViewControllerInterop::OnScreenStateChangedCallback)
            {
                m_viewModel.InsertOnScreenStateChangedCallback(m_onScreenStateChangedCallback);
            }
            
            ~MyPinCreationInitiationViewControllerInterop()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(m_onScreenStateChangedCallback);
            }
        };
        
    }
}
