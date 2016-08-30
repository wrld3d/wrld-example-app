// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsOpenableControl.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsOpenableControl::MyPinDetailsOpenableControl(Eegeo::Helpers::TIdentity identity,
                                                                     const std::shared_ptr<Reaction::View::IReactionControllerModel>& reactionControllerModel)
                : OpenableControl::View::OpenableControlViewModelBase(reactionControllerModel)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity MyPinDetailsOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
