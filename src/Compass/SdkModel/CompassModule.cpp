// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassModule.h"
#include "CompassViewModel.h"
#include "CompassModel.h"
#include "CompassUpdateController.h"
#include "CompassModeObserver.h"
#include "CompassViewCycledObserver.h"
#include "IInteriorsNavigationService.h"
#include "ILocationService.h"
#include "IAppCameraController.h"
#include "InteriorsExplorerModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "IVisualMapService.h"
#include "IAlertBoxFactory.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            CompassModule::CompassModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void CompassModule::Register()
            {
                m_builder->registerType<CompassModel>().as<ICompassModel>().singleInstance();
                m_builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<View::CompassViewModel>(context.resolve<Eegeo::Helpers::IIdentityProvider>(), false);
                                                   }).as<View::ICompassViewModel>().singleInstance();
                m_builder->registerType<CompassUpdateController>().as<ICompassUpdateController>().singleInstance();
                m_builder->registerType<CompassModeObserver>().singleInstance();
                m_builder->registerType<CompassViewCycledObserver>().singleInstance();
            }
        }
    }
}
