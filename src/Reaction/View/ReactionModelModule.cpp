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
            ReactionModelModule::ReactionModelModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void ReactionModelModule::Register()
            {
                m_builder->registerType<Menu::View::ReactorIgnoredReactionModel>().as<Menu::View::IReactorIgnoredReactionModel>().singleInstance();
                m_builder->registerType<Menu::View::ModalityIgnoredReactionModel>().as<Menu::View::IModalityIgnoredReactionModel>().singleInstance();
                m_builder->registerType<ScreenControl::View::TReactors>().singleInstance();
                m_builder->registerType<OpenableControl::View::TOpenables>().singleInstance();
                m_builder->registerType<ReactionControllerModel>().as<IReactionControllerModel>().singleInstance();
                m_builder->registerType<ReactionModel>().as<IReactionModel>().singleInstance();
            }
        }
    }
}
