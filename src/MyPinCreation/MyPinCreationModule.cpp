// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationModule.h"

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

#include "CollisionMeshResourceRepository.h"

#include "MyPinCreationModel.h"
#include "MyPinCreationInitiationViewModel.h"
#include "MyPinCreationConfirmationViewModel.h"
#include "MyPinCreationCompositeViewModel.h"

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
    namespace MyPinCreation
    {
        MyPinCreationModule::MyPinCreationModule(MyPins::IMyPinsService& myPinsService,
                                                 Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                 ExampleApp::Menu::IMenuViewModel& primaryMenuViewModel,
                                                 ExampleApp::Menu::IMenuViewModel& secondaryMenuViewModel,
                                                 ExampleApp::Search::ISearchQueryPerformer& searchQueryPerformer,
                                                 ExampleApp::Menu::IMenuViewModel& searchResultMenuViewModel,
                                                 ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
                                                 ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
        {
            
            m_pMyPinCreationModel = Eegeo_NEW(MyPinCreationModel)(myPinsService);
            
            m_pMyPinCreationModelObserver = Eegeo_NEW(MyPinCreationModelObserver)(*m_pMyPinCreationModel, nativeToUiMessageBus);
            
            m_pMyPinCreationViewStateChangedHandler = Eegeo_NEW(MyPinCreationViewStateChangedHandler)(*m_pMyPinCreationModel, uiToNativeMessageBus);
            
            m_pMyPinCreationViewSavePinHandler = Eegeo_NEW(MyPinCreationViewSavePinHandler)(*m_pMyPinCreationModel, uiToNativeMessageBus);
            
            m_pMyPinCreationInitiationViewModel = Eegeo_NEW(MyPinCreationInitiationViewModel)(identityProvider.GetNextIdentity(),
                                                                                              false);
            
            m_pMyPinCreationConfirmationViewModel = Eegeo_NEW(MyPinCreationConfirmationViewModel)(identityProvider.GetNextIdentity(),
                                                                                                  false);
            
            m_pMyPinCreationCompositeViewModel = Eegeo_NEW(MyPinCreationCompositeViewModel)(nativeToUiMessageBus,
                                                                                            *m_pMyPinCreationInitiationViewModel,
                                                                                            *m_pMyPinCreationConfirmationViewModel,
                                                                                            primaryMenuViewModel,
                                                                                            secondaryMenuViewModel,
                                                                                            searchQueryPerformer,
                                                                                            searchResultMenuViewModel);
            
        }
        
        MyPinCreationModule::~MyPinCreationModule()
        {
            Eegeo_DELETE m_pMyPinCreationCompositeViewModel;
            Eegeo_DELETE m_pMyPinCreationConfirmationViewModel;
            Eegeo_DELETE m_pMyPinCreationInitiationViewModel;
            Eegeo_DELETE m_pMyPinCreationModel;
        }
        
        IMyPinCreationModel& MyPinCreationModule::GetMyPinCreationModel() const
        {
            return *m_pMyPinCreationModel;
        }
        
        IMyPinCreationInitiationViewModel& MyPinCreationModule::GetMyPinCreationInitiationViewModel() const
        {
            return *m_pMyPinCreationInitiationViewModel;
        }
        
        IMyPinCreationConfirmationViewModel& MyPinCreationModule::GetMyPinCreationConfirmationViewModel() const
        {
            return *m_pMyPinCreationConfirmationViewModel;
        }
        
        IMyPinCreationCompositeViewModel& MyPinCreationModule::GetMyPinCreationCompositeViewModel() const
        {
            return *m_pMyPinCreationCompositeViewModel;
        }
        
        ScreenControlViewModel::IScreenControlViewModel& MyPinCreationModule::GetInitiationScreenControlViewModel() const
        {
            return m_pMyPinCreationInitiationViewModel->GetScreenControlViewModel();
        }
        
        ScreenControlViewModel::IScreenControlViewModel& MyPinCreationModule::GetConfirmationScreenControlViewModel() const
        {
            return m_pMyPinCreationConfirmationViewModel->GetScreenControlViewModel();
        }
    }
}