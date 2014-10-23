// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "FlattenButtonViewModule.h"
#include "RenderContext.h"
#include "FlattenButtonView.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        FlattenButtonViewModule::FlattenButtonViewModule(IFlattenButtonModel& model,
                                                         IFlattenButtonViewModel& viewModel,
                                                         const Eegeo::Rendering::ScreenProperties& screenProperties)
        {
            m_pView = [[FlattenButtonView alloc] initWithDimensions
                       :screenProperties.GetScreenWidth()
                       :screenProperties.GetScreenHeight()
                       :screenProperties.GetPixelScale()
                       ];
            
            m_pController = [[FlattenButtonViewController alloc] initWithParams:&viewModel
                                                                               :&model
                                                                               :m_pView];
        }
        
        FlattenButtonViewModule::~FlattenButtonViewModule()
        {
            [m_pController release];
            [m_pView release];
        }
        
        FlattenButtonViewController& FlattenButtonViewModule::GetFlattenButtonViewController() const
        {
            return *m_pController;
        }
        
        FlattenButtonView& FlattenButtonViewModule::GetFlattenButtonView() const
        {
            return *m_pView;
        }
    }
}
