// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "IIdentity.h"

namespace ExampleApp
{
    namespace OpenableControl
    {
        namespace View
        {
            class IOpenableControlViewModel : public virtual Eegeo::Helpers::IIdentity
            {
            public:
                virtual ~IOpenableControlViewModel() { }

                virtual bool HasReactorControl() const = 0;

                virtual bool TryAcquireReactorControl() = 0;

                virtual void ReleaseReactorControl() = 0;

                virtual bool Open(bool acquireReactor = true) = 0;

                virtual bool Close(bool releaseReactor = true) = 0;

                virtual void UpdateOpenState(float openState) = 0;

                virtual void InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback2<IOpenableControlViewModel&, float>& callback) = 0;

                virtual void RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback2<IOpenableControlViewModel&, float>& callback) = 0;

                virtual bool IsFullyOpen() const = 0;

                virtual bool IsFullyClosed() const = 0;

                virtual float OpenState() const = 0;
            };
        }
    }
}
