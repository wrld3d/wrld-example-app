// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AvatarController.h"

#include "InteriorController.h"
#include "InteriorsFloorModel.h"
#include "InteriorsModel.h"
#include "LatLongAltitude.h"
#include "IAvatarView.h"
#include "IAvatarModel.h"

#include "InteriorsFloorModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorHeightHelpers.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            AvatarController::AvatarController(IAvatarView& avatarView,
                                               IAvatarModel& avatarModel,
                                               Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                               Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                               ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel)
            : m_avatarView(avatarView)
            , m_avatarModel(avatarModel)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_appModeModel(appModeModel)
            , m_appModeChangedCallback(this, &AvatarController::OnAppModeChanged)
            , m_environmentFlatteningService(environmentFlatteningService)
            {
                m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
                
                UpdateAvatarVisibility();
            }
            
            AvatarController::~AvatarController()
            {
                m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
            }
            
            void AvatarController::SetModelTarget(const Eegeo::Space::LatLong& latLong, const Eegeo::Resources::Interiors::InteriorId& building, int floor, bool isBlueToothEnabled)
            {
                m_isBlueToothEnabled = isBlueToothEnabled;
                
                // Update building and floor
                m_avatarModel.SetInteriorId(building);
                m_avatarModel.SetFloor(floor);
                m_avatarModel.SetAvatarStatus(m_avatarView.IsShowingAvatar());
                
                // If still not supposed to show don't do anything else
                if(!ShouldShowAvatar())
                {
                    return;
                }
                float heightAboveSeaLevel = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevelIncludingEnvironmentFlattening(*m_interiorInteractionModel.GetInteriorModel(), m_interiorInteractionModel.GetSelectedFloorIndex(), m_environmentFlatteningService.GetCurrentScale());
                
                if((building.Value() == "swallow_lon_citygatehouse" || building.Value() == "westport_house") && m_interiorInteractionModel.GetSelectedFloorIndex() == floor){ // here check interior and floor for height offset
                    m_avatarView.SetHeightAboveSeaLevel(heightAboveSeaLevel+0.26); // #workaround to resolve floor height issue. Might need to look some offset factor for better solution
                }else{
                    m_avatarView.SetHeightAboveSeaLevel(heightAboveSeaLevel);
                }
                
                m_avatarModel.SetTargetPosition(latLong);
                
                m_avatarView.SetLatLongHeading(m_avatarModel.GetPosition(), m_avatarModel.GetHeading());
                
                if(!m_avatarModel.DestinationReached())
                {
                    m_avatarView.StartMoving();
                }
            }
            
            void AvatarController::Update(float dt)
            {
                UpdateAvatarVisibility();
                
                if(!ShouldShowAvatar())
                {
                    return;
                }
                m_avatarModel.Update(dt);
                
                if(m_avatarModel.DestinationReached())
                {
                    m_avatarView.StopMoving();
                }
                else
                {
                    m_avatarView.SetLatLongHeading(m_avatarModel.GetPosition(), m_avatarModel.GetHeading());
                }
                
            }
            
            void AvatarController::OnAppModeChanged()
            {
                UpdateAvatarVisibility();
            }
                   
            bool AvatarController::ShouldShowAvatar()
            {
                return m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode &&
                m_isBlueToothEnabled &&
                m_interiorInteractionModel.GetInteriorModel()!= NULL &&
                m_avatarModel.GetInteriorId() == m_interiorInteractionModel.GetInteriorModel()->GetId()&&
                m_avatarModel.GetFloor() == m_interiorInteractionModel.GetSelectedFloorIndex();
            }
            
            void AvatarController::UpdateAvatarVisibility()
            {
                if(!ShouldShowAvatar())
                {
                    if(m_avatarView.IsShowingAvatar())
                    {
                        m_avatarView.HideAvatar();
                        m_avatarModel.ResetAvatarModel();
                    }
                }
                else
                {
                    if(!m_avatarView.IsShowingAvatar())
                    {
                        m_avatarView.ShowAvatar();
                    }
                }                                               
            }
        }
    }
}