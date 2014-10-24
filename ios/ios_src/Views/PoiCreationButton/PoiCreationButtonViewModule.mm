// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "PoiCreationButtonViewModule.h"
#include "RenderContext.h"
#include "PoiCreationButtonView.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationButtonViewModule::PoiCreationButtonViewModule(IPoiCreationModel& model,
                                                                 IPoiCreationButtonViewModel& viewModel,
                                                                 const Eegeo::Rendering::ScreenProperties& screenProperties)
        {
            m_pController = [[PoiCreationButtonViewController alloc] initWithParams:&model
                                                                             :&viewModel
                                                                             :&screenProperties];
        }
        
        PoiCreationButtonViewModule::~PoiCreationButtonViewModule()
        {
            [m_pController release];
        }
        
        PoiCreationButtonViewController& PoiCreationButtonViewModule::GetPoiCreationButtonViewController() const
        {
            return *m_pController;
        }
        
        PoiCreationButtonView& PoiCreationButtonViewModule::GetPoiCreationButtonView() const
        {
            return *[m_pController pPoiCreationButtonView];
        }
    }
}
