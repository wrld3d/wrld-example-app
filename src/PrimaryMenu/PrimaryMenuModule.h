// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IPrimaryMenuModule.h"
#include "IIdentity.h"
#include "PlaceJumps.h"
#include "AboutPage.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        class PrimaryMenuModule: public IPrimaryMenuModule, private Eegeo::NonCopyable
        {
        private:
            Menu::IMenuModel* m_pModel;
            Menu::IMenuOptionsModel* m_pMenuOptionsModel;
            Menu::IMenuViewModel* m_pViewModel;
            
            Menu::IMenuSectionViewModel* m_pMenuSectionMisc;
            
        public:
            PrimaryMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                              AboutPage::IAboutPageViewModel& aboutPageViewModel,
                              Reaction::IReactionControllerModel& reactionControllerModel);
            
            ~PrimaryMenuModule();
            
            Menu::IMenuModel& GetPrimaryMenuModel() const;
            
            Menu::IMenuOptionsModel& GetPrimaryMenuOptionsModel() const;
            
            Menu::IMenuViewModel& GetPrimaryMenuViewModel() const;
        };
    }
}
