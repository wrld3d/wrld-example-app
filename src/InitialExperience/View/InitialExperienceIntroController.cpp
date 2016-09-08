// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroController.h"
#include "IInitialExperienceIntroView.h"
#include "InitialExperienceIntroDismissedMessage.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            InitialExperienceIntroController::InitialExperienceIntroController(const std::shared_ptr<IInitialExperienceIntroView>& view,
                                                                               const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
            : m_view(view)
            , m_messageBus(messageBus)
            , m_showIntroMessageHandler(this, &InitialExperienceIntroController::OnShowIntro)
            , m_viewDismissed(this, &InitialExperienceIntroController::OnViewDismissed)
            {
                m_view->InsertDismissedCallback(m_viewDismissed);
                m_messageBus->SubscribeUi(m_showIntroMessageHandler);
            }
            
            InitialExperienceIntroController::~InitialExperienceIntroController()
            {
                m_messageBus->UnsubscribeUi(m_showIntroMessageHandler);
                m_view->RemoveDismissedCallback(m_viewDismissed);
            }
            
            void InitialExperienceIntroController::OnShowIntro(const ShowInitialExperienceIntroMessage& message)
            {
                m_view->Show();
            }
            
            void InitialExperienceIntroController::OnViewDismissed()
            {
                m_messageBus->Publish(InitialExperienceIntroDismissedMessage());
            }

        }
    }
}