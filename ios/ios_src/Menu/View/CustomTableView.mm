// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "CustomTableView.h"
#import <QuartzCore/QuartzCore.h>
#import "CustomTableViewCell.h"
#import "MenuView.h"

@interface CustomTableView ()

@end

@implementation CustomTableView
{
    float m_animationSpeed;
    bool m_inAnimationCeremony;
    UIScrollView* m_pContainer;
    MenuView* m_pMenuView;
    bool m_hasSubMenus;
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
    m_animationSpeed = 0.3f;
    m_inAnimationCeremony = NO;
    m_hasSubMenus = hasSubMenus;
    
    return it;
}

-(BOOL)hasDynamicCellPresentation
{
    return m_hasSubMenus;
}

-(BOOL)inAnimationCeremony
{
    return m_inAnimationCeremony;
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
}

-(void)setInteractionEnabled:(BOOL)enabled
{
    m_inAnimationCeremony = !enabled;
    self.userInteractionEnabled = enabled;
    self.scrollEnabled = enabled;
    m_pContainer.userInteractionEnabled = YES;
    m_pContainer.scrollEnabled = YES;
}

-(void)insertRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation
{
    [self setInteractionEnabled: NO];

    [self reloadData];
    
    [m_pMenuView refreshTableHeights];
    
    int count = 1;
    CGFloat height = 0.0f;
    float offset = 0.0f;
    
    const float relativeDuration = 1.0f / indexPaths.count;
    
    for (NSIndexPath *indexPath in indexPaths)
    {
        UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];
        height = cell.bounds.size.height;
        offset += height;
        
        cell.transform = CGAffineTransformMakeTranslation(0.0f, -offset);
        
        CGRect contentFrame = [(CustomTableViewCell*)cell getContentViewRect];
        contentFrame.size.height = 0.0f;
        cell.contentView.frame = contentFrame;
        
        [UIView animateKeyframesWithDuration:m_animationSpeed
                                       delay:0.0f
                                     options:UIViewAnimationCurveEaseInOut
                                  animations:^{
                                      [UIView addKeyframeWithRelativeStartTime:0.0 relativeDuration:relativeDuration * count animations:^{
                                          cell.transform = CGAffineTransformIdentity;
                                      }];
                                      [UIView addKeyframeWithRelativeStartTime:1.0 - relativeDuration relativeDuration:relativeDuration animations:^{
                                          cell.contentView.frame = [(CustomTableViewCell*)cell getContentViewRect];
                                      }];
                                  }
                                  completion:nil];
        
        ++count;
    }
    
    [self animateSubsequentSections:[indexPaths lastObject] withOffset:offset];
    
    [UIView animateWithDuration:m_animationSpeed
                          delay:0.0f
                        options:UIViewAnimationCurveEaseInOut
                     animations:^{
                             [self relaxCells:[indexPaths lastObject] :CGAffineTransformIdentity];
                     }
                     completion:^(BOOL finished){
                         [self setInteractionEnabled:YES];
                     }];
}

-(void)deleteRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation
{
    [self setInteractionEnabled: NO];
    
    int count = 1;
    CGFloat height = 0.0f;
    float offset = 0.f;
    
    const float relativeDuration = 1.0f / indexPaths.count;
    
    for (NSIndexPath *indexPath in indexPaths)
    {
        UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];
        
        height = cell.bounds.size.height;
        offset -= height;
        
        [cell.layer removeAllAnimations];
        [cell.contentView.layer removeAllAnimations];
        
        [UIView animateKeyframesWithDuration:m_animationSpeed
                                       delay:0.0f
                                     options:UIViewAnimationCurveEaseInOut
                                  animations:^{
                                      [UIView addKeyframeWithRelativeStartTime:0.0 relativeDuration:relativeDuration animations:^{
                                          CGRect contentFrame = [(CustomTableViewCell*)cell getContentViewRect];
                                          contentFrame.size.height = 0.0f;
                                          cell.contentView.frame = contentFrame;
                                      }];
                                      [UIView addKeyframeWithRelativeStartTime:1.0 - (relativeDuration * count) relativeDuration:relativeDuration * count animations:^{
                                          cell.transform = CGAffineTransformMakeTranslation(0.0f, offset);
                                      }];
                                  }
                                  completion:nil];
        
        ++count;
    }
    
    const size_t cellsDeleted = indexPaths.count;
    m_pContainer.contentSize = CGSizeMake(self.contentSize.width, self.contentSize.height - (cellsDeleted*height));
    [self scrollRectToVisible: CGRectMake(0, 0, self.contentSize.width, 0) animated:YES];
    
    [UIView animateWithDuration:m_animationSpeed
                          delay:0.0f
                        options:UIViewAnimationCurveEaseInOut
                     animations:^{
                         [self relaxCells:[indexPaths lastObject] :CGAffineTransformMakeTranslation(0.0f, offset)];
                     }
                     completion:^(BOOL finished){
                         for (int section = 0; section < [self numberOfSections]; section++)
                         {
                             for (int row = 0; row < [self numberOfRowsInSection:section]; row++)
                             {
                                 NSIndexPath* cellPath = [NSIndexPath indexPathForRow:row inSection:section];
                                 UITableViewCell* cell = [self cellForRowAtIndexPath:cellPath];
                                 cell.transform = CGAffineTransformIdentity;
                                 cell.contentView.transform = CGAffineTransformIdentity;
                             }
                         }
                         
                         [self reloadData];
                         
                         [m_pMenuView refreshTableHeights];
                         
                         [self setInteractionEnabled: YES];
                     }];
}

-(void)animateSubsequentSections:(NSIndexPath*) indexPath withOffset:(float) offset
{
    NSInteger numberOfSections = [self numberOfSections];

    for (NSInteger i = indexPath.section + 1; i < numberOfSections; ++i)
    {
        NSInteger numberOfRowsInSection = [self numberOfRowsInSection: i];

        for (NSInteger j = 0; j < numberOfRowsInSection; ++j)
        {
            NSIndexPath *indexPath = [NSIndexPath indexPathForRow:j inSection:i];
            UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];

            cell.transform = CGAffineTransformMakeTranslation(0.f, -offset);
        }
    }
}

-(void)relaxCells:(NSIndexPath*)indexPath :(CGAffineTransform)transform
{
    NSInteger numberOfSections = [self numberOfSections];

    for (NSInteger i = indexPath.section + 1; i < numberOfSections; ++i)
    {
        NSInteger numberOfRowsInSection = [self numberOfRowsInSection: i];

        for (int j = 0; j < numberOfRowsInSection; ++j)
        {
            NSIndexPath *indexPath = [NSIndexPath indexPathForRow:j inSection:i];
            UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];
            cell.transform = transform;
        }
    }
}


@end
