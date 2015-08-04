// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "FlattenButton.h"
#include "FlattenButtonModule.h"
#include "IFlattenButtonModule.h"
#include "IIdentity.h"
#include "FlattenButtonViewModel.h"
#include "FlattenButtonViewStateChangedObserver.h"
#include "FlattenButtonModelStateChangedObserver.h"
#include "BidirectionalBus.h"
#include "MapMode.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            class FlattenButtonModule : public IFlattenButtonModule, private Eegeo::NonCopyable
            {
            private:
                View::FlattenButtonViewModel* m_pViewModel;
                IFlattenButtonModel* m_pModel;
                FlattenButtonViewStateChangedObserver* m_pFlattenButtonViewStateChangedObserver;
                FlattenButtonModelStateChangedObserver* m_pFlattenButtonModelStateChangedObserver;

            public:
                FlattenButtonModule(MapMode::SdkModel::IMapModeModel & mapModeModel,
                                    Eegeo::Helpers::IIdentityProvider& identityProvider,
                                    ExampleAppMessaging::TMessageBus& messageBus);

                ~FlattenButtonModule();

                IFlattenButtonModel& GetFlattenButtonModel() const;

                View::IFlattenButtonViewModel& GetFlattenButtonViewModel() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
            };
        }
    }
}
