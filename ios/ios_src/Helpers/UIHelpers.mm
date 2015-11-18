// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UIHelpers.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIHelpers
        {
            bool UsePhoneLayout()
            {
                return UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone;
            }
        }
    }
}