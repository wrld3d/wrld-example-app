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

                virtual void Open() = 0;

                virtual void Close() = 0;

                virtual void InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback1<IOpenableControlViewModel&>& callback) = 0;

                virtual void RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback1<IOpenableControlViewModel&>& callback) = 0;

                virtual bool IsOpen() const = 0;

                virtual bool IsClosed() const = 0;
            };
        }
    }
}
