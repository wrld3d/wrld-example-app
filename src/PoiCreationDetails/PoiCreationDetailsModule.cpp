// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationDetailsModule.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        PoiCreationDetailsModule::PoiCreationDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                           Reaction::IReactionControllerModel& reactionControllerModel)
        {
            m_pPoiCreationDetailsViewModel = Eegeo_NEW(PoiCreationDetailsViewModel)(identityProvider.GetNextIdentity(), reactionControllerModel);
        }
        
        PoiCreationDetailsModule::~PoiCreationDetailsModule()
        {
            Eegeo_DELETE m_pPoiCreationDetailsViewModel;
        }
        
        IPoiCreationDetailsViewModel& PoiCreationDetailsModule::GetPoiCreationDetailsViewModel() const
        {
            return *m_pPoiCreationDetailsViewModel;
        }
        
        OpenableControlViewModel::IOpenableControlViewModel& PoiCreationDetailsModule::GetObservableOpenableControl() const
        {
            return m_pPoiCreationDetailsViewModel->GetOpenableControl();
        }
    }
}