// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomTableViewCell.h"
#include "UIColors.h"
#include "ImageHelpers.h"

@implementation CustomTableViewCell
{
    UIView* pCustomSeparatorContainer;
    bool m_hasSetBackground;
    bool m_hasSetSeparators;
    bool m_selected;
    bool m_highlighted;
    bool m_requiresRefresh;
    bool m_customContentFramesSet;
}

-(void) lazySetBackgroundPresentation
{
    if(m_hasSetBackground && !m_tableView.hasDynamicCellPresentation)
    {
        return;
    }
    
    [self setBackgroundPresentation];
}

-(void) setBackgroundPresentation
{
    self.backgroundColor = m_pBackgroundColor;
    self.contentView.backgroundColor = m_pContentBackgroundColor;
    m_hasSetBackground = true;
}

-(bool) requiresVisualRefresh
{
    return !m_hasSetBackground || !m_hasSetSeparators || m_tableView.hasDynamicCellPresentation || m_requiresRefresh;
}

- (CGRect)getContentViewRect
{
    return CGRectMake(m_leftInset,
                      0.0f,
                      m_initialWidth,
                      self.frame.size.height - 1.0f);
}

- (void)layoutSubviews
{
    if([self requiresVisualRefresh])
    {
        m_requiresRefresh = false;
        [super layoutSubviews];
    }
    
    [self setClipsToBounds:YES];
    
    self->pCustomSeparatorContainer.frame = [self getContentViewRect];
    
    [self.contentView setClipsToBounds:YES];
    self.contentView.frame = [self getContentViewRect];
    
    if(m_customContentFramesSet)
    {
        self.imageView.frame = m_imageFrame;
        self.textLabel.frame = m_textFrame;
        self.detailTextLabel.frame = m_detailTextFrame;
    }
    
    [self insertSeparators :[self getContentViewRect]];
    [self lazySetBackgroundPresentation];
}

- (void)initCell:(CGFloat)initialWidth
                :(CGFloat)leftInset
                :(CustomTableView*)tableView
{
    m_initialWidth = initialWidth;
    m_leftInset = leftInset;
    m_tableView = tableView;
    m_hasSetBackground = false;
    m_hasSetSeparators = false;
    m_selected = false;
    m_highlighted = false;
    m_customContentFramesSet = false;
    self->pCustomSeparatorContainer = [[UIView alloc]  initWithFrame:CGRectMake(0,0,0,0)];
    [self addSubview:self->pCustomSeparatorContainer];
}

- (void)setContentFrames:(CGRect)imageFrame
                        :(CGRect)textFrame
                        :(CGRect)detailTextFrame
{
    m_imageFrame = imageFrame;
    m_textFrame = textFrame;
    m_detailTextFrame = detailTextFrame;
    
    m_customContentFramesSet = true;
}

- (void)setInfo :(bool)isHeader
                :(UIColor*)pBackgroundColor
                :(UIColor*)pContentBackgroundColor
                :(UIColor*)pPressColor
{
    m_isHeader = isHeader;
    m_pBackgroundColor = pBackgroundColor;
    m_pContentBackgroundColor = pContentBackgroundColor;
    m_pPressColor = pPressColor;
    m_requiresRefresh = true;
}

- (BOOL)canInteract
{
    if([m_tableView respondsToSelector:@selector(isAnimating)])
    {
        if([m_tableView isAnimating])
        {
            return false;
        }
    }

    return true;
}

- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated
{
    if(![self canInteract])
    {
        [self setBackgroundPresentation];
        return;
    }

    if (highlighted)
    {
        m_highlighted = true;
        [self.contentView setBackgroundColor:m_pPressColor];
    }
    else
    {
        if(m_highlighted)
        {
            [self setBackgroundPresentation];
        }
        m_highlighted = false;
    }
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    if(![self canInteract])
    {
        [self setBackgroundPresentation];
        return;
    }

    if (selected)
    {
        [self.contentView setBackgroundColor:m_pPressColor];
        m_selected = true;
    }
    else
    {
        if(m_selected)
        {
            [self setBackgroundPresentation];
        }
        m_selected = false;
    }
}

- (void)insertSeparators:(CGRect)cellFrame
{
    if(m_hasSetSeparators && !m_tableView.hasDynamicCellPresentation)
    {
        return;
    }
    
    m_hasSetSeparators = true;
    
    if([self->pCustomSeparatorContainer subviews] != nil) {
        for (UIView *subview in [self->pCustomSeparatorContainer subviews]) {
            [subview removeFromSuperview];
        }
    }
    
    NSIndexPath* indexPath = [m_tableView indexPathForCell:self];
    
    const bool isTop = indexPath.section == 0;
    
    if(m_isHeader && !isTop)
    {
        CGFloat topSeparatorY       = 0.f;
        CGFloat separatorHeight     = (1.f / [UIScreen mainScreen].scale);
        CGFloat separatorWidth      = cellFrame.size.width;
        
        UIImageView* topSeparator = [[[UIImageView alloc] initWithFrame:CGRectMake(0.0f,
                                                                                   topSeparatorY,
                                                                                   separatorWidth,
                                                                                   separatorHeight)] autorelease];
        
        topSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::TableSeparatorHeaderColor;
        
        [self->pCustomSeparatorContainer addSubview: topSeparator];
    }
}

@end
