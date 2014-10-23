// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassModule.h"
#include "CompassViewModel.h"
#include "CompassModel.h"
#include "CompassUpdateController.h"

namespace ExampleApp
{
    namespace Compass
    {
        CompassModule::CompassModule(Eegeo::Location::NavigationService& navigationService,
                                     Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
                                     Eegeo::Helpers::IIdentityProvider& identityProvider)
        {
            m_pModel = Eegeo_NEW(CompassModel)(navigationService, cameraController);
            m_pViewModel = Eegeo_NEW(CompassViewModel)(*m_pModel, identityProvider.GetNextIdentity(), false);
            m_pCompassUpdateController = Eegeo_NEW(CompassUpdateController)(*m_pModel, *m_pViewModel, navigationService);
        }
        
        CompassModule::~CompassModule()
        {
            Eegeo_DELETE m_pCompassUpdateController;
            Eegeo_DELETE m_pViewModel;
            Eegeo_DELETE m_pModel;
        }
        
        ICompassModel& CompassModule::GetCompassModel() const
        {
            return *m_pModel;
        }
        
        ICompassViewModel& CompassModule::GetCompassViewModel() const
        {
            return *m_pViewModel;
        }
        
        ICompassUpdateController& CompassModule::GetCompassUpdateController() const
        {
            return *m_pCompassUpdateController;
        }
        
        ScreenControlViewModel::IScreenControlViewModel& CompassModule::GetScreenControlViewModel() const
        {
            return m_pViewModel->GetScreenControlViewModel();
        }
    }
}
