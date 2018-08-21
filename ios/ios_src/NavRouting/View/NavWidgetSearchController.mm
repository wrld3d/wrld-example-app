#import <Foundation/Foundation.h>

#include "NavWidgetSearchController.h"
#import <WrldSearchWidget/WrldSearchWidget.h>
#import "NavWidgetView.h"
#import "NavWidgetSearchView.h"
#include "WidgetSearchResultModel.h"

@interface NavWidgetSearchController()
@property BOOL isSearchingForStartPoint;
@property ResultSelectedEvent selectedResultEvent;
@end;

@implementation NavWidgetSearchController
{
    ExampleApp::NavRouting::View::NavWidgetView* m_pNavWidgetView;
    ExampleApp::NavRouting::View::NavWidgetSearchView* m_pSearchView;
}

- (instancetype) initWithSearchView: (ExampleApp::NavRouting::View::NavWidgetSearchView*) searchView navWidgetView : (ExampleApp::NavRouting::View::NavWidgetView*) pNavWidgetView
{
    if(self = [super init])
    {
        m_pNavWidgetView = pNavWidgetView;
        m_pSearchView = searchView;
        _isSearchingForStartPoint = NO;
        
        self.selectedResultEvent = ^(id<WRLDSearchResultModel> selectedResultModel) {
            WidgetSearchResultModel* selectedWidgetResult = (WidgetSearchResultModel*) selectedResultModel;
            if(selectedWidgetResult != nil)
            {
                [self navSuggestionSelected: (int)selectedWidgetResult.index];
            }
            [self hideSearchView];
        };
    
        
        m_pSearchView->AddSelectedResultCallback(self.selectedResultEvent);
        m_pSearchView->AddCloseButtonTarget(self, @selector(closeSearchHandler:));
    }
    return self;
}

- (void) closeSearchHandler: (id) selector
{
    [self hideSearchView];
}

- (void) dealloc
{
    m_pSearchView->RemoveCloseButtonTarget(self, @selector(closeSearchHandler:));
    m_pSearchView->RemoveSelectedResultCallback(self.selectedResultEvent);
    [super dealloc];
}

- (void) navSuggestionSelected: (int) index
{
    if(self.isSearchingForStartPoint)
    {
        m_pNavWidgetView->SetStartPointFromResultIndex(index);
    }
    else
    {
        m_pNavWidgetView->SetEndPointFromResultIndex(index);
    }
}

- (void) eventReceived: (WRLDNavEvent) key
{
    switch(key){
        case WRLDNavEventSelectStartLocationClicked:
            _isSearchingForStartPoint = YES;
            [self showSearchView];
            break;
        case WRLDNavEventSelectEndLocationClicked:
            _isSearchingForStartPoint = NO;
            [self showSearchView];
            break;
        default:
            break;
    }
}

- (void) showSearchView
{
    m_pNavWidgetView->Hide();
    m_pSearchView->Show();
    m_pNavWidgetView->SetSearchingForLocation(true, self.isSearchingForStartPoint);
}

- (void) hideSearchView
{
    m_pNavWidgetView->Show();
    m_pSearchView->Hide();
    m_pNavWidgetView->SetSearchingForLocation(false, self.isSearchingForStartPoint);
}

- (void) handleLocationSet: (BOOL)wasStartLocation
{
    if(self.isSearchingForStartPoint == wasStartLocation)
    {
        [self hideSearchView];
    }
}
@end
