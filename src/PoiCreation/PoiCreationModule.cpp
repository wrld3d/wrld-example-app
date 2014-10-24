// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationModule.h"

#include "PoiRingController.h"
#include "PoiRingRenderable.h"
#include "PoiRingView.h"
#include "PoiRingTouchController.h"

#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "AsyncLoadersModule.h"
#include "LightingModule.h"
#include "LocalAsyncTextureLoader.h"
#include "TerrainModelModule.h"
#include "TerrainRayPicker.h"

#include "TerrainHeightProvider.h"
#include "CollisionMeshResourceRepository.h"

#include "PoiCreationModel.h"
#include "PoiCreationButtonViewModel.h"
#include "PoiCreationConfirmationViewModel.h"
#include "PoiCreationCompositeViewModel.h"

#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "VertexLayoutPool.h"
#include "VertexBindingPool.h"
#include "VertexBinding.h"
#include "LayerIds.h"

#include "BatchedSpriteShader.h"
#include "BatchedSpriteMaterial.h"
#include "BatchedSpriteRenderable.h"

#include "RenderableFilters.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationModule::PoiCreationModule(MyPins::IMyPinsService& myPinsService,
                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                             ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                                             ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                                             ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                                             ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel)
        {
            
            m_pPoiCreationModel = Eegeo_NEW(PoiCreationModel)(myPinsService);
            
            m_pPoiCreationButtonViewModel = Eegeo_NEW(PoiCreationButtonViewModel)(identityProvider.GetNextIdentity(),
                                                                                  false);
            
            m_pPoiCreationConfirmationViewModel = Eegeo_NEW(PoiCreationConfirmationViewModel)(identityProvider.GetNextIdentity(),
                                                                                              false);
            
            m_pPoiCreationCompositeViewModel = Eegeo_NEW(PoiCreationCompositeViewModel)(*m_pPoiCreationModel,
                                                                                        *m_pPoiCreationButtonViewModel,
                                                                                        *m_pPoiCreationConfirmationViewModel,
                                                                                        primaryMenuViewModel,
                                                                                        secondaryMenuViewModel,
                                                                                        searchQueryPerformer,
                                                                                        searchResultMenuViewModel);
            
        }
        
        PoiCreationModule::~PoiCreationModule()
        {
            Eegeo_DELETE m_pPoiCreationCompositeViewModel;
            Eegeo_DELETE m_pPoiCreationConfirmationViewModel;
            Eegeo_DELETE m_pPoiCreationButtonViewModel;
            Eegeo_DELETE m_pPoiCreationModel;
        }
        
        IPoiCreationModel& PoiCreationModule::GetPoiCreationModel() const
        {
            return *m_pPoiCreationModel;
        }
        
        IPoiCreationButtonViewModel& PoiCreationModule::GetPoiCreationButtonViewModel() const
        {
            return *m_pPoiCreationButtonViewModel;
        }
        
        IPoiCreationConfirmationViewModel& PoiCreationModule::GetPoiCreationConfirmationViewModel() const
        {
            return *m_pPoiCreationConfirmationViewModel;
        }
        
        IPoiCreationCompositeViewModel& PoiCreationModule::GetPoiCreationCompositeViewModel() const
        {
            return *m_pPoiCreationCompositeViewModel;
        }
        
        ScreenControlViewModel::IScreenControlViewModel& PoiCreationModule::GetButtonScreenControlViewModel() const
        {
            return m_pPoiCreationButtonViewModel->GetScreenControlViewModel();
        }
        
        ScreenControlViewModel::IScreenControlViewModel& PoiCreationModule::GetConfirmationScreenControlViewModel() const
        {
            return m_pPoiCreationConfirmationViewModel->GetScreenControlViewModel();
        }
    }
}