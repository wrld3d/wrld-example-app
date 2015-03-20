// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinDetailsView.h"
#include "CallbackCollection.h"
#include "ICallback.h"
#include "MyPinDetailsViewIncludes.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class MyPinDetailsViewInterop : public IMyPinDetailsView
            {
            public:

                MyPinDetailsViewInterop(MyPinDetailsView* pView)
                    : m_pView(pView)
                {
                }

                void OpenWithModel(const std::string& title,
                                   const std::string& description,
                                   const std::string& imagePath);
                void Close();

                void OnDismiss();
                void OnRemove();

                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void InsertRemovePinCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveRemovePinCallback(Eegeo::Helpers::ICallback0& callback);

            private:

                MyPinDetailsView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_dismissCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_removePinCallbacks;
            };
        }
    }
}
