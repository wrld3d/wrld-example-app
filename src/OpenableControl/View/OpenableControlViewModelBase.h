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
            typedef bool OpenState;
            class OpenableControlViewModelBase : public IOpenableControlViewModel
            {
            private:
                OpenState m_openState;

                Eegeo::Helpers::CallbackCollection1<IOpenableControlViewModel&> m_openStateChangedCallbacks;

            protected:
                OpenableControlViewModelBase();

            public:

                ~OpenableControlViewModelBase();

                void Open() override;

                void Close() override;

                void InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback1<IOpenableControlViewModel&>& callback) override;

                void RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback1<IOpenableControlViewModel&>& callback) override;

                bool IsOpen() const override;

                bool IsClosed() const override;
            };
        }
    }
}
