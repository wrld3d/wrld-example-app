// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundViewModule.h"
#include "IModalityModel.h"
#include "ModalBackgroundView.h"
#include "ModalBackgroundController.h"
#include "IModalBackgroundView.h"
#include "ModalBackgroundViewInterop.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            void ModalBackgroundViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto view = [[ModalBackgroundView alloc] initWithParams
                                                                  :screenProperties->GetScreenWidth()
                                                                  :screenProperties->GetScreenHeight()];
                                                     return std::make_shared<ModalBackgroundViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<ModalBackgroundViewWrapper>();
                                                     auto interop = [view->Get() getInterop];
                                                     return Hypodermic::makeExternallyOwned(*interop);
                                                 }).as<Modality::View::IModalBackgroundView>().singleInstance();
                builder->registerType<Modality::View::ModalBackgroundController>().singleInstance();
            }
            
            void ModalBackgroundViewModule::RegisterLeaves()
            {
                RegisterLeaf<Modality::View::ModalBackgroundController>();
            }
        }
    }
}
