// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetViewModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetViewModel::NavWidgetViewModel(Eegeo::Helpers::TIdentity identity,
                                                   Reaction::View::IReactionControllerModel& reactionControllerModel)
                    : m_openable(identity, reactionControllerModel)
            {

            }

            NavWidgetViewModel::~NavWidgetViewModel()
            {

            }

            bool NavWidgetViewModel::TryAcquireReactorControl()
            {
                return m_openable.TryAcquireReactorControl();
            }

            bool NavWidgetViewModel::IsOpen() const
            {
                return m_openable.IsFullyOpen();
            }

            void NavWidgetViewModel::Open()
            {
                Eegeo_ASSERT(!IsOpen(), "Cannot open NavWidgetViewModel when already open.\n");
                if(m_openable.Open())
                {
                    m_openedCallbacks.ExecuteCallbacks();
                }
            }

            void NavWidgetViewModel::Close()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot close NavWidgetViewModel when view model when already closed.\n");

                {
                    const bool closed = m_openable.Close();
                    Eegeo_ASSERT(closed, "Failed to close");
                }

                m_closedCallbacks.ExecuteCallbacks();
            }

            void NavWidgetViewModel::SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                Eegeo_ASSERT(IsOpen(), "Cannot set start location when NavWidget is not open.\n");

                m_startLocationSetCallbacks.ExecuteCallbacks(locationModel);
            }

            void NavWidgetViewModel::ClearStartLocation()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot clear start location when NavWidget is not open.\n");

                m_startLocationClearedCallbacks.ExecuteCallbacks();
            }

            void NavWidgetViewModel::SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                Eegeo_ASSERT(IsOpen(), "Cannot set end location when NavWidget is not open.\n");

                m_endLocationSetCallbacks.ExecuteCallbacks(locationModel);
            }

            void NavWidgetViewModel::ClearEndLocation()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot clear end location when NavWidget is not open.\n");

                m_endLocationClearedCallbacks.ExecuteCallbacks();
            }

            void NavWidgetViewModel::SetRoute(const SdkModel::NavRoutingRouteModel& routeModel)
            {
                Eegeo_ASSERT(IsOpen(), "Cannot set route when NavWidget is not open.\n");

                m_routeSetCallbacks.ExecuteCallbacks(routeModel);
            }

            void NavWidgetViewModel::ClearRoute()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot clear route when NavWidget is not open.\n");

                m_routeClearedCallbacks.ExecuteCallbacks();
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

            void NavWidgetViewModel::InsertStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback)
            {
                m_startLocationSetCallbacks.AddCallback(startLocationSetCallback);
            }

            void NavWidgetViewModel::RemoveStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback)
            {
                m_startLocationSetCallbacks.RemoveCallback(startLocationSetCallback);
            }

            void NavWidgetViewModel::InsertStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback)
            {
                m_startLocationClearedCallbacks.AddCallback(startLocationClearedCallback);
            }

            void NavWidgetViewModel::RemoveStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback)
            {
                m_startLocationClearedCallbacks.RemoveCallback(startLocationClearedCallback);
            }

            void NavWidgetViewModel::InsertEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback)
            {
                m_endLocationSetCallbacks.AddCallback(endLocationSetCallback);
            }

            void NavWidgetViewModel::RemoveEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback)
            {
                m_endLocationSetCallbacks.RemoveCallback(endLocationSetCallback);
            }

            void NavWidgetViewModel::InsertEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback)
            {
                m_endLocationClearedCallbacks.AddCallback(endLocationClearedCallback);
            }

            void NavWidgetViewModel::RemoveEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback)
            {
                m_endLocationClearedCallbacks.RemoveCallback(endLocationClearedCallback);
            }

            void NavWidgetViewModel::InsertRouteSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingRouteModel&>& routeSetCallback)
            {
                m_routeSetCallbacks.AddCallback(routeSetCallback);
            }

            void NavWidgetViewModel::RemoveRouteSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingRouteModel&>& routeSetCallback)
            {
                m_routeSetCallbacks.RemoveCallback(routeSetCallback);
            }

            void NavWidgetViewModel::InsertRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback)
            {
                m_routeClearedCallbacks.AddCallback(routeClearedCallback);
            }

            void NavWidgetViewModel::RemoveRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback)
            {
                m_routeClearedCallbacks.RemoveCallback(routeClearedCallback);
            }
        }
    }
}
