// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonModule.h"
#include "FlattenButtonViewModel.h"
#include "FlattenButtonModel.h"
#include "FlattenButtonViewStateChangedObserver.h"
#include "FlattenButtonModelStateChangedObserver.h"
#include "IMapModeModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            FlattenButtonModule::FlattenButtonModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void FlattenButtonModule::Register()
            {
                m_builder->registerType<FlattenButtonModel>().as<IFlattenButtonModel>().singleInstance();
                m_builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<View::FlattenButtonViewModel>(context.resolve<Eegeo::Helpers::IIdentityProvider>(), false);
                                                   }).as<View::IFlattenButtonViewModel>().singleInstance();
                m_builder->registerType<FlattenButtonViewStateChangedObserver>().singleInstance();
                m_builder->registerType<FlattenButtonModelStateChangedObserver>().singleInstance();
            }
        }
    }
}
