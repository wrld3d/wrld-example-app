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
        namespace SdkModel
        {
            MyPinCreationModule::MyPinCreationModule(MyPins::SdkModel::IMyPinsService& myPinsService,
                    Eegeo::Helpers::IIdentityProvider& identityProvider,
                    ExampleApp::Menu::View::IMenuViewModel& searchMenuViewModel,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel,
                    Search::SdkModel::ISearchRefreshService& searchRefreshService,
                    ScreenControl::View::IScreenControlViewModel& interiorControlViewModel,
                    Eegeo::Labels::ILabelFilterModel& labelFilterModel,
                    const Eegeo::Labels::LabelLayer::IdType& interiorMarkerLabelLayer,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Reaction::View::IReactionControllerModel& reactionControllerModel,
                    ExampleApp::Watermark::View::IWatermarkViewModel& watermarkViewModel)
            {

                m_pMyPinCreationModel = Eegeo_NEW(MyPinCreationModel)(myPinsService);

                m_pMyPinCreationModelObserver = Eegeo_NEW(MyPinCreationModelObserver)(*m_pMyPinCreationModel, messageBus);

                m_pMyPinCreationViewStateChangedHandler = Eegeo_NEW(MyPinCreationViewStateChangedHandler)(*m_pMyPinCreationModel, searchRefreshService, labelFilterModel, interiorMarkerLabelLayer, messageBus);

                m_pMyPinCreationViewSavePinHandler = Eegeo_NEW(MyPinCreationViewSavePinHandler)(*m_pMyPinCreationModel, messageBus);

                m_pMyPinCreationInitiationViewModel = Eegeo_NEW(View::MyPinCreationInitiationViewModel)(identityProvider.GetNextIdentity(),
                                                      false,
                                                      messageBus);

                m_pMyPinCreationConfirmationViewModel = Eegeo_NEW(View::MyPinCreationConfirmationViewModel)(identityProvider.GetNextIdentity(),
                                                        false,
                                                        reactionControllerModel);

                m_pMyPinCreationCompositeViewModel = Eegeo_NEW(View::MyPinCreationCompositeViewModel)(messageBus,
                                                     *m_pMyPinCreationInitiationViewModel,
                                                     *m_pMyPinCreationConfirmationViewModel,
                                                     searchMenuViewModel,
                                                     settingsMenuViewModel,
                                                     interiorControlViewModel,
                                                     watermarkViewModel);
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

            View::IMyPinCreationInitiationViewModel& MyPinCreationModule::GetMyPinCreationInitiationViewModel() const
            {
                return *m_pMyPinCreationInitiationViewModel;
            }

            View::IMyPinCreationConfirmationViewModel& MyPinCreationModule::GetMyPinCreationConfirmationViewModel() const
            {
                return *m_pMyPinCreationConfirmationViewModel;
            }

            View::IMyPinCreationCompositeViewModel& MyPinCreationModule::GetMyPinCreationCompositeViewModel() const
            {
                return *m_pMyPinCreationCompositeViewModel;
            }

            ScreenControl::View::IScreenControlViewModel& MyPinCreationModule::GetInitiationScreenControlViewModel() const
            {
                return m_pMyPinCreationInitiationViewModel->GetScreenControlViewModel();
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
