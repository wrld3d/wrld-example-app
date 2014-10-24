// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationDetailsViewModule.h"
#include "PoiCreationDetailsViewController.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        PoiCreationDetailsViewModule::PoiCreationDetailsViewModule(PoiCreation::IPoiCreationModel& poiCreationModel,
                                                                   IPoiCreationDetailsViewModel& poiCreationDetailsViewModel)
        {
            m_pController = [[PoiCreationDetailsViewController alloc] initWithParams:&poiCreationModel
                                                                                    :&poiCreationDetailsViewModel];
        }
        
        PoiCreationDetailsViewModule::~PoiCreationDetailsViewModule()
        {
            [m_pController release];
        }
        
        PoiCreationDetailsViewController& PoiCreationDetailsViewModule::GetPoiCreationDetailsViewController() const
        {
            return *m_pController;
        }
        
        PoiCreationDetailsView& PoiCreationDetailsViewModule::GetPoiCreationDetailsView() const
        {
            return *[m_pController pPoiCreationDetailsView];
        }
    }
}