// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingCustomLocationPicker.h"
#include "IAppCameraLocationPicker.h"
#include "AppCameraLocationPicker.h"
#include "NavRoutingLocationModel.h"
#include "INavRoutingModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingCustomLocationPicker::NavRoutingCustomLocationPicker(
                    INavRoutingModel& navRoutingModel,
                    AppCamera::SdkModel::IAppCameraLocationPicker& cameraLocationPicker
            )
            : m_navRoutingModel(navRoutingModel)
            , m_cameraLocationPicker(cameraLocationPicker)
            , m_isSearching(false)
            , m_isStartLocation(false)
            {
            }

            NavRoutingCustomLocationPicker::~NavRoutingCustomLocationPicker()
            {
            }

            void NavRoutingCustomLocationPicker::StartSearching(bool forStartLocation)
            {
                m_isSearching = true;
                m_isStartLocation = forStartLocation;
            }

            void NavRoutingCustomLocationPicker::StopSearching()
            {
                m_isSearching = false;
            }

            bool NavRoutingCustomLocationPicker::HandleTouchTap(float screenX, float screenY)
            {
                if(!m_isSearching)
                {
                    return false;
                }

                AppCamera::SdkModel::AppCameraLocationPickerResult result = m_cameraLocationPicker.PickLocation(screenX, screenY);
                if(!result.IsValidResult())
                {
                    return true;
                }

                NavRoutingLocationModel locationModel("Custom location",
                                                      result.GetLocation(),
                                                      result.IsIndoors(),
                                                      result.GetIndoorId(),
                                                      result.GetIndoorFloorNumber());
                if(m_isStartLocation)
                {
                    m_navRoutingModel.SetStartLocation(locationModel);
                }
                else
                {
                    m_navRoutingModel.SetEndLocation(locationModel);
                }

                return true;
            }
        }
    }
}
