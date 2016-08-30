// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalityModule.h"
#include "ModalityModel.h"
#include "ModalityController.h"
#include "ModalityObserver.h"
#include "ModalityIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            ModalityModule::ModalityModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void ModalityModule::Register()
            {
                m_builder->registerType<ModalityModel>().as<IModalityModel>().singleInstance();
                m_builder->registerType<ModalityController>().as<IModalityController>().singleInstance();
                m_builder->registerType<ModalityObserver>().singleInstance();
            }
        }
    }
}
