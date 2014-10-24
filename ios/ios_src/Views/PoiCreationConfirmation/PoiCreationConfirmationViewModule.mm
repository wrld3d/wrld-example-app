// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "PoiCreationConfirmationViewModule.h"
#include "RenderContext.h"
#include "PoiCreationConfirmationView.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationConfirmationViewModule::PoiCreationConfirmationViewModule(IPoiCreationModel& model,
                                                                             IPoiCreationConfirmationViewModel& viewModel,
                                                                             IPoiCreationCompositeViewModel& compositeViewModel,
                                                                             PoiCreationDetails::IPoiCreationDetailsViewModel& poiCreationDetailsViewModel,
                                                                             const Eegeo::Rendering::ScreenProperties& screenProperties)
        {
            m_pController = [[PoiCreationConfirmationViewController alloc] initWithParams:&model
                                                                                         :&viewModel
                                                                                         :&compositeViewModel
                                                                                         :&poiCreationDetailsViewModel
                                                                                         :&screenProperties];
        }
        
        PoiCreationConfirmationViewModule::~PoiCreationConfirmationViewModule()
        {
            [m_pController release];
        }
        
        PoiCreationConfirmationViewController& PoiCreationConfirmationViewModule::GetPoiCreationConfirmationViewController() const
        {
            return *m_pController;
        }
        
        PoiCreationConfirmationView& PoiCreationConfirmationViewModule::GetPoiCreationConfirmationView() const
        {
            return *[m_pController pPoiCreationConfirmationView];
        }
    }
}
