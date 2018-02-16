// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

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

#include "MyPinCreationMenuOption.h"
#include "MyPinCreation.h"
#include "MenuOptionsModel.h"
#include "MenuModel.h"

#include "RenderableFilters.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            MyPinCreationModule::MyPinCreationModule(MyPins::SdkModel::IMyPinsService& myPinsService,
                    Eegeo::Helpers::IIdentityProvider& identityProvider,
                    ExampleApp::Menu::View::IMenuViewModel& menuViewModel,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Search::SdkModel::ISearchRefreshService& searchRefreshService,
                    ScreenControl::View::IScreenControlViewModel& interiorControlViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Reaction::View::IReactionControllerModel& reactionControllerModel)
            {

                m_pMyPinCreationModel = Eegeo_NEW(MyPinCreationModel)(myPinsService);

                m_pMyPinCreationModelObserver = Eegeo_NEW(MyPinCreationModelObserver)(*m_pMyPinCreationModel, messageBus);

                m_pMyPinCreationViewStateChangedHandler = Eegeo_NEW(MyPinCreationViewStateChangedHandler)(*m_pMyPinCreationModel, searchRefreshService, messageBus);

                m_pMyPinCreationViewSavePinHandler = Eegeo_NEW(MyPinCreationViewSavePinHandler)(*m_pMyPinCreationModel, messageBus);


                m_pMyPinCreationConfirmationViewModel = Eegeo_NEW(View::MyPinCreationConfirmationViewModel)(identityProvider.GetNextIdentity(),
                                                        false,
                                                        reactionControllerModel);

                m_pMyPinCreationCompositeViewModel = Eegeo_NEW(View::MyPinCreationCompositeViewModel)(messageBus,
                                                     *m_pMyPinCreationConfirmationViewModel,
                                                     menuViewModel,
                                                     interiorControlViewModel);
                
                
                m_pMyPinCreationMenuModel        = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMyPinCreationMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMyPinCreationMenuModel);
                m_pMyPinCreationMenuOptionsModel->AddItem("Create Pin", "Create Pin", "", "", Eegeo_NEW(View::MyPinCreationMenuOption)(menuViewModel,*m_pMyPinCreationConfirmationViewModel));
                
            }

            MyPinCreationModule::~MyPinCreationModule()
            {
                Eegeo_DELETE m_pMyPinCreationMenuOptionsModel;
                Eegeo_DELETE m_pMyPinCreationMenuModel;
                Eegeo_DELETE m_pMyPinCreationCompositeViewModel;
                Eegeo_DELETE m_pMyPinCreationConfirmationViewModel;
                Eegeo_DELETE m_pMyPinCreationModel;
            }

            IMyPinCreationModel& MyPinCreationModule::GetMyPinCreationModel() const
            {
                return *m_pMyPinCreationModel;
            }


            View::IMyPinCreationConfirmationViewModel& MyPinCreationModule::GetMyPinCreationConfirmationViewModel() const
            {
                return *m_pMyPinCreationConfirmationViewModel;
            }

            View::IMyPinCreationCompositeViewModel& MyPinCreationModule::GetMyPinCreationCompositeViewModel() const
            {
                return *m_pMyPinCreationCompositeViewModel;
            }

            ScreenControl::View::IScreenControlViewModel& MyPinCreationModule::GetConfirmationScreenControlViewModel() const
            {
                return m_pMyPinCreationConfirmationViewModel->GetScreenControlViewModel();
            }

            OpenableControl::View::IOpenableControlViewModel& MyPinCreationModule::GetObservableOpenableControl() const
            {
                return m_pMyPinCreationConfirmationViewModel->GetOpenableControlViewModel();
            }
        }
    }
}
