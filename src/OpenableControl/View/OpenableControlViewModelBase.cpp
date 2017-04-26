// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OpenableControlViewModelBase.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace OpenableControl
    {
        namespace View
        {
            OpenableControlViewModelBase::OpenableControlViewModelBase(Reaction::View::IReactionControllerModel& reactionControllerModel)
                : m_openState(0.f)
                , m_reactionControllerModel(reactionControllerModel)
            {

            }

            OpenableControlViewModelBase::~OpenableControlViewModelBase()
            {

            }

            bool OpenableControlViewModelBase::HasReactorControl() const
            {
                return m_reactionControllerModel.HasModalControl(GetIdentity());
            }

            bool OpenableControlViewModelBase::TryAcquireReactorControl()
            {
                if(m_reactionControllerModel.IsModalControlAcquired())
                {
                    return m_reactionControllerModel.HasModalControl(GetIdentity());
                }
                else
                {
                    m_reactionControllerModel.AcquireModalControl(GetIdentity());
                    return true;
                }
            }

            bool OpenableControlViewModelBase::TryAcquireOpenableControl()
            {
                if(m_reactionControllerModel.IsAnyOpenableOpen())
                {
                    return m_reactionControllerModel.IsOpenableOpen(GetIdentity());
                }
                else
                {
                    m_reactionControllerModel.AcquireOpenableOpen(GetIdentity());
                    return true;
                }
            }

            void OpenableControlViewModelBase::ReleaseOpenableControl()
            {
                if(m_reactionControllerModel.IsOpenableOpen(GetIdentity()))
                {
                    m_reactionControllerModel.ReleaseOpenableOpen(GetIdentity());
                }
            }

            void OpenableControlViewModelBase::ReleaseReactorControl()
            {
                return m_reactionControllerModel.ReleaseModalControl(GetIdentity());
            }

            bool OpenableControlViewModelBase::Open(bool acquireReactor)
            {
                if (!acquireReactor)
                {
                    m_openState = 1.f;
                    m_openStateChangedCallbacks.ExecuteCallbacks(*this, m_openState);
                    return true;
                }
                else if(TryAcquireReactorControl())
                {
                    m_openState = 1.f;
                    m_openStateChangedCallbacks.ExecuteCallbacks(*this, m_openState);

                    {
                        const bool acquiredOpenableControl = TryAcquireOpenableControl();
                        Eegeo_ASSERT(acquiredOpenableControl, "failed to acquire openable control");
                    }

                    return true;
                }
                return false;
            }

            bool OpenableControlViewModelBase::Close(bool releaseReactor)
            {
                if (!releaseReactor)
                {
                    m_openState = 0.f;
                    m_openStateChangedCallbacks.ExecuteCallbacks(*this, m_openState);
                    return true;
                }
                else if(TryAcquireReactorControl())
                {
                    m_openState = 0.f;
                    m_openStateChangedCallbacks.ExecuteCallbacks(*this, m_openState);
                    ReleaseReactorControl();
                    ReleaseOpenableControl();
                    return true;
                }
                return false;
            }

            void OpenableControlViewModelBase::UpdateOpenState(float openState)
            {
                Eegeo_ASSERT(openState >= 0.f && openState <= 1.f, "Invalid value %f for open state, valid range for UI open-state is 0.0 to 1.0 inclusive.\n", openState)

                {
                    const bool acquiredReactorControl = TryAcquireReactorControl();
                    Eegeo_ASSERT(acquiredReactorControl, "failed to acquire reactor control");
                }

                if(openState < 1.f)
                {
                    ReleaseOpenableControl();
                }

                m_openState = openState;
                m_openStateChangedCallbacks.ExecuteCallbacks(*this, m_openState);
            }

            void OpenableControlViewModelBase::InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback2<IOpenableControlViewModel&, float>& callback)
            {
                m_openStateChangedCallbacks.AddCallback(callback);
            }

            void OpenableControlViewModelBase::RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback2<IOpenableControlViewModel&, float>& callback)
            {
                m_openStateChangedCallbacks.RemoveCallback(callback);
            }

            bool OpenableControlViewModelBase::IsFullyOpen() const
            {
                return OpenState() == 1.f;
            }

            bool OpenableControlViewModelBase::IsFullyClosed() const
            {
                return OpenState() == 0.f;
            }

            float OpenableControlViewModelBase::OpenState() const
            {
                return m_openState;
            }
        }
    }
}
