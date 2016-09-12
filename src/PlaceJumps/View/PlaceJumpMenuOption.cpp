// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PlaceJumpMenuOption.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace View
        {
            PlaceJumpMenuOption::PlaceJumpMenuOption(PlaceJumpModel jumpModel,
                                                     const std::shared_ptr<Menu::View::IMenuViewModel>& menuViewModel,
                                                     const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                     const std::shared_ptr<Metrics::IMetricsService>& metricsService,
                                                     const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReaction)
                : m_jumpModel(jumpModel)
                , m_menuViewModel(menuViewModel)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_menuReaction(menuReaction)
            {
            }

            void PlaceJumpMenuOption::Select()
            {
                m_metricsService->SetEvent("UIItem: Placejump", "Name", m_jumpModel.GetName().c_str());
                
                if (m_menuReaction->GetShouldCloseMenu())
                {
                    m_menuViewModel->Close();
                }
                
                m_messageBus->Publish(PlaceJumpSelectedMessage(m_jumpModel));
            }
        }
    }
}
