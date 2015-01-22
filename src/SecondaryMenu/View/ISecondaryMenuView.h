// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

#include <string>

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            class ISecondaryMenuView
            {
            public:
                virtual ~ISecondaryMenuView() { };

                virtual void RemoveSeachKeyboard() = 0;
                virtual void DisableEditText() = 0;
                virtual void EnableEditText() = 0;

                virtual void InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
                virtual void RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback) = 0;
            };
        }
    }
}
