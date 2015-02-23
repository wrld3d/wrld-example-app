// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsModule.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            MyPinCreationDetailsModule::MyPinCreationDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                    Reaction::View::IReactionControllerModel& reactionControllerModel)
            {
                m_pMyPinCreationDetailsViewModel = Eegeo_NEW(MyPinCreationDetailsViewModel)(identityProvider.GetNextIdentity(), reactionControllerModel);
            }

            MyPinCreationDetailsModule::~MyPinCreationDetailsModule()
            {
                Eegeo_DELETE m_pMyPinCreationDetailsViewModel;
            }

            IMyPinCreationDetailsViewModel& MyPinCreationDetailsModule::GetMyPinCreationDetailsViewModel() const
            {
                return *m_pMyPinCreationDetailsViewModel;
            }

            OpenableControl::View::IOpenableControlViewModel& MyPinCreationDetailsModule::GetObservableOpenableControl() const
            {
                return m_pMyPinCreationDetailsViewModel->GetOpenableControl();
            }
        }
    }
}
