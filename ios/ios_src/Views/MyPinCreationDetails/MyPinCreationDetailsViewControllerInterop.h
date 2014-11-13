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
            
            Eegeo::Helpers::TCallback0<MyPinCreationDetailsViewControllerInterop> m_myPinCreationDetailsOpenedCallback;
            Eegeo::Helpers::TCallback0<MyPinCreationDetailsViewControllerInterop> m_myPinCreationDetailsClosedCallback;
            
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
            , m_myPinCreationDetailsOpenedCallback(this, &MyPinCreationDetailsViewControllerInterop::HandleMyPinCreationDetailsOpened)
            , m_myPinCreationDetailsClosedCallback(this, &MyPinCreationDetailsViewControllerInterop::HandleMyPinCreationDetailsClosed)
            {
                m_viewModel.InsertOpenedCallback(m_myPinCreationDetailsOpenedCallback);
                m_viewModel.InsertClosedCallback(m_myPinCreationDetailsClosedCallback);
            }
            
            ~MyPinCreationDetailsViewControllerInterop()
            {
                m_viewModel.RemoveOpenedCallback(m_myPinCreationDetailsOpenedCallback);
                m_viewModel.RemoveClosedCallback(m_myPinCreationDetailsClosedCallback);
            }
        };
    }
}
