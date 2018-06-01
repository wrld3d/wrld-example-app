#pragma once

#import <UIKit/UIKit.h>
#import "WRLDViewVisibilityController.h"

@class WRLDSearchWidgetTableViewContainer;
@class WRLDSearchWidgetResultsTableDataSource;
@class WRLDSearchWidgetStyle;

@interface WRLDSearchWidgetTableViewController : NSObject<UITableViewDelegate, WRLDViewVisibilityController>

- (instancetype) initWithTableView: (WRLDSearchWidgetTableViewContainer *) tableView
                        dataSource: (WRLDSearchWidgetResultsTableDataSource *) dataSource
                             style: (WRLDSearchWidgetStyle *) style;

- (void) refreshTable;
@end


