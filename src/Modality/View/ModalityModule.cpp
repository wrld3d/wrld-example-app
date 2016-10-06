// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalityModule.h"
#include "ModalityModel.h"
#include "ModalityController.h"
#include "ModalityObserver.h"
#include "ModalityIgnoredReactionModel.h"
#include "ModalBackgroundController.h"
#include "IModalBackgroundView.h"

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
                builder->registerType<Modality::View::ModalBackgroundController>().singleInstance();
            }
            
            void ModalityModule::RegisterNativeLeaves()
            {
                RegisterLeaf<ModalityObserver>();
                RegisterLeaf<IModalityController>();
            }
            
            void ModalityModule::RegisterUiLeaves()
            {
                Eegeo_TTY("ModalityModule::RegisterUiLeaves begin");
                RegisterLeaf<Modality::View::ModalBackgroundController>();
                Eegeo_TTY("ModalityModule::RegisterUiLeaves end");
            }
        }
    }
}
