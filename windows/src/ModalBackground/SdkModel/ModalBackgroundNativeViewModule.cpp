// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundNativeViewModule.h"
#include "RenderableFilters.h"
#include "RenderingModule.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ModalBackgroundNativeView.h"
#include "ModalBackgroundNativeModalityObserver.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace SdkModel
        {
            void ModalBackgroundNativeViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<ModalBackgroundNativeView>().singleInstance();
                builder->registerType<ModalBackgroundNativeModalityObserver>().singleInstance();
            }

            void ModalBackgroundNativeViewModule::RegisterNativeLeaves()
            {
                ASSERT_NATIVE_THREAD
                RegisterLeaf<ModalBackgroundNativeView>();
                RegisterLeaf<ModalBackgroundNativeModalityObserver>();
            }

            void ModalBackgroundNativeViewModule::RegisterRenderableFilters()
            {
                RegisterRenderableFilter<ModalBackgroundNativeView>();
            }
        }
    }
}
