// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "CustomTableView.h"
#import <QuartzCore/QuartzCore.h>
#import "CustomTableViewCell.h"
#import "MenuView.h"
#import "CellConstants.h"
#import "CircleCurve.h"
#import "ViewAnimationController.h"
#import "ViewPositionAnimator.h"
#import "ViewSizeAnimator.h"

@interface CustomTableView ()

@end

@implementation CustomTableView
{
    float m_animationDuration;
    bool m_isAnimating;
    UIScrollView* m_pContainer;
    MenuView* m_pMenuView;
    bool m_hasSubMenus;
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_pAnimationController;
}

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style
                    container:(UIScrollView*)container
                     menuView:(MenuView*)menuView
                  hasSubMenus:(bool)hasSubMenus
{
    id it = [super initWithFrame:frame style:style];
    m_pContainer = container;
    m_pMenuView = menuView;
    m_animationDuration = 0.2f;
    m_isAnimating = NO;
    m_hasSubMenus = hasSubMenus;
    
    self.pBackgroundView = [[UIView alloc]initWithFrame:CGRectMake(0.0f, 0.0f, frame.size.width, frame.size.height)];
    [self addSubview:self.pBackgroundView];
    
    m_pAnimationController = NULL;
    
    return it;
}

- (void)dealloc
{
    if(m_pAnimationController != NULL)
    {
        Eegeo_DELETE m_pAnimationController;
        m_pAnimationController = NULL;
    }
    
    [super dealloc];
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    
    if(m_hasSubMenus)
    {
        float zOffset = 0.f;
        const float zOffsetIncrement = 0.001f;
        
        NSArray *sortedIndexPaths = [[self indexPathsForVisibleRows] sortedArrayUsingSelector:@selector(compare:)];
        for (NSIndexPath *path in sortedIndexPaths)
        {
            UITableViewCell *cell = [self cellForRowAtIndexPath:path];
            [self sendSubviewToBack:cell];
            [cell.layer setZPosition: zOffset];
            
            zOffset -= zOffsetIncrement;
        }
        
        m_pContainer.contentSize = self.contentSize;
    }
    
    [self sendSubviewToBack:self.pBackgroundView];
}

- (BOOL)hasDynamicCellPresentation
{
    return m_hasSubMenus;
}

- (BOOL)isAnimating
{
    return m_isAnimating;
}

- (void)updateAnimation:(double)deltaSeconds
{
    Eegeo_ASSERT([self isAnimating], "updateAnimation called when table is not animating, please call isAnimating to check that animation is running before calling updateAnimation");
    
    m_pAnimationController->Update(deltaSeconds);
    
    [self->m_pContainer setContentSize:CGSizeMake(self.pBackgroundView.frame.size.width, self.pBackgroundView.frame.size.height)];
    
    if(!m_pAnimationController->IsActive())
    {
        Eegeo_DELETE m_pAnimationController;
        m_pAnimationController = NULL;
        
        [self setInteractionEnabled:YES];
    }
}

-(void)setInteractionEnabled:(BOOL)enabled
{
    m_isAnimating = !enabled;
    self.userInteractionEnabled = enabled;
    self.scrollEnabled = enabled;
    m_pContainer.userInteractionEnabled = YES;
    m_pContainer.scrollEnabled = YES;
}

-(void)insertRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation
{
    if([indexPaths count] == 0)
    {
        return;
    }
    
    if([self isHidden])
    {
        [self reloadData];
        [m_pMenuView refreshTableHeights];
        
        return;
    }
    
    [self setInteractionEnabled: NO];
    
    [self reloadData];
    
    const float currentTableHeight = self.frame.size.height;
    
    [m_pMenuView refreshTableHeights];
    
    m_pAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                  ^(UIView* view){
                                                                                                      [(CustomTableView*)view setInteractionEnabled:YES];
                                                                                                  },
                                                                                                  NULL);
    
    // animate inserted cells
    const float cellAnimationDuration = (m_animationDuration / [indexPaths count]);
    [self addCellHeightAnimatorsWithIndexPaths:indexPaths startHeight:0.0f endHeight:SUB_SECTION_CELL_HEIGHT animationDuration:cellAnimationDuration animationDelay:m_animationDuration - cellAnimationDuration];
    
    // animate subsequent cells
    const float heightOffset = SUB_SECTION_CELL_HEIGHT * [indexPaths count];
    [self addCellPositionAnimatorsAfterIndexPath:(NSIndexPath*)[indexPaths lastObject] deltaY:-heightOffset deltaStart:true];
    
    // animate background
    [self addBackgroundAnimatorWithStartHeight:currentTableHeight endHeight:[m_pMenuView getTableHeight]];
    
    m_pAnimationController->Play();
}

-(void)deleteRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation
{
    if([indexPaths count] == 0)
    {
        return;
    }
    
    if([self isHidden])
    {
        [self reloadData];
        [m_pMenuView refreshTableHeights];
        
        return;
    }
    
    [self setInteractionEnabled:NO];
    
    m_pAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                  ^(UIView* view){
                                                                                                      CustomTableView* tableView = (CustomTableView*)view;
                                                                                                      
                                                                                                      [tableView reloadData];
                                                                                                      [tableView->m_pMenuView refreshTableHeights];
                                                                                                      [tableView setInteractionEnabled:YES];
                                                                                                  },
                                                                                                  NULL);
    
    // animate removed cells
    [self addCellHeightAnimatorsWithIndexPaths:indexPaths startHeight:SUB_SECTION_CELL_HEIGHT endHeight:0.0f animationDuration:m_animationDuration / [indexPaths count] animationDelay:0.0];
    
    // animate subsequent cells
    const float heightOffset = SUB_SECTION_CELL_HEIGHT * [indexPaths count];
    [self addCellPositionAnimatorsAfterIndexPath:(NSIndexPath*)[indexPaths lastObject] deltaY:-heightOffset deltaStart:false];
    
    // animate background
    [self addBackgroundAnimatorWithStartHeight:self.frame.size.height endHeight:self.frame.size.height - heightOffset];
    
    m_pAnimationController->Play();
}

- (void)addCellHeightAnimatorsWithIndexPaths:(NSArray*)indexPaths
                                 startHeight:(float)startHeight
                                   endHeight:(float)endHeight
                           animationDuration:(double)animationDuration
                              animationDelay:(double)animationDelay
{
    for (NSIndexPath *indexPath in indexPaths)
    {
        UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];
        
        if(cell != nil)
        {
            const float cellWidth = cell.frame.size.width;
            
            CGRect frame = cell.frame;
            frame.size.height = startHeight;
            cell.frame = frame;
            
            m_pAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewSizeAnimator)(cell,
                                                                                                              animationDuration,
                                                                                                              animationDelay,
                                                                                                              Eegeo::v2(cellWidth, startHeight),
                                                                                                              Eegeo::v2(cellWidth, endHeight),
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
        }
    }
}

- (void)addCellPositionAnimatorsAfterIndexPath:(NSIndexPath*)indexPath
                                        deltaY:(float)deltaY
                                    deltaStart:(bool)deltaStart
{
    NSInteger numberOfSections = [self numberOfSections];
    
    for (NSInteger i = (indexPath).section + 1; i < numberOfSections; ++i)
    {
        NSInteger numberOfRowsInSection = [self numberOfRowsInSection: i];
        
        for (NSInteger j = 0; j < numberOfRowsInSection; ++j)
        {
            NSIndexPath *indexPath = [NSIndexPath indexPathForRow:j inSection:i];
            UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];
            
            if(cell != nil)
            {
                const float startY = deltaStart ? cell.frame.origin.y + deltaY : cell.frame.origin.y;
                const float endY = deltaStart ? cell.frame.origin.y : cell.frame.origin.y + deltaY;
                
                CGRect frame = cell.frame;
                frame.origin.y = startY;
                cell.frame = frame;
                
                m_pAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(cell,
                                                                                                                      m_animationDuration,
                                                                                                                      0.0,
                                                                                                                      Eegeo::v2(cell.frame.origin.x, startY),
                                                                                                                      Eegeo::v2(cell.frame.origin.x, endY),
                                                                                                                      Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
            }
        }
    }
}

- (void)addBackgroundAnimatorWithStartHeight:(float)startHeight
                                   endHeight:(float)endHeight
{
    CGRect frame = self.pBackgroundView.frame;
    frame.size.height = startHeight;
    self.pBackgroundView.frame = frame;
    
    m_pAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewSizeAnimator)(self.pBackgroundView,
                                                                                                      m_animationDuration,
                                                                                                      0.0,
                                                                                                      Eegeo::v2(self.pBackgroundView.frame.size.width, startHeight),
                                                                                                      Eegeo::v2(self.pBackgroundView.frame.size.width, endHeight),
                                                                                                      Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
}

@end
