// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchMenuView::SearchMenuView(WindowsNativeState& nativeState,
                                           const std::string& viewClassName)
                : Menu::View::MenuView(nativeState, viewClassName)
            {
                mUpdateHeader.SetupMethod(m_uiViewClass, m_uiView, "UpdateHeader");
                mSetAttractMode.SetupMethod(m_uiViewClass, m_uiView, "SetAttractMode");
            }

            void SearchMenuView::SetHeader(const std::string& header, bool queryPending, size_t numResult)
            {
                System::String^ queryString = gcnew System::String(header.c_str());
                mUpdateHeader(queryString, queryPending, (int)numResult);
            }

            void SearchMenuView::HandleSearchClosed()
            {
                m_closedCallbacks.ExecuteCallbacks();
            }

            void SearchMenuView::SetAttractMode(bool attractModeEnabled)
            {
                SetAttractMode(attractModeEnabled);
            }

            void SearchMenuView::InsertSearchClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.AddCallback(callback);
            }

            void SearchMenuView::RemoveSearchClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
