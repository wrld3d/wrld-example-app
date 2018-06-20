// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UIHelpers.h"
#include <string>

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
            
            UIAlertController* CreateSimpleAlert(NSString* title, NSString* message, NSString* okButtonText)
            {
                UIAlertController * alert = [UIAlertController
                                             alertControllerWithTitle:title
                                             message:message
                                             preferredStyle:UIAlertControllerStyleAlert];
                
                UIAlertAction* okButton = [UIAlertAction
                                           actionWithTitle:okButtonText
                                           style:UIAlertActionStyleDefault
                                           handler:^(UIAlertAction * action) {
                                           }];
                
                [alert addAction:okButton];
                return alert;
            }
        }
    }
}
