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
    return CGRectMake(m_leftInset + m_contentInset,
                      1.0f,
                      m_initialWidth - m_contentInset * 2.0f,
                      self.frame.size.height - 2.0f);
}

- (void)layoutSubviews
{
    if([self requiresVisualRefresh])
    {
        m_requiresRefresh = false;
        [super layoutSubviews];
    }
    
    [self setClipsToBounds:YES];
    
    self->pCustomSeparatorContainer.frame = [self getContentViewRect];;
    
    [self.contentView setClipsToBounds:YES];
    self.contentView.frame = [self getContentViewRect];

    CGRect imageFrame = self.imageView.frame;
    imageFrame.origin.x =  0.f;
    self.imageView.frame = imageFrame;

    CGRect accessoryFrame = self.accessoryView.frame;
    accessoryFrame.origin.x = 0.f;
    self.accessoryView.frame = accessoryFrame;
    
    const float textOffset = 6.0f;

    CGRect labelFrame = self.textLabel.frame;
    labelFrame.origin.x = imageFrame.origin.x + imageFrame.size.width + textOffset;
    self.textLabel.frame = labelFrame;
    
    CGRect detailFrame = self.detailTextLabel.frame;
    detailFrame.origin.x = self.textLabel.frame.origin.x;
    self.detailTextLabel.frame = detailFrame;
    
    [self insertSeparators :[self getContentViewRect] :imageFrame];
    [self lazySetBackgroundPresentation];
}

- (void)initCell:(CGFloat)initialWidth
                :(CGFloat)leftInset
                :(CGFloat)contentInset
                :(CGFloat)separatorInset
                :(CustomTableView*)tableView
{
    m_initialWidth = initialWidth;
    m_leftInset = leftInset;
    m_contentInset = contentInset;
    m_separatorInset = separatorInset;
    m_tableView = tableView;
    m_hasSetBackground = false;
    m_hasSetSeparators = false;
    m_selected = false;
    m_highlighted = false;
    self->pCustomSeparatorContainer = [[UIView alloc]  initWithFrame:CGRectMake(0,0,0,0)];
    [self addSubview:self->pCustomSeparatorContainer];
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
        [self.contentView setBackgroundColor: ExampleApp::Helpers::ColorPalette::LightGreyTone];
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

- (void)insertSeparators:(CGRect)cellFrame :(CGRect)imageFrame
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
    
    if(m_isHeader)
    {
        CGFloat topSeparatorY       = 0.f;
        CGFloat separatorHeight     = (1.f / [UIScreen mainScreen].scale);
        CGFloat separatorWidth      = cellFrame.size.width - m_separatorInset * 2.0f;
        
        UIImageView* topSeparator = [[[UIImageView alloc] initWithFrame:CGRectMake(m_separatorInset,
                                                                                   topSeparatorY,
                                                                                   separatorWidth,
                                                                                   separatorHeight)] autorelease];
        
        topSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::MenuSeparatorHeaderColor;
        
        [self->pCustomSeparatorContainer addSubview: topSeparator];
    }
}

@end
