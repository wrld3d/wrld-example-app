// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModalBackgroundView.h"

#include "CallbackCollection.h"
#include "ICallback.h"
#include "ModalBackgroundViewIncludes.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            class ModalBackgroundViewInterop : public Modality::View::IModalBackgroundView
            {
            public:

                ModalBackgroundViewInterop(ModalBackgroundView* pView)
                    : m_pView(pView)
                , m_searchPerformedCallback(this, &ModalBackgroundViewInterop::SearchPerformedCallbackImpl)
                {
                }

                void SetFullyActive();
                void SetFullyInactive();
                void SetActiveStateToIntermediateValue(float modality);
                
                void InsertTappedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTappedCallback(Eegeo::Helpers::ICallback0& callback);
                void InsertTouchCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTouchCallback(Eegeo::Helpers::ICallback0& callback);

                void HandleViewTapped();
                void HandleTouchOnView();

                void SearchPerformedCallbackImpl(const std::string & str);
                Eegeo::Helpers::ICallback1<const std::string&>& GetSearchPerformedCallback();
                
            private:

                ModalBackgroundView* m_pView;
                
                Eegeo::Helpers::CallbackCollection0 m_tappedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_touchCallbacks;

                Eegeo::Helpers::TCallback1<ModalBackgroundViewInterop, const std::string&> m_searchPerformedCallback;
            };
        }
    }
}
