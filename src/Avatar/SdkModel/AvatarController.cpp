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
            
            void AvatarController::SetModelTarget(const Eegeo::Space::LatLong& latLong, const Eegeo::Resources::Interiors::InteriorId& building, int floor)
            {
                // Directly set position if it wasn't showing previously
                if(!ShouldShowAvatar())
                {
                    m_avatarModel.SetPosition(latLong);
                    m_avatarView.SetLatLongHeading(m_avatarModel.GetPosition(), m_avatarModel.GetHeading());
                }
                // Update building and floor
                m_avatarModel.SetInteriorId(building);
                m_avatarModel.SetFloor(floor);
                
                if(floor == m_interiorInteractionModel.GetSelectedFloorIndex()){
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
                }else{
                    if(m_avatarView.IsShowingAvatar())
                    {
                        Eegeo::Space::LatLong latLong1(0.0f,0.0f);
                        m_avatarModel.SetPosition(latLong1);
                        m_avatarModel.SetTargetPosition(latLong1);
                        m_avatarView.HideAvatar();
                    }
                }
                m_avatarModel.SetAvatarStatus(m_avatarView.IsShowingAvatar());

                
                
            }
            
            void AvatarController::Update(float dt)
            {
                UpdateAvatarVisibility();
                if(m_avatarModel.GetFloor() == m_interiorInteractionModel.GetSelectedFloorIndex()){
                    if(!ShouldShowAvatar())
                    {
                        return;
                    }
                    if((m_interiorInteractionModel.GetInteriorModel()!= NULL) && m_avatarModel.GetInteriorId() != m_interiorInteractionModel.GetInteriorModel()->GetId())
                    {
                        m_avatarView.HideAvatar();
                        return;
                        
                    }
                    
                    m_avatarModel.Update(dt);
                    
                    if(m_avatarModel.DestinationReached())
                    {
                        m_avatarView.StopMoving();
                    }
                    else
                    {
//                        printf("Lat: %f , Lng: %f \n",m_avatarModel.GetPosition().GetLatitudeInDegrees(), m_avatarModel.GetPosition().GetLongitudeInDegrees());

                        m_avatarView.SetLatLongHeading(m_avatarModel.GetPosition(), m_avatarModel.GetHeading());
                    }
                
                }else{
                    if(m_avatarView.IsShowingAvatar())
                    {
//                        Eegeo::Space::LatLong latLong1(0.0f,0.0f);
//                        m_avatarModel.SetPosition(latLong1);
//                        m_avatarModel.SetTargetPosition(latLong1);
                        
                        m_avatarModel.ResetAvatarModel();
                        m_avatarView.HideAvatar();
                    }
                }

            }
            
            void AvatarController::OnAppModeChanged()
            {
                UpdateAvatarVisibility();
            }
                   
            bool AvatarController::ShouldShowAvatar()
            {
                return m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode;
            }
            
            void AvatarController::UpdateAvatarVisibility()
            {
                if(!ShouldShowAvatar())
                {
                    if(m_avatarView.IsShowingAvatar())
                    {
                        m_avatarView.HideAvatar();
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