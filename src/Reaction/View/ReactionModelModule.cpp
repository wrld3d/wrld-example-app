// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReactionModelModule.h"
#include "ReactionModel.h"
#include "ReactionControllerModel.h"
#include "ReactorIgnoredReactionModel.h"
#include "ModalityIgnoredReactionModel.h"
#include "ReactionControllerModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            void ReactionModelModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<Menu::View::ReactorIgnoredReactionModel>().as<Menu::View::IReactorIgnoredReactionModel>().singleInstance();
                builder->registerType<Menu::View::ModalityIgnoredReactionModel>().as<Menu::View::IModalityIgnoredReactionModel>().singleInstance();
                builder->registerType<ScreenControl::View::TReactors>().singleInstance();
                builder->registerType<OpenableControl::View::TOpenables>().singleInstance();
                builder->registerType<ReactionControllerModel>().as<IReactionControllerModel>().singleInstance();
                builder->registerType<ReactionModel>().as<IReactionModel>().singleInstance();
            }
        }
    }
}
