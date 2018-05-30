// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavUIModule.h"
#include "OpenableControlViewModelBase.h"
#include "NavWidgetViewModel.h"

namespace
{
    //This is stupid there are many implementations of this class that are identical bar the name!
    class OpenableControlViewModel_lt: public ExampleApp::OpenableControl::View::OpenableControlViewModelBase
    {
        Eegeo::Helpers::TIdentity m_identity;
    public:
        OpenableControlViewModel_lt(Eegeo::Helpers::TIdentity identity):
        ExampleApp::OpenableControl::View::OpenableControlViewModelBase(),
        m_identity(identity)
        {
            
        }
        
        Eegeo::Helpers::TIdentity GetIdentity() const override
        {
            return m_identity;
        }
    };
}

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            struct NavUIModule::Private
            {
                OpenableControlViewModel_lt openable;
                
                Private(Eegeo::Helpers::IIdentityProvider& identityProvider)
                        : openable(identityProvider.GetNextIdentity())
                {
                    
                }
            };
            
            NavUIModule::NavUIModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                     Menu::View::IMenuIgnoredReactionModel& ignoredMenuReaction):
                d(new Private(identityProvider))
            {
                m_pNavWidgetViewModel = Eegeo_NEW(NavWidgetViewModel)(identityProvider.GetNextIdentity());
                ignoredMenuReaction.AddIgnoredMenuIdentity(m_pNavWidgetViewModel->GetOpenableControl().GetIdentity());
            }

            NavUIModule::~NavUIModule()
            {
                Eegeo_DELETE m_pNavWidgetViewModel;
                delete d;
            }

            OpenableControl::View::IOpenableControlViewModel& NavUIModule::GetObservableOpenableControl() const
            {
                return m_pNavWidgetViewModel->GetOpenableControl();
            }

            INavWidgetViewModel& NavUIModule::GetNavWidgetViewModel() const
            {
                return *m_pNavWidgetViewModel;
            }
        }
    }
}
