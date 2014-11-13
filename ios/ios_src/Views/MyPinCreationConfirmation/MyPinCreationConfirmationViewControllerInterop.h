// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreationConfirmationViewController.h"
#include "MyPinCreationModel.h"
#include "Types.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "IMyPinCreationCompositeViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationConfirmationViewControllerInterop : private Eegeo::NonCopyable
        {
            MyPinCreationConfirmationViewController* m_pController;
            IMyPinCreationConfirmationViewModel& m_viewModel;
            IMyPinCreationCompositeViewModel& m_compositeViewModel;
            
            Eegeo::Helpers::TCallback2<MyPinCreationConfirmationViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float> m_onScreenStateChangedCallback;

            void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                [m_pController handleScreenStateChanged:m_viewModel.OnScreenState()];
            }
            
            
        public:
            
            MyPinCreationConfirmationViewControllerInterop(MyPinCreationConfirmationViewController* pController,
                                                           IMyPinCreationConfirmationViewModel& viewModel,
                                                           IMyPinCreationCompositeViewModel& compositeViewModel)
            : m_pController(pController)
            , m_viewModel(viewModel)
            , m_compositeViewModel(compositeViewModel)
            , m_onScreenStateChangedCallback(this, &MyPinCreationConfirmationViewControllerInterop::OnScreenStateChangedCallback)
            {
                m_viewModel.InsertOnScreenStateChangedCallback(m_onScreenStateChangedCallback);
            }
            
            ~MyPinCreationConfirmationViewControllerInterop()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(m_onScreenStateChangedCallback);
            }
        };
        
    }
}
