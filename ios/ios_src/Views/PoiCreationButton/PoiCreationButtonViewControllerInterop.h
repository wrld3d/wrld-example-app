// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiCreationButtonViewController.h"
#include "PoiCreationModel.h"
#include "Types.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationButtonViewControllerInterop : private Eegeo::NonCopyable
        {
            PoiCreationButtonViewController* m_pController;
            IPoiCreationModel& m_model;
            IPoiCreationButtonViewModel& m_viewModel;

            Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;
            
            void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                [m_pController handleScreenStateChanged:m_viewModel.OnScreenState()];
            }
            
        public:
            
            PoiCreationButtonViewControllerInterop(PoiCreationButtonViewController* pController,
                                                   IPoiCreationModel& model,
                                                   IPoiCreationButtonViewModel& viewModel)
            : m_pController(pController)
            , m_model(model)
            , m_viewModel(viewModel)
            , m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<PoiCreationButtonViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &PoiCreationButtonViewControllerInterop::OnScreenStateChangedCallback))
            {
                m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
            }
            
            ~PoiCreationButtonViewControllerInterop()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
    
                Eegeo_DELETE m_pOnScreenStateChangedCallback;
            }
        };
        
    }
}
