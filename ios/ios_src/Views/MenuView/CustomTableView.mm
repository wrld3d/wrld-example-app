// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "CustomTableView.h"
#import <QuartzCore/QuartzCore.h>

@implementation CustomTableView
{
    float m_animationSpeed;
    bool m_inAnimationCeremony;
    UIScrollView* m_pContainer;
}

- (instancetype)initWithFrame:(CGRect)frame style:(UITableViewStyle)style
{
    return [self initWithFrame: frame style: style container: nil];
}

- (instancetype)initWithFrame:(CGRect)frame style:(UITableViewStyle)style container:(UIScrollView*)container
{
    id it = [super initWithFrame:frame style:style];
    m_pContainer = container;
    m_animationSpeed = 0.3f;
    m_inAnimationCeremony = NO;
    return it;
}


-(BOOL)inAnimationCeremony
{
    return m_inAnimationCeremony;
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    
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
    
    int count = 1;
    float height = -1;
    float offset = 0.f;
    
    for (NSIndexPath *indexPath in indexPaths)
    {
        UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];
        height = cell.bounds.size.height;
        offset += height;
        cell.transform = CGAffineTransformMakeTranslation(0.f, -height * count++);
    }
    
    [self animateSubsequentSections: [indexPaths lastObject] withOffset: offset];
    
    [UIView beginAnimations: @"cellTransform" context: NULL];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(rowsAddedCompleted:finished:context:)];
    for (NSIndexPath *indexPath in indexPaths)
    {
        UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];;
        
        [UIView setAnimationDuration: m_animationSpeed];
        cell.transform = CGAffineTransformIdentity;
    }
    
    [self relaxCells: [indexPaths lastObject] :CGAffineTransformIdentity];
    [UIView commitAnimations];
}

- (void)rowsAddedCompleted:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context
{
    [self setInteractionEnabled: YES];
}

- (void)rowsDeleteComplete:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context
{
    for (int section = 0; section < [self numberOfSections]; section++)
    {
        for (int row = 0; row < [self numberOfRowsInSection:section]; row++)
        {
            NSIndexPath* cellPath = [NSIndexPath indexPathForRow:row inSection:section];
            UITableViewCell* cell = [self cellForRowAtIndexPath:cellPath];
            cell.transform = CGAffineTransformIdentity;
        }
    }
    
    [self reloadData];
    [self setInteractionEnabled: YES];
}

-(void)deleteRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation
{
    [self setInteractionEnabled: NO];
    
    int count = 1;
    float height = -1;
    
    [UIView beginAnimations: @"cellTransform" context: NULL];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(rowsDeleteComplete:finished:context:)];
    
    float offset = 0.f;
    
    for (NSIndexPath *indexPath in indexPaths)
    {
        UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];
        
        height = cell.bounds.size.height;
        [UIView setAnimationDuration: m_animationSpeed];
        offset = (-height * count++);
        cell.transform = CGAffineTransformMakeTranslation(0.f, offset);
    }
    
    const size_t cellsDeleted = indexPaths.count;
    m_pContainer.contentSize = CGSizeMake(self.contentSize.width, self.contentSize.height - (cellsDeleted*height));
        [self scrollRectToVisible: CGRectMake(0, 0, self.contentSize.width, 0) animated:YES];
    
    [self relaxCells: [indexPaths lastObject]: CGAffineTransformMakeTranslation(0.f, offset)];
    [UIView commitAnimations];
}

-(void)animateSubsequentSections:(NSIndexPath*) indexPath withOffset:(float) offset
{
    int numberOfSections = [self numberOfSections];

    for (int i = indexPath.section + 1; i < numberOfSections; ++i)
    {
        NSInteger numberOfRowsInSection = [self numberOfRowsInSection: i];
        
        for (int j = 0; j < numberOfRowsInSection; ++j)
        {
            NSIndexPath *indexPath = [NSIndexPath indexPathForRow:j inSection:i];
            UITableViewCell *cell = [self cellForRowAtIndexPath:indexPath];
            
            cell.transform = CGAffineTransformMakeTranslation(0.f, -offset);
        }
    }
}

-(void)relaxCells:(NSIndexPath*)indexPath :(CGAffineTransform)transform
{
    int numberOfSections = [self numberOfSections];
    
    for (int i = indexPath.section + 1; i < numberOfSections; ++i)
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
