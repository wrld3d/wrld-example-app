// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsModule.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        MyPinCreationDetailsModule::MyPinCreationDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                           Reaction::IReactionControllerModel& reactionControllerModel)
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
        
        OpenableControlViewModel::IOpenableControlViewModel& MyPinCreationDetailsModule::GetObservableOpenableControl() const
        {
            return m_pMyPinCreationDetailsViewModel->GetOpenableControl();
        }
    }
}