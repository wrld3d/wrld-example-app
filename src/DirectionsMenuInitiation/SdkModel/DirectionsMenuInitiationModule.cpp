// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuInitiationModule.h"
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
#include "DirectionsMenuInitiationViewModel.h"
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
    namespace DirectionsMenuInitiation
    {
        namespace SdkModel
        {
            DirectionsMenuInitiationModule::DirectionsMenuInitiationModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                           ExampleApp::Menu::View::IMenuViewModel& searchMenuViewModel,
                                           ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel,
                                           ScreenControl::View::IScreenControlViewModel& interiorControlViewModel,
                                           ExampleAppMessaging::TMessageBus& messageBus,
                                           Reaction::View::IReactionControllerModel& reactionControllerModel)
            {
                m_pDirectionsMenuInitiationViewModel = Eegeo_NEW(View::DirectionsMenuInitiationViewModel)(identityProvider.GetNextIdentity(),
                                                                                                        false);
            }
            
            DirectionsMenuInitiationModule::~DirectionsMenuInitiationModule()
            {
                Eegeo_DELETE m_pDirectionsMenuInitiationViewModel;
            }

            View::IDirectionsMenuInitiationViewModel& DirectionsMenuInitiationModule::GetDirectionsMenuInitiationViewModel() const{
                
                return *m_pDirectionsMenuInitiationViewModel;
            }
            
            ScreenControl::View::IScreenControlViewModel& DirectionsMenuInitiationModule::GetInitiationScreenControlViewModel() const
            {
                return m_pDirectionsMenuInitiationViewModel->GetScreenControlViewModel();
            }
        }
    }
}
