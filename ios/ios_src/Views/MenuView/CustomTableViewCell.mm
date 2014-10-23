// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CustomTableViewCell.h"
#include "UIColors.h"

@implementation CustomTableViewCell


- (void)layoutSubviews
{
    [super layoutSubviews];
    
    CGRect r = self.contentView.frame;
    
    if(!m_isHeader)
    {
        r = CGRectMake(m_rightAlignFrame ? 22.f : 0.f,
                       r.origin.y,
                       m_initialWidth - 22.f,
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
    self.backgroundColor = [UIColor clearColor];
    self.contentView.backgroundColor = [UIColor whiteColor];
    
    CGRect imageFrame = self.imageView.frame;
    const float initialImageX = imageFrame.origin.x;
    imageFrame.origin.x = m_rightAlignImage ? (r.size.width - imageFrame.size.width) : 0.f;
    self.imageView.frame = imageFrame;
    
    CGRect accessoryFrame = self.accessoryView.frame;
    accessoryFrame.origin.x = m_rightAlignImage ? (r.size.width - accessoryFrame.size.width) : 0.f;
    self.accessoryView.frame = accessoryFrame;
    
    if(!m_rightAlignImage)
    {
        const float delta = (imageFrame.origin.x - initialImageX);
        
        CGRect labelFrame = self.textLabel.frame;
        labelFrame.origin.x += delta;
        self.textLabel.frame = labelFrame;
        
        CGRect detailFrame = self.detailTextLabel.frame;
        detailFrame.origin.x += delta;
        self.detailTextLabel.frame = detailFrame;
    }
}

- (void)initCell:(float)initialWidth :(UITableView*)tableView;
{
    m_initialWidth = initialWidth;
    m_tableView = tableView;
}

- (void)setAlignInfo:(bool)rightAlignFrame :(bool)rightAlignImage :(bool)isHeader
{
    m_rightAlignFrame = rightAlignFrame;
    m_rightAlignImage = rightAlignImage;
    m_isHeader = isHeader;
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
        [self.contentView setBackgroundColor: [UIColor whiteColor]];
        return;
    }
    
    if (highlighted)
    {
        [self.contentView setBackgroundColor: ExampleApp::Helpers::ColorPalette::LightGreyTone];
    }
    else
    {
        [self.contentView setBackgroundColor: [UIColor whiteColor]];
    }
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    if(![self canInteract])
    {
        [self.contentView setBackgroundColor: [UIColor whiteColor]];
        return;
    }
    
    if (selected)
    {
        [self.contentView setBackgroundColor: ExampleApp::Helpers::ColorPalette::LightGreyTone];
    }
    else
    {
        [self.contentView setBackgroundColor: [UIColor whiteColor]];
    }
}

@end
