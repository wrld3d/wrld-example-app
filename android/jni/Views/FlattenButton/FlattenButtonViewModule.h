// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IFlattenButtonViewModule.h"
#include "AndroidNativeState.h"
#include "Types.h"
#include "FLattenButton.h"
#include "FlattenButtonViewIncludes.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        class FlattenButtonViewModule: public IFlattenButtonViewModule, private Eegeo::NonCopyable
        {
        private:
        	FlattenButtonViewController* m_pController;

        public:
        	FlattenButtonViewModule(
            	AndroidNativeState& nativeState,
				FlattenButton::IFlattenButtonModel& model,
        		FlattenButton::IFlattenButtonViewModel& viewModel
            );

            ~FlattenButtonViewModule();
        };
    }
}
