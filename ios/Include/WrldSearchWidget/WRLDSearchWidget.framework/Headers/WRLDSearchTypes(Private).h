#pragma once

@protocol WRLDSearchRequestFulfillerHandle;
@protocol WRLDSearchResultModel;

typedef NSMutableArray< id <WRLDSearchRequestFulfillerHandle> > WRLDSearchRequestFulfillerCollection;
typedef NSMutableDictionary< NSNumber *, WRLDSearchResultsCollection * > WRLDFulfillerResultsDictionary;
