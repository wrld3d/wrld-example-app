// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsTableDataProvider.h"

#include "CustomTableViewCell.h"
#include "UIColors.h"

@implementation SettingsTableDataProvider

- (void) setCellInfo:(CustomTableViewCell*)cell :(bool)isHeader :(bool)hasSeparator
{
    [cell setInfo :false
                  :ExampleApp::Helpers::ColorPalette::UiBorderColor
                  :ExampleApp::Helpers::ColorPalette::TableSubCellColor
                  :ExampleApp::Helpers::ColorPalette::TableSubCellPressColor
                  :ExampleApp::Helpers::ColorPalette::TableSubCellTextColor
                  :ExampleApp::Helpers::ColorPalette::TableSubCellTextColor
                  :nil];
}

@end;
