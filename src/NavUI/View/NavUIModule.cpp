// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavUIModule.h"
#include "OpenableControlViewModelBase.h"

namespace
{
    //This is stupid there are many implementations of this class that are identical bar the name!
    class OpenableControlViewModel_lt: public ExampleApp::OpenableControl::View::OpenableControlViewModelBase
    {
        Eegeo::Helpers::TIdentity m_identity;
    public:
        OpenableControlViewModel_lt(ExampleApp::Reaction::View::IReactionControllerModel& reactionControllerModel,
                                    Eegeo::Helpers::TIdentity identity):
        ExampleApp::OpenableControl::View::OpenableControlViewModelBase(reactionControllerModel),
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
    namespace NavUI
    {
        namespace View
        {
            struct NavUIModule::Private
            {
                OpenableControlViewModel_lt openable;
                
                Private(Eegeo::Helpers::IIdentityProvider& identityProvider,
                        Reaction::View::IReactionControllerModel& reactionControllerModel):
                    openable(reactionControllerModel, identityProvider.GetNextIdentity())
                {
                    
                }
            };
            
            NavUIModule::NavUIModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                     Reaction::View::IReactionControllerModel& reactionControllerModel):
                d(new Private(identityProvider, reactionControllerModel))
            {

            }

            NavUIModule::~NavUIModule()
            {
                delete d;
            }

            OpenableControl::View::IOpenableControlViewModel& NavUIModule::GetObservableOpenableControl() const
            {
                return d->openable;
            }
        }
    }
}
