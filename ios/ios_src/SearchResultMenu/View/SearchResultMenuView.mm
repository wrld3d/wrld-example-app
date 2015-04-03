// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuView.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "MenuViewInterop.h"
#include "SearchResultMenuViewInterop.h"
#include "CellConstants.h"
#include "App.h"

@implementation SearchResultMenuView

- (ExampleApp::SearchResultMenu::View::SearchResultMenuViewInterop*) getSearchInterop
{
    return m_pSearchInterop;
}

- (void) initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
    m_pSearchInterop = Eegeo_NEW(ExampleApp::SearchResultMenu::View::SearchResultMenuViewInterop)(self);
    m_inAttractMode = false;
    
    m_pColour = ExampleApp::Helpers::ColorPalette::WhiteTone;

    m_stateChangeAnimationTimeSeconds = 0.2f;
    
    m_dragTabWidth = (50.f * m_pixelScale);
    m_dragTabHeight = (50.f * m_pixelScale);
    
    const float headerContainerHeight = m_dragTabHeight;
    const float headerContainerY = 50.f;
    const bool isPhone = App::IsDeviceSmall();

    m_mainContainerOffscreenOffsetX = (0.f * m_pixelScale);
    m_mainContainerOffscreenOffsetY = (0.f * m_pixelScale);
    m_mainContainerVisibleOnScreenWhenClosedX = (0.f * m_pixelScale);
    m_mainContainerVisibleOnScreenWhenClosedY = (0.f * m_pixelScale);
    m_mainContainerX = (0.f * m_pixelScale) - m_mainContainerOffscreenOffsetX;
    m_mainContainerY = (headerContainerY * m_pixelScale);
    m_mainContainerOnScreenWidth = ((isPhone ? 270.f : 300.f) * m_pixelScale);
    m_mainContainerOnScreenHeight = m_screenHeight - m_mainContainerY;
    m_mainContainerWidth = m_mainContainerOnScreenWidth;
    m_mainContainerHeight = m_mainContainerOnScreenHeight + m_mainContainerOffscreenOffsetY;
    
    self.pHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_mainContainerX,
                                                                      m_mainContainerY,
                                                                      m_mainContainerWidth,
                                                                      headerContainerHeight)] autorelease];
    
    const NSString* searchResultBarAsset = isPhone ? @"search_results_bar_small" : @"search_results_bar";
    self.pHeaderContainer.backgroundColor = [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(searchResultBarAsset)];
    
    self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_mainContainerX,
                                                                    m_mainContainerY + headerContainerHeight,
                                                                    m_mainContainerWidth,
                                                                    m_mainContainerHeight - headerContainerHeight)] autorelease];
    self.pMenuContainer.backgroundColor = [UIColor clearColor];
    
    m_dragTabX = m_mainContainerOnScreenWidth;
    m_dragTabY = m_mainContainerY + (0.f * m_pixelScale);
    self.pDragTab = [[[UIView alloc] initWithFrame:CGRectMake(m_dragTabX, m_dragTabY, m_dragTabWidth, m_dragTabHeight)] autorelease];
    self.pDragTab.backgroundColor = [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"menu_button")];
    self.pDragTab.transform = CGAffineTransformScale(CGAffineTransformIdentity, -1.f, 1.f);

    m_tableOffsetIntoContainerX = (0.f * m_pixelScale);
    m_tableOffsetIntoContainerY = (0.f * m_pixelScale);
    m_tableX = m_tableOffsetIntoContainerX;
    m_tableY = m_tableOffsetIntoContainerY + m_mainContainerVisibleOnScreenWhenClosedY;
    m_tableWidth = m_mainContainerOnScreenWidth - (2 * m_tableOffsetIntoContainerX);
    m_tableHeight = m_mainContainerHeight - (2 * m_tableOffsetIntoContainerY) - m_tableOffsetIntoContainerY - headerContainerHeight;
    
    const float tableScreenY = m_mainContainerY + m_mainContainerOffscreenOffsetY + m_tableY;
    const float tableScreenSpace = m_screenHeight - tableScreenY;
    m_tableHeight = std::min(tableScreenSpace, m_tableHeight);
    
    const float realTableHeight = (SECTION_HEADER_CELL_HEIGHT * numberOfCells);
    
    self.pTableviewContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(m_tableX, m_tableY, m_tableWidth, m_tableHeight)] autorelease];
    self.pTableviewContainer.bounces = NO;
    self.pTableviewContainer.contentSize = CGSizeMake(m_tableWidth, realTableHeight);
    
    self.pTableview = [[[CustomTableView alloc] initWithFrame:CGRectMake(0.f, 0.f, m_tableWidth, realTableHeight)
                                                        style:UITableViewStylePlain
                                                    container:self.pTableviewContainer
                                                  hasSubMenus:false
                        ] autorelease];
    self.pTableview.backgroundColor = [UIColor clearColor];
    self.pTableview.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.pTableview.bounces = NO;

    m_offscreenX = -(m_mainContainerWidth + m_dragTabWidth);
    m_closedX = -(m_mainContainerOnScreenWidth - m_mainContainerVisibleOnScreenWhenClosedX);
    m_openX = (0.f * m_pixelScale);

    //close
    const float closeButtonEdgeSize = 20.f;
    const float closeButtonInset = 10.f;
    const float closeButtonX = m_mainContainerWidth - closeButtonEdgeSize - closeButtonInset;
    self.pClearResults = [[[UIButton alloc] initWithFrame:CGRectMake(closeButtonX,
                                                                     15.f,
                                                                     closeButtonEdgeSize,
                                                                     closeButtonEdgeSize)] autorelease];
    
    [self.pClearResults setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"buttonsmall_close_off") forState:UIControlStateNormal];
    [self.pClearResults setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"buttonsmall_close_on") forState:UIControlStateHighlighted];

    //category
    float categoryIconEdgeSize = headerContainerHeight;
    self.pCategory = [[[UIView alloc] initWithFrame:CGRectMake(2.f,
                                                               0.f,
                                                               categoryIconEdgeSize,
                                                               categoryIconEdgeSize)] autorelease];
    
    if(isPhone)
    {
        // No category icon for phones, they are not wide enough.
        categoryIconEdgeSize = 0.f;
        [self.pCategory setHidden:YES];
    }

    //spinner
    const float spinnerSize = self.pDragTab.frame.size.height;
    const float spinnerX = self.pDragTab.frame.size.width - spinnerSize;
    CGRect spinnerFrame = self.pDragTab.frame;
    spinnerFrame.origin.x += spinnerX;
    self.pSpinner = [[[UIActivityIndicatorView alloc] initWithFrame:spinnerFrame] autorelease];
    [self.pSpinner startAnimating];
    self.pSpinner.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhite;
    
    //heading label
    const float headingTextOffset = isPhone ? 30.f : 10.f;
    const float headingX = categoryIconEdgeSize + headingTextOffset;
    self.pHeading = [[[UILabel alloc] initWithFrame:CGRectMake(headingX,
                                                               0.f,
                                                               closeButtonX - headingX,
                                                               headerContainerHeight)] autorelease];
    
    self.pHeading.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
    self.pHeading.textAlignment = NSTextAlignmentLeft;
    self.pHeading.text = @"";
    [self.pHeading setFont:[UIFont systemFontOfSize:18]];

    //results count
    CGRect resultsCountFrame = spinnerFrame;
    self.pResultsCount = [[[UILabel alloc] initWithFrame:resultsCountFrame] autorelease];
    self.pResultsCount.textColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
    self.pResultsCount.textAlignment = NSTextAlignmentCenter;
    [self.pResultsCount setFont:[UIFont systemFontOfSize:22]];

    [self addSubview: self.pMenuContainer];
    [self addSubview: self.pHeaderContainer];
    [self addSubview: self.pDragTab];
    [self addSubview: self.pSpinner];
    [self addSubview: self.pResultsCount];
    [self.pHeaderContainer addSubview: self.pClearResults];
    [self.pHeaderContainer addSubview: self.pCategory];
    [self.pHeaderContainer addSubview: self.pHeading];
    
    [self.pTableviewContainer addSubview:self.pTableview];
    [self.pMenuContainer addSubview:self.pTableviewContainer];

    [self.pClearResults addTarget:self action:@selector(onClearPressed:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)dealloc
{   
    [self.pTableviewContainer removeFromSuperview];
    [self.pTableviewContainer release];
    
    [self.pTableview removeFromSuperview];
    [self.pTableview release];

    [self.pSpinner removeFromSuperview];
    [self.pSpinner release];

    [self.pResultsCount removeFromSuperview];
    [self.pResultsCount release];

    [self.pDragTab removeFromSuperview];
    [self.pDragTab release];

    [self.pMenuContainer removeFromSuperview];
    [self.pMenuContainer release];
    
    [self.pHeading removeFromSuperview];
    [self.pHeading release];

    [self.pClearResults removeFromSuperview];
    [self.pClearResults release];

    [self.pCategory removeFromSuperview];
    [self.pCategory release];

    Eegeo_DELETE m_pSearchInterop;
    [self removeFromSuperview];
    [super dealloc];
}

- (void) updateViewForQuery:(const std::string&)searchText :(bool)queryPending :(size_t)numResults
{
    if(queryPending)
    {
        [self.pSpinner startAnimating];
        self.pResultsCount.hidden = true;
    }
    else
    {
        [self.pSpinner stopAnimating];
        self.pResultsCount.text = [NSString stringWithFormat:@"%lu", numResults];
        self.pResultsCount.hidden = false;
    }

    self.pHeading.text = [NSString stringWithUTF8String: searchText.c_str()];
    [self.pCategory.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];

    std::string categoryIcon = ExampleApp::Helpers::IconResources::GetSmallIconForCategory(searchText);
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pCategory, categoryIcon, ExampleApp::Helpers::ImageHelpers::Centre);
}

- (void) setAttractMode :(bool)attractModeEnabled
{
    m_inAttractMode = attractModeEnabled;
    [self updateAttractMode];
}

- (void) updateAttractMode
{
    [self.layer removeAllAnimations];
    
    if(m_inAttractMode)
    {
        self.frame = CGRectMake(m_closedX,
                                self.frame.origin.y,
                                self.frame.size.width,
                                self.frame.size.height);
        
        [UIView animateWithDuration:0.3f
                              delay:0.0f
                            options:(UIViewAnimationOptionAutoreverse | UIViewAnimationOptionRepeat)
                         animations:^{
                             self.frame = CGRectMake(m_closedX - 10.f,
                                                     self.frame.origin.y,
                                                     self.frame.size.width,
                                                     self.frame.size.height);
                         }
                         completion:nil];
    }
}

- (void) onClearPressed:(UIButton *) sender
{
    m_pSearchInterop->SearchClosed();
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    if([self isAnimating])
    {
        return;
    }
    
    self.hidden = false;
    [self setOffscreenPartsHiddenState:false];
    
    float newX = m_offscreenX + ((m_closedX - m_offscreenX) * onScreenState);
    if(fabs(self.frame.origin.x - newX) < 0.01f)
    {
        return;
    }
    
    CGRect f = self.frame;
    f.origin.x = newX;
    self.frame = f;
    
    [self updateAttractMode];
}

- (void) updateDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    CGRect f = self.frame;
    f.origin.x = m_controlStartPos.x + (absolutePosition.x - m_dragStartPos.x);
    
    if(f.origin.x > m_mainContainerOffscreenOffsetX)
    {
        f.origin.x = m_mainContainerOffscreenOffsetX;
    }
    
    if(f.origin.x < m_closedX)
    {
        f.origin.x = m_closedX;
    }
    
    float normalisedDragState = (static_cast<float>(self.frame.origin.x) + (-m_closedX)) / (std::abs(m_openX - m_closedX));
    normalisedDragState = Eegeo::Clamp(normalisedDragState, 0.f, 1.f);
    
    self.frame = f;
    
    m_pInterop->HandleDraggingViewInProgress(normalisedDragState);
    
    [self.layer removeAllAnimations];
}

- (void) completeDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    const bool startedClosed = m_controlStartPos.x == m_closedX;
    const float minimumXValueToClose = startedClosed ? 0.35f : 0.65f;
    bool close = absolutePosition.x < ((m_dragTabWidth+m_mainContainerWidth) * minimumXValueToClose);
    
    const float velocityMagitude = std::abs(static_cast<float>(absoluteVelocity.x));
    if(velocityMagitude > (200 * m_pixelScale))
    {
        close = absoluteVelocity.x < 0 ? true : false;
    }
    
    [self animateToX:(close ? m_closedX : m_openX)];
    m_pInterop->HandleDraggingViewCompleted();
    [self updateAttractMode];
}

- (void) refreshTableHeights: (size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
    const float tableScreenY = m_mainContainerY + m_mainContainerOffscreenOffsetY + m_tableY;
    const float tableScreenSpace = m_screenHeight - tableScreenY;
    m_tableHeight = fmin(tableScreenSpace, m_tableHeight);
    
    const float realTableHeight = (SECTION_HEADER_CELL_HEIGHT * numberOfCells);
    self.pTableviewContainer.frame = CGRectMake(m_tableX, m_tableY, m_tableWidth, m_tableHeight);
    self.pTableviewContainer.bounces = NO;
    self.pTableviewContainer.contentSize = CGSizeMake(m_tableWidth, realTableHeight);
    self.pTableview.frame = CGRectMake(0.f, 0.f, m_tableWidth, realTableHeight);
}

@end
