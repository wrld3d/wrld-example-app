// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewInterop.h"
#include "MyPinDetailsView.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            void MyPinDetailsViewInterop::OpenWithModel(const std::string& title,
                                                        const std::string& description,
                                                        const std::string& imagePath)
            {
                [m_pView setContent :title :description :imagePath];
                [m_pView setFullyActive];
            }

            void MyPinDetailsViewInterop::Close()
            {
                [m_pView setFullyInactive];
            }

            void MyPinDetailsViewInterop::InsertDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_dismissCallbacks.AddCallback(callback);
            }

            void MyPinDetailsViewInterop::RemoveDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_dismissCallbacks.RemoveCallback(callback);
            }

            void MyPinDetailsViewInterop::InsertRemovePinCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_removePinCallbacks.AddCallback(callback);
            }

            void MyPinDetailsViewInterop::RemoveRemovePinCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_removePinCallbacks.RemoveCallback(callback);
            }

            void MyPinDetailsViewInterop::OnRemove()
            {
                m_removePinCallbacks.ExecuteCallbacks();
            }

            void MyPinDetailsViewInterop::OnDismiss()
            {
                m_dismissCallbacks.ExecuteCallbacks();
            }
        }
    }
}