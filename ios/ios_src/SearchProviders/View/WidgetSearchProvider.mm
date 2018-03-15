#import "WidgetSearchProvider.h"
#import "ISearchProvider.h"

@implementation WidgetSearchProvider

- (instancetype) initWithSearchProvider: (ExampleApp::SearchMenu::View::ISearchProvider *) searchProvider
{
    self = [super init];
    
    if (self)
    {
    }
    
    return self;
}

- (void)searchFor:(WRLDSearchRequest *)query
{
}

- (void)getSuggestions:(WRLDSearchRequest *)query
{
}

@synthesize moreResultsName;

@synthesize cellIdentifier;

@synthesize cellHeight;

@end
