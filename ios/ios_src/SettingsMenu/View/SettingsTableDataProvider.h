// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "CustomTableDataProvider.h"
#include "ViewWrap.h"

@class SettingsTableDataProvider;

class SettingsTableDataProviderWrapper : public ViewWrap<SettingsTableDataProvider>
{
    using ViewWrap::ViewWrap;
};

@interface SettingsTableDataProvider : CustomTableDataProvider
{
    
}


@end;