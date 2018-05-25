// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkController.h"


namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkController::DeepLinkController(DeepLinkModel& deepLinkModel)
            : m_deepLinkModel(deepLinkModel)
            , m_pDelayedRequest(NULL)
            , m_uiStarted(false)
            {
            }
            
            DeepLinkController::~DeepLinkController()
            {
                if (m_pDelayedRequest != NULL)
                {
                    delete m_pDelayedRequest;
                }
            }

            void DeepLinkController::OnUiStarted()
            {
                m_uiStarted = true;

                if (m_pDelayedRequest != NULL)
                {
                    AppInterface::UrlData data;
                    data.host  = m_pDelayedRequest->Host ().c_str();
                    data.path  = m_pDelayedRequest->Path ().c_str();
                    data.query = m_pDelayedRequest->Query().c_str();

                    DoHandleDeepLinkOpen(data);

                    delete m_pDelayedRequest;
                    m_pDelayedRequest = NULL;
                }
            }

            void DeepLinkController::HandleDeepLinkOpen(const AppInterface::UrlData& data)
            {
                if (m_uiStarted)
                {
                    DoHandleDeepLinkOpen(data);
                    return;
                }

                Eegeo_ASSERT(m_pDelayedRequest == NULL);

                m_pDelayedRequest = new DeepLinkRequest(data);
            }

            void DeepLinkController::DoHandleDeepLinkOpen(const AppInterface::UrlData& data)
            {
                IDeepLinkHandler* handler = m_deepLinkModel.Get(data.host);
                if(handler != NULL)
                {
                    handler->HandleDeepLink(data);
                }
            }
        }
    }
}
