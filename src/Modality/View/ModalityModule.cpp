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
            void ModalityModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<ModalityModel>().as<IModalityModel>().singleInstance();
                builder->registerType<ModalityController>().as<IModalityController>().singleInstance();
                builder->registerType<ModalityObserver>().singleInstance();
            }
            
            void ModalityModule::RegisterLeaves()
            {
                RegisterLeaf<ModalityObserver>();
                RegisterLeaf<IModalityController>();
            }
        }
    }
}
