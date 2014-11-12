// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsViewController.h"
#include "Types.h"
#include "MyPinCreationDetailsView.h"
#include "IMyPinCreationDetailsViewModel.h"
#include "ICallback.h"

@class MyPinCreationDetailsViewController;

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        class MyPinCreationDetailsViewControllerInterop : private Eegeo::NonCopyable
        {
            MyPinCreationDetailsViewController* m_pController;
            IMyPinCreationDetailsViewModel& m_viewModel;
            
            Eegeo::Helpers::ICallback0* m_pMyPinCreationDetailsOpenedCallback;
            Eegeo::Helpers::ICallback0* m_pMyPinCreationDetailsClosedCallback;
            
            void HandleMyPinCreationDetailsOpened()
            {
                [m_pController open];
            }
            
            void HandleMyPinCreationDetailsClosed()
            {
                [m_pController close];
            }
            
        public:
            MyPinCreationDetailsViewControllerInterop(MyPinCreationDetailsViewController* pController,
                                                    IMyPinCreationDetailsViewModel& viewModel)
            : m_pController(pController)
            , m_viewModel(viewModel)
            , m_pMyPinCreationDetailsOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<MyPinCreationDetailsViewControllerInterop>(this, &MyPinCreationDetailsViewControllerInterop::HandleMyPinCreationDetailsOpened)))
            , m_pMyPinCreationDetailsClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<MyPinCreationDetailsViewControllerInterop>(this, &MyPinCreationDetailsViewControllerInterop::HandleMyPinCreationDetailsClosed)))
            {
                m_viewModel.InsertOpenedCallback(*m_pMyPinCreationDetailsOpenedCallback);
                m_viewModel.InsertClosedCallback(*m_pMyPinCreationDetailsClosedCallback);
            }
            
            ~MyPinCreationDetailsViewControllerInterop()
            {
                m_viewModel.RemoveOpenedCallback(*m_pMyPinCreationDetailsOpenedCallback);
                m_viewModel.RemoveClosedCallback(*m_pMyPinCreationDetailsClosedCallback);
                
                Eegeo_DELETE m_pMyPinCreationDetailsOpenedCallback;
                Eegeo_DELETE m_pMyPinCreationDetailsClosedCallback;
            }
        };
    }
}
