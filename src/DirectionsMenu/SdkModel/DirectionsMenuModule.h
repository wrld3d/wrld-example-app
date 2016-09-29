// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IDirectionsMenuModule.h"

#include <vector>

#include "BidirectionalBus.h"
#include "IIdentity.h"
#include "Metrics.h"
#include "Reaction.h"
#include "DirectionsMenu.h"
#include "Types.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            class DirectionsMenuModule : public IDirectionsMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuViewModel* m_pMenuViewModel;
                Menu::View::IMenuSectionViewModel* m_pSearchSectionViewModel;

            public:
                DirectionsMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                 ExampleApp::Reaction::View::IReactionControllerModel& reactionControllerModel,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                 Metrics::IMetricsService& metricsService);
                
                
                ~DirectionsMenuModule();
                
                void SetDirectionsSection(const std::string& name,
                                      Menu::View::IMenuModel& menuModel);

                Menu::View::IMenuModel& GetDirectionsMenuModel() const;
                
                Menu::View::IMenuViewModel& GetDirectionsMenuViewModel() const;
                Menu::View::IMenuSectionViewModel& GetDirectionsSectionViewModel() const;
            };
        }
    }
}