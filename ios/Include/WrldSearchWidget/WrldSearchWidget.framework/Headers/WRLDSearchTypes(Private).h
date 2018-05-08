#pragma once

@protocol WRLDSearchRequestFulfillerHandle;
@protocol WRLDSearchResultModel;

typedef NSMutableArray< id <WRLDSearchRequestFulfillerHandle> > WRLDSearchRequestFulfillerCollection;
typedef NSMutableArray< id<WRLDSearchResultModel> > WRLDMutableSearchResultsCollection;
typedef NSMutableDictionary< NSNumber *, WRLDSearchResultsCollection * > WRLDFulfillerResultsDictionary;
