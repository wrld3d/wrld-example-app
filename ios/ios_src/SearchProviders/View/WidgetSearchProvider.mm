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
        cellIdentifier = nil;
        cellHeight = 64;
    }
    
    return self;
}

- (void)searchFor:(WRLDSearchRequest *)query
{
    m_pSearchProvider->PeformSearch(query);
}

- (void)getSuggestions:(WRLDSearchRequest *)query
{
}

@synthesize moreResultsName;

@synthesize cellIdentifier;

@synthesize cellHeight;

@end
