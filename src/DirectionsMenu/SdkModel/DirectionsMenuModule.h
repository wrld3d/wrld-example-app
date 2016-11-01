// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IDirectionsMenuModule.h"
#include "BidirectionalBus.h"
#include "IIdentity.h"
#include "Reaction.h"
#include "DirectionsMenu.h"
#include "Types.h"
#include "DirectionMenuFindDirectionMessageHandler.h"
#include "FindDirectionQueryPerformer.h"
#include "DirectionMenuGeoNameMessageHandler.h"
#include "GeoNamesSearchService.h"

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
                
                DirectionMenuFindDirectionMessageHandler* m_pFindDirectionMessageHandler;
                DirectionMenuGeoNameMessageHandler* m_pGetGeoNamesDirectionMessageHandler;

            public:
                DirectionsMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                 ExampleApp::Reaction::View::IReactionControllerModel& reactionControllerModel,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                     ExampleApp::Direction::SdkModel::FindDirectionQueryPerformer& findDirectionQueryPerformer,
                                     ExampleApp::Search::GeoNames::SdkModel::GeoNamesSearchService &geoNameSearchService);
                
                
                ~DirectionsMenuModule();
                
                void SetDirectionsSection(const std::string& name,
                                      Menu::View::IMenuModel& menuModel);
                void DeleteSearchSectionViewModel();

                Menu::View::IMenuModel& GetDirectionsMenuModel() const;
                
                Menu::View::IMenuViewModel& GetDirectionsMenuViewModel() const;
                Menu::View::IMenuSectionViewModel& GetDirectionsSectionViewModel() const;
            };
        }
    }
}