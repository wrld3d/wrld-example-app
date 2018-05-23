// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OpenableControlViewModelBase.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace OpenableControl
    {
        namespace View
        {
            OpenableControlViewModelBase::OpenableControlViewModelBase()
                : m_openState(false)
            {

            }

            OpenableControlViewModelBase::~OpenableControlViewModelBase()
            {

            }

            void OpenableControlViewModelBase::Open()
            {
                m_openState = true;
                m_openStateChangedCallbacks.ExecuteCallbacks(*this);
            }

            void OpenableControlViewModelBase::Close()
            {
                m_openState = false;
                m_openStateChangedCallbacks.ExecuteCallbacks(*this);
            }

            void OpenableControlViewModelBase::InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback1<IOpenableControlViewModel&>& callback)
            {
                m_openStateChangedCallbacks.AddCallback(callback);
            }

            void OpenableControlViewModelBase::RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback1<IOpenableControlViewModel&>& callback)
            {
                m_openStateChangedCallbacks.RemoveCallback(callback);
            }

            bool OpenableControlViewModelBase::IsOpen() const
            {
                return m_openState;
            }

            bool OpenableControlViewModelBase::IsClosed() const
            {
                return !m_openState;
            }
        }
    }
}
