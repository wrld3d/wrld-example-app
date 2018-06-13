// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IOpenableControlViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"
#include "INavWidgetViewModel.h"
#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavUIModule : private Eegeo::NonCopyable
            {
            public:
                NavUIModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                            Menu::View::IMenuIgnoredReactionModel& ignoredMenuReaction);

                ~NavUIModule();

                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;

                INavWidgetViewModel& GetNavWidgetViewModel() const;
                
            private:
                struct m_Private;
                m_Private* m_pImpl;
            };
        }
    }
}
