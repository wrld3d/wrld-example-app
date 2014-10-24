// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "PoiCreationButtonViewIncludes.h"
#include "Rendering.h"
#include "PoiCreation.h"
#include "IPoiCreationButtonViewModule.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationButtonViewModule: public IPoiCreationButtonViewModule, private Eegeo::NonCopyable
        {
        private:
            PoiCreationButtonViewController* m_pController;
            
        public:
            PoiCreationButtonViewModule(IPoiCreationModel& model,
                                        IPoiCreationButtonViewModel& viewModel,
                                        const Eegeo::Rendering::ScreenProperties& screenProperties);
            
            ~PoiCreationButtonViewModule();
            
            PoiCreationButtonViewController& GetPoiCreationButtonViewController() const;
            
            PoiCreationButtonView& GetPoiCreationButtonView() const;
        };
    }
}
