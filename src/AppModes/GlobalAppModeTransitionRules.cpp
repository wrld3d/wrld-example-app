// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "WorldState.h"
#include "IAppCameraController.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "IAppCameraController.h"
#include "CameraState.h"
#include "RenderCamera.h"
#include "InteriorsCameraController.h"
#include "IUserIdleService.h"
#include "MyPinCreationModel.h"
#include "MyPinCreationStage.h"
#include "GlobalAppModeTransitionRules.h"
#include "AppGlobeCameraWrapper.h"
#include "AppInteriorCameraWrapper.h"
#include "InteriorsExplorerModel.h"
#include "GpsGlobeCameraController.h"
#include "IMyPinsService.h"

#include <limits>

namespace ExampleApp
{
    namespace AppModes
    {
        namespace
        {
            const bool HandleInteriorSelection[] =
                {
                    /*[WorldMode]    =*/ true,
                    /*[InteriorMode] =*/ false,
                    /*[AttractMode]  =*/ true,
                };
            const bool DisablePinCreation[] =
                {
                    /*[WorldMode]    =*/ false,
                    /*[InteriorMode] =*/ true,
                    /*[AttractMode]  =*/ true,
                };
        }

        GlobalAppModeTransitionRules::GlobalAppModeTransitionRules(AppCamera::SdkModel::IAppCameraController& cameraController,
                                                                   ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                   Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                   AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                   AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                                                   AppCamera::SdkModel::AppInteriorCameraWrapper& interiorCameraController,
                                                                   Eegeo::Input::IUserIdleService& userIdleService,
                                                                   const bool attractModeEnabled,
                                                                   const long long attractModeTimeout,
                                                                   MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                                                   MyPins::SdkModel::IMyPinsService& myPinsService)
        : m_cameraController(cameraController)
        , m_appModeModel(appModeModel)
        , m_worldCameraController(worldCameraController)
        , m_interiorCameraController(interiorCameraController)
        , m_interiorsExplorerModel(interiorsExplorerModel)
        , m_interiorSelectionModel(interiorSelectionModel)
        , m_interiorSelectionModelChangedCallback(this, &GlobalAppModeTransitionRules::OnInteriorSelectionModelChanged)
        , m_attractModeTimer(userIdleService, attractModeEnabled ? attractModeTimeout : std::numeric_limits<long long>::max())
        , m_myPinCreationModel(myPinCreationModel)
        , m_worldCameraHandle(m_cameraController.CreateCameraHandleFromController(m_worldCameraController))
        , m_interiorCameraHandle(m_cameraController.CreateCameraHandleFromController(m_interiorCameraController))
        , m_currentState(appModeModel.GetAppMode())
        , m_myPinsService(myPinsService)
        {
        }

        GlobalAppModeTransitionRules::~GlobalAppModeTransitionRules()
        {
            m_cameraController.RemoveCameraHandle(m_worldCameraHandle);
            m_cameraController.RemoveCameraHandle(m_interiorCameraHandle);
        }

        void GlobalAppModeTransitionRules::Enter(int previousState)
        {
            m_currentState = m_appModeModel.GetAppMode();
            if (HandleInteriorSelection[m_currentState])
            {
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
            }
            if (DisablePinCreation[m_currentState])
            {
                m_myPinCreationModel.SetCreationStage(MyPinCreation::Inactive);
            }
        }

        void GlobalAppModeTransitionRules::Update(float dt)
        {
            if (m_attractModeTimer.IsComplete())
            {
                // NOTE: The interiors mode does not exit through the expected, direct route, instead going through
                // an intermediate 'exiting' state which is triggered by a hook in the viewing state's OnInteriorsExplorerExit().
                // The exiting state will never get a chance to run its update function which would normally trigger a camera
                // update and a direct change to WorldMode.  This could potentially cause problems in the future, however exiting
                // the interiors explorer and changing to attract mode here produces the desired behavior currently. JU & CS.
                if (m_interiorSelectionModel.IsInteriorSelected())
                {
                    m_interiorsExplorerModel.Exit();
                }
                m_myPinsService.RemoveAllPins();
                m_appModeModel.SetAppMode(SdkModel::AttractMode);
            }
        }

        void GlobalAppModeTransitionRules::Exit(int nextState)
        {
            if (HandleInteriorSelection[m_currentState])
            {
                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
            }

            SetupCameraForNextMode(m_currentState, static_cast<SdkModel::AppMode>(nextState));
        }

        void GlobalAppModeTransitionRules::OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
        {
            if(m_interiorSelectionModel.IsInteriorSelected())
            {
                m_appModeModel.SetAppMode(SdkModel::InteriorMode);
            }
        }

        void GlobalAppModeTransitionRules::SetupCameraForNextMode(const SdkModel::AppMode currentState, const SdkModel::AppMode nextState)
        {
            if (nextState == SdkModel::AppMode::InteriorMode)
            {
                SetupInteriorCamera();
            }
            else if (nextState == SdkModel::AppMode::WorldMode)
            {
				if (currentState == SdkModel::AppMode::InteriorMode)
				{
					SetupWorldCamera();
				}
            }
        }

        void GlobalAppModeTransitionRules::SetupWorldCamera()
        {
            Eegeo::Space::LatLongAltitude latLong = Eegeo::Space::LatLongAltitude::FromECEF(m_interiorCameraController.GetCameraState().InterestPointEcef());
            const float interestDistance = 500.0f;
            m_worldCameraController.GetGlobeCameraController().SetView(latLong.GetLatitudeInDegrees(), latLong.GetLongitudeInDegrees(),
                                                                       m_interiorCameraController.GetHeadingDegrees(),
                                                                       interestDistance);
        }

        void GlobalAppModeTransitionRules::SetupInteriorCamera()
        {
            Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController = m_interiorCameraController.GetInteriorCameraController();
            interiorsCameraController.SetHeading(m_worldCameraController.GetHeadingDegrees());
        }

        const int GlobalAppModeTransitionRules::GetWorldCameraHandle() const
        {
            return m_worldCameraHandle;
        }

        const int GlobalAppModeTransitionRules::GetInteriorsCameraHandle() const
        {
            return m_interiorCameraHandle;
        }
    }
}
