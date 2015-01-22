// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISecondaryMenuView.h"
#include "SecondaryMenuViewIncludes.h"
#include "CallbackCollection.h"
#include <string>

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            class SecondaryMenuViewInterop : private Eegeo::NonCopyable, public ISecondaryMenuView
            {
            private:
                SecondaryMenuView* m_pView;
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_callbacks;

            public:
                SecondaryMenuViewInterop(SecondaryMenuView* pView)
                    : m_pView(pView)
                {
                }

                void RemoveSeachKeyboard()
                {
                    [m_pView removeSeachKeyboard];
                }

                void DisableEditText()
                {
                    [m_pView disableEdit];
                }

                void EnableEditText()
                {
                    [m_pView enableEdit];
                }

                void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_callbacks.AddCallback(callback);
                }

                void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
                {
                    m_callbacks.RemoveCallback(callback);
                }

                void SearchPerformed(const std::string& searchQuery)
                {
                    m_callbacks.ExecuteCallbacks(searchQuery);
                }
            };
        }
    }
}
