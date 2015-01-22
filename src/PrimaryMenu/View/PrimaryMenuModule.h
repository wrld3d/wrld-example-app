// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IPrimaryMenuModule.h"
#include "IIdentity.h"
#include "PlaceJumps.h"
#include "AboutPage.h"
#include "Reaction.h"

#include <vector>
#include <string>

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        namespace View
        {
            class PrimaryMenuModule: public IPrimaryMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                Menu::View::IMenuViewModel* m_pViewModel;

                std::vector<Menu::View::IMenuSectionViewModel*> m_sections;

                Menu::View::IMenuSectionViewModel* m_pMenuSectionMisc;

            public:
                PrimaryMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                  AboutPage::View::IAboutPageViewModel& aboutPageViewModel,
                                  Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~PrimaryMenuModule();

                void AddMenuSection(const std::string& name, const std::string& icon, Menu::View::IMenuModel& menuModel, bool isExpandable);

                Menu::View::IMenuModel& GetPrimaryMenuModel() const;

                Menu::View::IMenuOptionsModel& GetPrimaryMenuOptionsModel() const;

                Menu::View::IMenuViewModel& GetPrimaryMenuViewModel() const;
            };
        }
    }
}
