// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetViewModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetViewModel::NavWidgetViewModel(Eegeo::Helpers::TIdentity identity)
                    : m_openable(identity)
            {

            }

            NavWidgetViewModel::~NavWidgetViewModel()
            {

            }


            bool NavWidgetViewModel::IsOpen() const
            {
                return m_openable.IsOpen();
            }

            void NavWidgetViewModel::Open()
            {
                Eegeo_ASSERT(!IsOpen(), "Cannot open NavWidgetViewModel when already open.\n");
                m_openable.Open();
                m_openedCallbacks.ExecuteCallbacks();
            }

            void NavWidgetViewModel::Close()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot close NavWidgetViewModel when view model when already closed.\n");

                m_openable.Close();
                m_closedCallbacks.ExecuteCallbacks();
            }


            void NavWidgetViewModel::SetNavMode(SdkModel::NavRoutingMode mode)
            {
                const float navWidgetBottomHeight = 100.0f;
                if(mode == SdkModel::NavRoutingMode::Ready || mode == SdkModel::NavRoutingMode::Active)
                {
                    m_compassOffsetProvider.SetOffset(navWidgetBottomHeight);
                }
                else
                {
                    m_compassOffsetProvider.SetOffset(0.0f);
                }
            }

            OpenableControl::View::IOpenableControlViewModel& NavWidgetViewModel::GetOpenableControl()
            {
                return m_openable;
            }

            void NavWidgetViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void NavWidgetViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void NavWidgetViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void NavWidgetViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }

            Reaction::View::IReactionScreenOffsetProvider& NavWidgetViewModel::GetCompassOffsetProvider()
            {
                return m_compassOffsetProvider;
            }
        }
    }
}
