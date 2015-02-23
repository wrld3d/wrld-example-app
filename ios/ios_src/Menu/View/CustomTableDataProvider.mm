// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomTableDataProvider.h"
#include "CellConstants.h"
#include "CustomTableViewCell.h"
#include "MenuView.h"
#include "UIColors.h"
#include "IconResources.h"
#include "document.h"
#include "MenuViewInterop.h"
#include "MenuSectionViewModel.h"

#include <sstream>

@implementation CustomTableDataProvider

NSInteger const SubItemCellShadowViewTag = 1;
NSInteger const SubItemCellShadowFlippedViewTag = 2;
NSInteger const SubItemCellOpenableMenuArrowTag = 3;

- (size_t)getTotalNumberOfCellsInTableView
{
    return ExampleApp::Menu::View::NumberOfCells(m_currentSections);
}

- (size_t)getNumberOfSections
{
    return m_currentSections.size();
}

- (void)updateMenuSections:(ExampleApp::Menu::View::TSections*)sections
{
    m_currentSections = *sections;
    [[m_pView pTableview] reloadData];

}

- (void)dealloc
{
    [self.pSubItemShadow release];
    [self.pSubItemShadowFlipped release];
    [self.pOpenableMenuArrow release];
    [super dealloc];
}

- (id)initWithParams:(MenuView*)view
{
    m_pView = view;

    CustomTableView* tableView = [m_pView pTableview];
    [tableView setDataSource:self];
    [tableView setDelegate:self];

    self.pSubItemShadow = [UIImage imageNamed:@"shadow_01"];
    self.pSubItemShadowFlipped = [UIImage imageNamed:@"shadow_01_flip"];
    self.pOpenableMenuArrow = [UIImage imageNamed:@"arrow2"];
    return self;
}

- (UITableViewCell *)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    std::stringstream ss;

    const ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);
    const NSInteger index = section.IsExpandable() ? indexPath.row - 1 : indexPath.row;
    const bool isExpandableHeader = section.IsExpandable() && indexPath.row == 0;
    const bool isLastExpandableSection = section.IsExpandable() && indexPath.section == m_currentSections.size() - 1;
    const bool flippedShadowIsVisible = !isLastExpandableSection;

    static NSString *CellIdentifier = @"cell";

    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if(cell == nil)
    {
        bool isRightMenu = [m_pView isRightMenu];
        cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
        [(CustomTableViewCell*)cell initCell: m_pView.pTableview.bounds.size.width :(CustomTableView*)tableView];
        cell.selectionStyle = UITableViewCellSelectionStyleGray;

        UIImageView* pShadowView = [[[UIImageView alloc] initWithImage:self.pSubItemShadow] autorelease];
        pShadowView.autoresizingMask = isRightMenu ? UIViewAutoresizingFlexibleRightMargin : UIViewAutoresizingFlexibleLeftMargin;
        pShadowView.tag = SubItemCellShadowViewTag;
        pShadowView.frame = CGRectMake(0, 0, cell.bounds.size.width, 32);
        [cell addSubview:pShadowView];

        UIImageView* pShadowFlippedView = [[[UIImageView alloc] initWithImage:self.pSubItemShadowFlipped] autorelease];
        pShadowFlippedView.tag = SubItemCellShadowFlippedViewTag;
        pShadowFlippedView.frame = CGRectMake(0, 0, cell.bounds.size.width, 32);
        pShadowFlippedView.autoresizingMask = isRightMenu ? UIViewAutoresizingFlexibleRightMargin : UIViewAutoresizingFlexibleLeftMargin;
        [cell addSubview:pShadowFlippedView];

        UIImageView* pOpenableMenuArrowView = [[[UIImageView alloc] initWithImage:self.pOpenableMenuArrow] autorelease];
        pOpenableMenuArrowView.tag = SubItemCellOpenableMenuArrowTag;

        const float tableWidth = m_pView.pTableview.bounds.size.width;
        const float openableArrowX = [m_pView isRightMenu] ? (tableWidth - 20.f) : 0.f;
        pOpenableMenuArrowView.frame = CGRectMake(openableArrowX, (SECTION_HEADER_CELL_HEIGHT*0.5f) - 8.f, 16.f, 16.f);
        [cell addSubview:pOpenableMenuArrowView];

        if ([cell respondsToSelector:@selector(layoutMargins)])
        {
            cell.layoutMargins = UIEdgeInsetsZero;
        }

        if ([cell respondsToSelector:@selector(separatorInset)])
        {
            [cell setSeparatorInset:UIEdgeInsetsZero];
        }
    }

    [self setFlippedShadowVisibility: (CustomTableViewCell*) cell : flippedShadowIsVisible];

    const bool isHeader = isExpandableHeader | !section.IsExpandable();

    if(isExpandableHeader)
    {
        std::string json = section.SerializeJson();
        [self populateCellWithJson :json :cell :isHeader];
    }
    else
    {
        ExampleApp::Menu::View::MenuItemModel item = section.GetItemAtIndex(index);
        std::string json = item.SerializeJson();
        [self populateCellWithJson :json :cell :isHeader];
    }

    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    CustomTableViewCell *cell = (CustomTableViewCell*)[tableView cellForRowAtIndexPath:indexPath];
    if(![cell canInteract])
    {
        return;
    }

    ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);

    if(section.IsExpandable() && indexPath.row == 0)
    {
        // only first row toggles expand/collapse.
        NSInteger rows;

        NSMutableArray *tmpArray = [NSMutableArray array];

        if(section.IsExpanded())
        {
            rows = section.Size();
            section.Contract();
            [self showOpenableArrowClosed:cell];
        }
        else
        {
            section.Expand();
            rows = section.Size();
            [self showOpenableArrowOpen:cell];
        }

        for(int i=1; i <rows; i++)
        {
            NSIndexPath *tmpIndexPath = [NSIndexPath indexPathForRow:i inSection:indexPath.section];
            [tmpArray addObject:tmpIndexPath];
        }

        if(!section.IsExpanded())
        {
            [tableView deleteRowsAtIndexPaths:tmpArray withRowAnimation:UITableViewRowAnimationNone];
        }
        else
        {
            [tableView insertRowsAtIndexPaths:tmpArray withRowAnimation:UITableViewRowAnimationNone];
        }

    }
    else
    {
        ExampleApp::Menu::View::MenuViewInterop* interop = [m_pView getInterop];
        interop->HandleItemSelected(indexPath.section, indexPath.row);
    }
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);
    UIImageView *shadow = (UIImageView*)[cell viewWithTag:SubItemCellShadowViewTag];
    UIImageView *shadowFlipped = (UIImageView*)[cell viewWithTag:SubItemCellShadowFlippedViewTag];
    UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];

    CustomTableViewCell* customCell = (CustomTableViewCell*)cell;

    if(section.IsExpandable() && indexPath.row != 0)
    {
        cell.textLabel.font = [UIFont systemFontOfSize:[self getTextLabelFontSize:false]];
        cell.indentationLevel = 0;

        BOOL isFirstChild = indexPath.row == 1;
        BOOL isLastChild = indexPath.row == [tableView numberOfRowsInSection:indexPath.section] - 1;

        shadow.hidden = !isFirstChild;
        shadowFlipped.hidden = !isLastChild;
        openableArrow.hidden = true;
        [self setCellAlignInfo:customCell:false];
    }
    else
    {
        cell.textLabel.font = [UIFont systemFontOfSize:[self getTextLabelFontSize:true]];
        cell.indentationLevel = 0;
        shadow.hidden = true;
        shadowFlipped.hidden = true;
        openableArrow.hidden = !section.IsExpandable();

        if(section.IsExpanded())
        {
            [self showOpenableArrowOpen :cell];
        }
        else
        {
            [self showOpenableArrowClosed :cell];
        }

        [self setCellAlignInfo:customCell:true];
    }

    cell.textLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
    [cell setBackgroundColor:ExampleApp::Helpers::ColorPalette::WhiteTone];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);

    if(section.IsExpandable() && indexPath.row != 0)
    {
        return SUB_SECTION_CELL_HEIGHT;
    }
    else
    {
        return SECTION_HEADER_CELL_HEIGHT;
    }
}

- (void) populateCellWithJson:(std::string)json :(UITableViewCell*)cell :(const bool)isHeader
{
    rapidjson::Document document;
    if (!document.Parse<0>(json.c_str()).HasParseError())
    {
        std::string name = document["name"].GetString();
        std::string icon = document["icon"].GetString();
        std::string iconResourceName = ExampleApp::Helpers::IconResources::GetSmallIconPathForResourceName(icon);

        cell.imageView.image = [UIImage imageNamed: [NSString stringWithUTF8String:iconResourceName.c_str()]];
        cell.imageView.contentMode = UIViewContentModeScaleToFill;

        if ([m_pView isRightMenu])
        {
            cell.textLabel.text = [NSString stringWithUTF8String:name.c_str()];
        }
        else
        {
            for (UIView* subview in cell.contentView.subviews)
            {
                [subview removeFromSuperview];
            }

            const float subLabelWidth = 160.f;
            const float subLabelHeight = isHeader ? SECTION_HEADER_CELL_HEIGHT : SUB_SECTION_CELL_HEIGHT;
            UILabel *subLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, subLabelWidth, subLabelHeight)];
            subLabel.backgroundColor = [UIColor clearColor];
            subLabel.textAlignment = NSTextAlignmentRight;
            subLabel.text = [NSString stringWithUTF8String:name.c_str()];
            subLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
            subLabel.highlightedTextColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
            subLabel.font = [UIFont systemFontOfSize: [self getTextLabelFontSize: isHeader]];
            [cell.contentView addSubview: subLabel];
        }
    }
}

- (float)getTextLabelFontSize:(bool)headline
{
    return headline ? 25.0 : 20.f;
}

- (void) setCellAlignInfo:(CustomTableViewCell*)cell :(bool)isHeader
{
    bool isRightMenu = [m_pView isRightMenu];
    [cell setAlignInfo :isRightMenu :!isRightMenu :isHeader];
}


- (NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    return m_currentSections.size();
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return m_currentSections.at(section)->Size();
}

- (void) setFlippedShadowVisibility: (CustomTableViewCell*)cell :(BOOL) flippedShadowIsVisible
{
    UIImageView *shadow = (UIImageView*) [cell viewWithTag: SubItemCellShadowFlippedViewTag];
    CGFloat alpha = flippedShadowIsVisible ? 1.f : 0.f;
    shadow.alpha = alpha;
}

- (CGAffineTransform)computeOpenableArrowTransform:(float)degrees
{
    return CGAffineTransformRotate(CGAffineTransformIdentity, Eegeo::Math::Deg2Rad(degrees));
}

- (void)showOpenableArrowClosed:(UITableViewCell *)cell
{
    const float angle = [m_pView isRightMenu] ? 180.f : 0.f;
    UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];
    openableArrow.transform = [self computeOpenableArrowTransform:angle];
}

- (void)showOpenableArrowOpen:(UITableViewCell *)cell
{
    UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];
    openableArrow.transform = [self computeOpenableArrowTransform:90.f];
}
@end;
