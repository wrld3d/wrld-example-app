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
#include "UIView+TouchExclusivity.h"

@interface CustomTableView ()

@property (nonatomic, retain) UIView* pBackgroundView;

@end

@implementation CustomTableView
{
    float m_maxAnimationDuration;
    float m_minAnimationDuration;
    float m_cellAnimationDuration;
    bool m_isAnimating;
    MenuView* m_pMenuView;
    bool m_hasSubMenus;
    float m_cellWidth;
    float m_cellInset;
    
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_pAnimationController;
}

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style
                     menuView:(MenuView*)menuView
                  hasSubMenus:(bool)hasSubMenus
                    cellWidth:(float)cellWidth
                    cellInset:(float)cellInset
{
    id it = [super initWithFrame:frame style:style];
    m_pMenuView = menuView;
    m_maxAnimationDuration = 0.5f;
    m_minAnimationDuration = 0.2f;
    m_cellAnimationDuration = 0.1f;
    m_isAnimating = NO;
    m_hasSubMenus = hasSubMenus;
    m_cellWidth = cellWidth;
    m_cellInset = cellInset;
    
    self.pBackgroundView = [[UIView alloc]initWithFrame:CGRectMake(0.0f, 0.0f, frame.size.width, frame.size.height)];
    self.pBackgroundView.backgroundColor = [UIColor colorWithWhite:0.0 alpha:0.0];
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
    
    [m_pMenuView onTableAnimationUpdated];
    
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
    
    [m_pMenuView setTableCanInteract:enabled];
    
    self.scrollEnabled = enabled;
}

- (float)getCellWidth
{
    return m_cellWidth;
}

- (float)getCellInset
{
    return m_cellInset;
}

- (float)refreshHeight:(float)realHeight
{
    if(!m_isAnimating)
    {
        CGRect frame = self.frame;
        frame.size.height = realHeight;
        self.frame = frame;
        
        frame = self.pBackgroundView.frame;
        frame.size.height = realHeight;
        self.pBackgroundView.frame = frame;
    }
    
    [self setTouchExclusivity:self];
    
    return self.pBackgroundView.frame.size.height;
}

- (float)getAnimationDurationForCellCount:(int)cellCount
{
    return Eegeo::Math::Clamp(cellCount * m_cellAnimationDuration, m_minAnimationDuration, m_maxAnimationDuration);
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
    
    [self reloadData];
    
    const float currentTableHeight = self.frame.size.height;
    
    [m_pMenuView refreshTableHeights];
    
    [self setInteractionEnabled: NO];
    
    const float cellHeight = [self.delegate tableView:self heightForRowAtIndexPath:(NSIndexPath*)[indexPaths firstObject]];
    
    const float animationDuration = [self getAnimationDurationForCellCount:static_cast<int>([indexPaths count])];
    
    m_pAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                  ^(UIView* view){
                                                                                                      [(CustomTableView*)view setInteractionEnabled:YES];
                                                                                                  },
                                                                                                  NULL);
    
    // animate inserted cells
    [self addCellHeightAnimatorsWithIndexPaths:indexPaths startHeight:0.0f endHeight:cellHeight animationDuration:m_cellAnimationDuration animationDelay:animationDuration - m_cellAnimationDuration];
    
    // animate subsequent cells
    const float heightOffset = cellHeight * [indexPaths count];
    [self addCellPositionAnimatorsAfterIndexPath:(NSIndexPath*)[indexPaths lastObject] deltaY:-heightOffset deltaStart:true animationDuration:animationDuration];
    
    // animate background
    [self addBackgroundAnimatorWithStartHeight:currentTableHeight endHeight:[m_pMenuView getHeightForTable:self] animationDuration:animationDuration];
    
    m_pAnimationController->Play();
    
    [m_pMenuView onTableAnimationUpdated];
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
    
    const float currentTableHeight = self.frame.size.height;
    
    const float cellHeight = [self.delegate tableView:self heightForRowAtIndexPath:(NSIndexPath*)[indexPaths firstObject]];
    
    const float animationDuration = [self getAnimationDurationForCellCount:static_cast<int>([indexPaths count])];
    
    m_pAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                  ^(UIView* view){
                                                                                                      CustomTableView* tableView = (CustomTableView*)view;
                                                                                                      
                                                                                                      [tableView reloadData];
                                                                                                      [tableView->m_pMenuView refreshTableHeights];
                                                                                                      [tableView setInteractionEnabled:YES];
                                                                                                  },
                                                                                                  NULL);
    
    // animate removed cells
    [self addCellHeightAnimatorsWithIndexPaths:indexPaths startHeight:cellHeight endHeight:0.0f animationDuration:m_cellAnimationDuration animationDelay:0.0];
    
    // animate subsequent cells
    const float heightOffset = cellHeight * [indexPaths count];
    [self addCellPositionAnimatorsAfterIndexPath:(NSIndexPath*)[indexPaths lastObject] deltaY:-heightOffset deltaStart:false animationDuration:animationDuration];
    
    // animate background
    [self addBackgroundAnimatorWithStartHeight:currentTableHeight endHeight:currentTableHeight - heightOffset animationDuration:animationDuration];
    
    m_pAnimationController->Play();
    
    [m_pMenuView onTableAnimationUpdated];
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
                             animationDuration:(float)animationDuration
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
                                                                                                                      animationDuration,
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
                           animationDuration:(float)animationDuration
{
    CGRect frame = self.pBackgroundView.frame;
    frame.size.height = startHeight;
    self.pBackgroundView.frame = frame;
    
    m_pAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewSizeAnimator)(self.pBackgroundView,
                                                                                                      animationDuration,
                                                                                                      0.0,
                                                                                                      Eegeo::v2(self.pBackgroundView.frame.size.width, startHeight),
                                                                                                      Eegeo::v2(self.pBackgroundView.frame.size.width, endHeight),
                                                                                                      Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
}

@end
