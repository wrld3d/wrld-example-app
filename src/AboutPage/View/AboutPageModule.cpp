// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageModule.h"
#include "AboutPageViewModel.h"
#include "EegeoWorld.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageModule::AboutPageModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                             Reaction::View::IReactionControllerModel& reactionControllerModel,
                                             const std::string& buildVersion,
                                             const std::string& appName)
            {
                std::string platformRuntimeArchitecture = (sizeof(void*) == 4) ? "32-bit" : "64-bit";
                m_pAboutPageViewModel = Eegeo_NEW(AboutPageViewModel)(identityProvider.GetNextIdentity(), reactionControllerModel, buildVersion, EEGEO_PLATFORM_VERSION_NUMBER, EEGEO_PLATFORM_VERSION_HASH, platformRuntimeArchitecture, "", appName);
            }

            AboutPageModule::~AboutPageModule()
            {
                Eegeo_DELETE m_pAboutPageViewModel;
            }

            IAboutPageViewModel& AboutPageModule::GetAboutPageViewModel() const
            {
                return *m_pAboutPageViewModel;
            }

            OpenableControl::View::IOpenableControlViewModel& AboutPageModule::GetObservableOpenableControl() const
            {
                return m_pAboutPageViewModel->GetOpenableControl();
            }
        }
    }
}
