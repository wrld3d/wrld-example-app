// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsViewController.h"
#include "Types.h"
#include "MyPinCreationDetailsView.h"
#include "IMyPinCreationDetailsViewModel.h"
#include "ICallback.h"
#include "IConnectivityService.h"

@class MyPinCreationDetailsViewController;

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        class MyPinCreationDetailsViewControllerInterop : private Eegeo::NonCopyable
        {
            MyPinCreationDetailsViewController* m_pController;
            IMyPinCreationDetailsViewModel& m_viewModel;
            Eegeo::Web::IConnectivityService& m_connectivityService;
            
            Eegeo::Helpers::TCallback0<MyPinCreationDetailsViewControllerInterop> m_myPinCreationDetailsOpenedCallback;
            Eegeo::Helpers::TCallback0<MyPinCreationDetailsViewControllerInterop> m_myPinCreationDetailsClosedCallback;
            Eegeo::Helpers::TCallback1<MyPinCreationDetailsViewControllerInterop, const bool&> m_networkConnectivityChangedCallback;
            
            void HandleMyPinCreationDetailsOpened()
            {
                [m_pController open];
            }
            
            void HandleMyPinCreationDetailsClosed()
            {
                [m_pController close];
            }
            
            void HandleNetworkConnectivityChanged(const bool& hasConnectivity)
            {
                [m_pController setNetworkConnectivityState: hasConnectivity];
            }
            
        public:
            MyPinCreationDetailsViewControllerInterop(MyPinCreationDetailsViewController* pController,
                                                      IMyPinCreationDetailsViewModel& viewModel,
                                                      Eegeo::Web::IConnectivityService& connectivityService)
            : m_pController(pController)
            , m_viewModel(viewModel)
            , m_connectivityService(connectivityService)
            , m_myPinCreationDetailsOpenedCallback(this, &MyPinCreationDetailsViewControllerInterop::HandleMyPinCreationDetailsOpened)
            , m_myPinCreationDetailsClosedCallback(this, &MyPinCreationDetailsViewControllerInterop::HandleMyPinCreationDetailsClosed)
            , m_networkConnectivityChangedCallback(this, &MyPinCreationDetailsViewControllerInterop::HandleNetworkConnectivityChanged)
            {
                m_viewModel.InsertOpenedCallback(m_myPinCreationDetailsOpenedCallback);
                m_viewModel.InsertClosedCallback(m_myPinCreationDetailsClosedCallback);
                m_connectivityService.RegisterConnectivityChangedCallback(m_networkConnectivityChangedCallback);
            }
            
            ~MyPinCreationDetailsViewControllerInterop()
            {
                m_viewModel.RemoveOpenedCallback(m_myPinCreationDetailsOpenedCallback);
                m_viewModel.RemoveClosedCallback(m_myPinCreationDetailsClosedCallback);
                m_connectivityService.UnregisterConnectivityChangedCallback(m_networkConnectivityChangedCallback);
            }
        };
    }
}
