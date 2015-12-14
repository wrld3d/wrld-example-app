// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomTableViewCell.h"
#include "UIColors.h"
#include "ImageHelpers.h"

const float SubViewInset = 0.f;

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
    if(m_isHeader)
    {
        if(m_headerBackgroundImage != nil)
        {
            self.contentView.backgroundColor = [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(m_headerBackgroundImage)];
            m_hasSetBackground = true;
        }
    }
    else
    {
        if(m_subMenuBackgroundImage != nil)
        {
            self.contentView.backgroundColor = [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(m_subMenuBackgroundImage)];
            m_hasSetBackground = true;
        }
    }
}

-(bool) requiresVisualRefresh
{
    return !m_hasSetBackground || !m_hasSetSeparators || m_tableView.hasDynamicCellPresentation || m_requiresRefresh;
}

- (void)layoutSubviews
{
    if([self requiresVisualRefresh])
    {
        m_requiresRefresh = false;
        [super layoutSubviews];
    }
    
    CGRect r = self.contentView.frame;

    if(!m_isHeader)
    {
        r = CGRectMake(SubViewInset,
                       r.origin.y,
                       m_initialWidth - SubViewInset,
                       r.size.height);
    }
    else
    {
        r = CGRectMake(0.f,
                       r.origin.y,
                       m_initialWidth,
                       r.size.height);
    }

    self.contentView.frame = r;
    self->pCustomSeparatorContainer.frame = r;
    self.backgroundColor = [UIColor clearColor];

    CGRect imageFrame = self.imageView.frame;
    const float initialImageX = static_cast<float>(imageFrame.origin.x);
    imageFrame.origin.x =  0.f;
    self.imageView.frame = imageFrame;

    CGRect accessoryFrame = self.accessoryView.frame;
    accessoryFrame.origin.x = 0.f;
    self.accessoryView.frame = accessoryFrame;
    
    const float delta = static_cast<float>(imageFrame.origin.x - initialImageX);

    CGRect labelFrame = self.textLabel.frame;
    labelFrame.origin.x += delta;
    self.textLabel.frame = labelFrame;
    
    CGRect detailFrame = self.detailTextLabel.frame;
    detailFrame.origin.x = self.textLabel.frame.origin.x;
    self.detailTextLabel.frame = detailFrame;
    
    [self insertSeparators :r :imageFrame];
    [self lazySetBackgroundPresentation];
}

- (void)initCell:(CGFloat)initialWidth :(CustomTableView*)tableView;
{
    m_initialWidth = static_cast<float>(initialWidth);
    m_tableView = tableView;
    m_hasSetBackground = false;
    m_hasSetSeparators = false;
    m_selected = false;
    m_highlighted = false;
    self->pCustomSeparatorContainer = [[UIView alloc]  initWithFrame:CGRectMake(0,0,0,0)];
    [self addSubview:self->pCustomSeparatorContainer];
}

- (void)setInfo :(bool)isHeader
                :(NSString*)headerBackgroundImage
                :(NSString*)subMenuBackgroundImage
{
    m_isHeader = isHeader;
    m_headerBackgroundImage = headerBackgroundImage;
    m_subMenuBackgroundImage = subMenuBackgroundImage;
    m_requiresRefresh = true;
}

- (BOOL)canInteract
{
    if([m_tableView respondsToSelector:@selector(inAnimationCeremony)])
    {
        if([m_tableView inAnimationCeremony])
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
        [self.contentView setBackgroundColor: ExampleApp::Helpers::ColorPalette::LightGreyTone];
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
    
    NSIndexPath* indexPath = [m_tableView indexPathForCell:self];
    
    const bool isTop = indexPath.row == 0;
    const bool isBottom = indexPath.row == [m_tableView numberOfRowsInSection:indexPath.section] - 1;
    
    if(!m_isHeader)
    {
        if(!isBottom)
        {
            CGFloat separatorY      = cellFrame.size.height;
            CGFloat separatorHeight = (1.f / [UIScreen mainScreen].scale);
            CGFloat separatorWidth  = cellFrame.size.width - imageFrame.size.width;
            CGFloat separatorInset  = imageFrame.size.width;
            
            UIImageView* separator = [[[UIImageView alloc] initWithFrame:CGRectMake(separatorInset,
                                                                                    separatorY,
                                                                                    separatorWidth,
                                                                                    separatorHeight)] autorelease];
            
            separator.backgroundColor = ExampleApp::Helpers::ColorPalette::MenuSeparatorSubMenuColor;
            [self->pCustomSeparatorContainer addSubview: separator];
        }
    }
    else
    {
        CGFloat topSeparatorY       = 0.f;
        CGFloat bottomSeparatorY    = cellFrame.size.height;
        CGFloat separatorHeight     = (1.f / [UIScreen mainScreen].scale);
        CGFloat separatorWidth      = cellFrame.size.width - SubViewInset;
        CGFloat separatorInset      = cellFrame.origin.x + SubViewInset;
        
        if(!isTop)
        {
            UIImageView* topSeparator = [[[UIImageView alloc] initWithFrame:CGRectMake(separatorInset,
                                                                                       topSeparatorY,
                                                                                       separatorWidth,
                                                                                       separatorHeight)] autorelease];
            
            topSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::MenuSeparatorHeaderColor;
            
            [self->pCustomSeparatorContainer addSubview: topSeparator];
        }
        
        UIImageView* bottomSeparator = [[[UIImageView alloc] initWithFrame:CGRectMake(separatorInset,
                                                                                      bottomSeparatorY,
                                                                                      separatorWidth,
                                                                                      separatorHeight)] autorelease];
        
        bottomSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::MenuSeparatorHeaderColor;
        
        [self->pCustomSeparatorContainer addSubview: bottomSeparator];
    }
}

@end
