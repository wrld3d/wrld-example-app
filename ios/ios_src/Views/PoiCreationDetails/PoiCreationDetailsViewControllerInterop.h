// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationDetailsViewController.h"
#include "Types.h"
#include "PoiCreationDetailsView.h"
#include "IPoiCreationDetailsViewModel.h"
#include "ICallback.h"

@class PoiCreationDetailsViewController;

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        class PoiCreationDetailsViewControllerInterop : private Eegeo::NonCopyable
        {
            PoiCreationDetailsViewController* m_pController;
            IPoiCreationDetailsViewModel& m_viewModel;
            
            Eegeo::Helpers::ICallback0* m_pPoiCreationDetailsOpenedCallback;
            Eegeo::Helpers::ICallback0* m_pPoiCreationDetailsClosedCallback;
            
            void HandlePoiCreationDetailsOpened()
            {
                [m_pController open];
            }
            
            void HandlePoiCreationDetailsClosed()
            {
                [m_pController close];
            }
            
        public:
            PoiCreationDetailsViewControllerInterop(PoiCreationDetailsViewController* pController,
                                                    IPoiCreationDetailsViewModel& viewModel)
            : m_pController(pController)
            , m_viewModel(viewModel)
            , m_pPoiCreationDetailsOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<PoiCreationDetailsViewControllerInterop>(this, &PoiCreationDetailsViewControllerInterop::HandlePoiCreationDetailsOpened)))
            , m_pPoiCreationDetailsClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<PoiCreationDetailsViewControllerInterop>(this, &PoiCreationDetailsViewControllerInterop::HandlePoiCreationDetailsClosed)))
            {
                m_viewModel.InsertOpenedCallback(*m_pPoiCreationDetailsOpenedCallback);
                m_viewModel.InsertClosedCallback(*m_pPoiCreationDetailsClosedCallback);
            }
            
            ~PoiCreationDetailsViewControllerInterop()
            {
                m_viewModel.RemoveOpenedCallback(*m_pPoiCreationDetailsOpenedCallback);
                m_viewModel.RemoveClosedCallback(*m_pPoiCreationDetailsClosedCallback);
                
                Eegeo_DELETE m_pPoiCreationDetailsOpenedCallback;
                Eegeo_DELETE m_pPoiCreationDetailsClosedCallback;
            }
        };
    }
}
