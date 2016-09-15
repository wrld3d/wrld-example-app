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
#include "CompassController.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            void CompassModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<CompassModel>().as<ICompassModel>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<View::CompassViewModel>(context.resolve<Eegeo::Helpers::IIdentityProvider>(), false);
                                                   }).as<View::ICompassViewModel>().singleInstance();
                builder->registerType<CompassUpdateController>().as<ICompassUpdateController>().singleInstance();
                builder->registerType<CompassModeObserver>().singleInstance();
                builder->registerType<CompassViewCycledObserver>().singleInstance();
                builder->registerType<View::CompassController>().singleInstance();
            }
            
            void CompassModule::RegisterLeaves()
            {
                RegisterLeaf<View::CompassController>();
                RegisterLeaf<CompassModeObserver>();
                RegisterLeaf<CompassViewCycledObserver>();
            }
            
            void CompassModule::RegisterOpenablesAndReactors()
            {
                RegisterReactor(&Resolve<View::ICompassViewModel>()->GetScreenControlViewModel());
            }
        }
    }
}
