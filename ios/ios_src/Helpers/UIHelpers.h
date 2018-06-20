// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIHelpers
        {
            bool UsePhoneLayout();
            
            UIAlertController* CreateSimpleAlert(NSString* title, NSString* message, NSString* okButtonText);
        }
    }
}
