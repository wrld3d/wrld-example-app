// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassUpdateController.h"
#include "CompassModel.h"
#include "CompassViewModel.h"
#include "NavigationService.h"

namespace ExampleApp
{
    namespace Compass
    {
        CompassUpdateController::CompassUpdateController(ICompassModel& model,
                                                         ICompassViewModel& viewModel,
                                                         Eegeo::Location::NavigationService& navigationService)
        : m_model(model)
        , m_viewModel(viewModel)
        , m_navigationService(navigationService)
        {
        }
        
        void CompassUpdateController::Update(float deltaSeconds)
        {
            m_viewModel.UpdateHeadingAngleRadians(m_model.GetHeadingRadians());
            
            m_model.TryUpdateToNavigationServiceGpsMode(m_navigationService.GetGpsMode());
        }
    }
}
