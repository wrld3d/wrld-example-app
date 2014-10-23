// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "FlattenButtonViewController.h"
#include "IFlattenButtonViewModel.h"
#include "IFlattenButtonModel.h"
#include "Types.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        class FlattenButtonViewControllerInterop : private Eegeo::NonCopyable
        {
            FlattenButtonViewController* m_pController;
            IFlattenButtonModel& m_model;
            IFlattenButtonViewModel& m_viewModel;
            
            Eegeo::Helpers::ICallback0* m_pFlattenModelStateChangedCallback;
            Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;
            
            void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                [m_pController handleScreenStateChanged:m_viewModel.OnScreenState()];
            }
            
            void OnFlattenModelStateChangedCallback()
            {
                [m_pController handleModelStateChanged:m_model.GetFlattened()];
            }

        public:
            
            FlattenButtonViewControllerInterop(FlattenButtonViewController* pController,
                                               IFlattenButtonModel& model,
                                               IFlattenButtonViewModel& viewModel)
            : m_pController(pController)
            , m_model(model)
            , m_viewModel(viewModel)
            , m_pFlattenModelStateChangedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<FlattenButtonViewControllerInterop>)(this, &FlattenButtonViewControllerInterop::OnFlattenModelStateChangedCallback))
            , m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<FlattenButtonViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &FlattenButtonViewControllerInterop::OnScreenStateChangedCallback))
            {
                m_model.InsertChangedCallback(*m_pFlattenModelStateChangedCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
            }
            
            ~FlattenButtonViewControllerInterop()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
                m_model.RemoveChangedCallback(*m_pFlattenModelStateChangedCallback);
                
                Eegeo_DELETE m_pFlattenModelStateChangedCallback;
                Eegeo_DELETE m_pOnScreenStateChangedCallback;
            }
        };
    }
}