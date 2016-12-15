// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AboutPage.h"
#include "IAboutPageModule.h"
#include "AboutPageViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class AboutPageModule : public IAboutPageModule, private Eegeo::NonCopyable
            {
                AboutPageViewModel* m_pAboutPageViewModel;

            public:
                AboutPageModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                Reaction::View::IReactionControllerModel& reactionControllerModel,
                                const std::string& buildVersion,
                                const std::string& appName);

                ~AboutPageModule();

                IAboutPageViewModel& GetAboutPageViewModel() const;

                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;
            };
        }
    }
}
