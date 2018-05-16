#pragma once

#import <Foundation/Foundation.h>

/*!
 A model representing a search result.  All results from WRLDSearchProviders and WRLDSuggestionProviders should fulfill this contract.
 */
@protocol WRLDSearchResultModel

/*!
 NSString summary that represents the content of the result.  Displayed by the default WRLDSearchWidgetTableViewCells.
 */
@property (nonatomic, copy) NSString* title;

/*!
 NSString containing additional information related to the result.  Displayed by the default WRLDSearchWidgetTableViewCells.
 */
@property (nonatomic, copy) NSString* subTitle;

/*!
 NSString that can be resolved to an icon for this results.  The default WRLDSearchWidgetTableViewCells attempts to resolve this as a web URL.
 */
@property (nonatomic, copy) NSString* iconKey;
@end


