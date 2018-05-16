#pragma once

@protocol WRLDSearchResultModel;

/*!
 A collection of WRLDSearchResultModels.
 */
typedef NSArray< id<WRLDSearchResultModel> > WRLDSearchResultsCollection;
typedef NSMutableArray< id<WRLDSearchResultModel> > WRLDMutableSearchResultsCollection;
