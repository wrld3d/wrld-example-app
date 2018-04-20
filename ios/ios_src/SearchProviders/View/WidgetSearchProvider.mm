#import "WidgetSearchProvider.h"
#import "SearchProvider.h"

@implementation WidgetSearchProvider
{
    ExampleApp::SearchProviders::SearchProvider* m_pSearchProvider;
}

- (instancetype) initWithSearchProvider: (ExampleApp::SearchProviders::SearchProvider*) searchProvider
{
    self = [super init];
    
    if (self)
    {
        m_pSearchProvider = searchProvider;
        
        moreResultsName = @"Bloomberg";
        cellIdentifier = @"WidgetSearchResultTableViewCell";
        cellHeight = 64;
    }
    
    return self;
}

- (void)searchFor:(WRLDSearchRequest *)query
{
    m_pSearchProvider->PerformSearch(query);
}

- (void)getSuggestions:(WRLDSearchRequest *)query
{
    m_pSearchProvider->PerformAutocompleteSuggestions(query);
}

@synthesize moreResultsName;

@synthesize cellIdentifier;

@synthesize cellHeight;

@end
