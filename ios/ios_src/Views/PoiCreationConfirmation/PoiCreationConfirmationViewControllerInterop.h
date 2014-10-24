// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiCreationConfirmationViewController.h"
#include "PoiCreationModel.h"
#include "Types.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "IPoiCreationCompositeViewModel.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationConfirmationViewControllerInterop : private Eegeo::NonCopyable
        {
            PoiCreationConfirmationViewController* m_pController;
            IPoiCreationModel& m_model;
            IPoiCreationConfirmationViewModel& m_viewModel;
            IPoiCreationCompositeViewModel& m_compositeViewModel;
            
            Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

            void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState)
            {
                [m_pController handleScreenStateChanged:m_viewModel.OnScreenState()];
            }
            
            
        public:
            
            PoiCreationConfirmationViewControllerInterop(PoiCreationConfirmationViewController* pController,
                                                         IPoiCreationModel& model,
                                                         IPoiCreationConfirmationViewModel& viewModel,
                                                         IPoiCreationCompositeViewModel& compositeViewModel)
            : m_pController(pController)
            , m_model(model)
            , m_viewModel(viewModel)
            , m_compositeViewModel(compositeViewModel)
            , m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<PoiCreationConfirmationViewControllerInterop, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &PoiCreationConfirmationViewControllerInterop::OnScreenStateChangedCallback))
            {
                m_viewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
            }
            
            ~PoiCreationConfirmationViewControllerInterop()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
                
                Eegeo_DELETE m_pOnScreenStateChangedCallback;
            }
        };
        
    }
}
