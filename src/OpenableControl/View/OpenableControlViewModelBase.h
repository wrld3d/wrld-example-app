// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Reaction.h"
#include "CallbackCollection.h"
#include "ICallback.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace OpenableControl
    {
        namespace View
        {
            class OpenableControlViewModelBase : public IOpenableControlViewModel
            {
            private:
                float m_openState;
                std::shared_ptr<Reaction::View::IReactionControllerModel> m_reactionControllerModel;

                Eegeo::Helpers::CallbackCollection2<IOpenableControlViewModel&, float> m_openStateChangedCallbacks;

                bool TryAcquireOpenableControl();

                void ReleaseOpenableControl();

            protected:
                OpenableControlViewModelBase(const std::shared_ptr<Reaction::View::IReactionControllerModel>& reactionControllerModel);

            public:

                ~OpenableControlViewModelBase();

                bool HasReactorControl() const;

                bool TryAcquireReactorControl();

                void ReleaseReactorControl();

                bool Open(bool acquireReactor = true);

                bool Close(bool releaseReactor = true);

                void UpdateOpenState(float openState);

                void InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback2<IOpenableControlViewModel&, float>& callback);

                void RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback2<IOpenableControlViewModel&, float>& callback);

                bool IsFullyOpen() const;

                bool IsFullyClosed() const;

                float OpenState() const;
            };
        }
    }
}
