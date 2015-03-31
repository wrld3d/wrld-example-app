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
#include "ImageHelpers.h"
#include <sstream>

@implementation CustomTableDataProvider

NSInteger const SubItemCellOpenableMenuArrowTag = 1;

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
    [self.pOpenableMenuArrow release];
    [super dealloc];
}

- (id)initWithParams:(MenuView*)view
{
    m_pView = view;

    CustomTableView* tableView = [m_pView pTableview];
    [tableView setDataSource:self];
    [tableView setDelegate:self];

    self.pOpenableMenuArrow = ExampleApp::Helpers::ImageHelpers::LoadImage(@"sub_menu_arrow");
    return self;
}

- (UITableViewCell *)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    std::stringstream ss;

    const ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);
    const NSInteger index = section.IsExpandable() ? indexPath.row - 1 : indexPath.row;
    const bool isExpandableHeader = section.IsExpandable() && indexPath.row == 0;

    static NSString *CellIdentifier = @"cell";

    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if(cell == nil)
    {
        cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
        [(CustomTableViewCell*)cell initCell: m_pView.pTableview.bounds.size.width :(CustomTableView*)tableView];
        cell.selectionStyle = UITableViewCellSelectionStyleGray;

        UIImageView* pOpenableMenuArrowView = [[[UIImageView alloc] initWithImage:self.pOpenableMenuArrow] autorelease];
        pOpenableMenuArrowView.tag = SubItemCellOpenableMenuArrowTag;

        const float tableWidth = m_pView.pTableview.bounds.size.width;
        const float openableArrowX = [m_pView isRightMenu] ? (tableWidth - 20.f) : 0.f;
        pOpenableMenuArrowView.frame = CGRectMake(openableArrowX,
                                                  (SECTION_HEADER_CELL_HEIGHT*0.5f) - 8.f,
                                                  pOpenableMenuArrowView.frame.size.width,
                                                  pOpenableMenuArrowView.frame.size.height);
        
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
    CustomTableViewCell* customCell = (CustomTableViewCell*)cell;
    
    if(![customCell requiresVisualRefresh])
    {
        return;
    }
    
    ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);
    UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];

    if(section.IsExpandable() && indexPath.row != 0)
    {
        cell.textLabel.font = [UIFont systemFontOfSize:[self getTextLabelFontSize:false]];
        cell.indentationLevel = 0;

        openableArrow.hidden = true;
        [self setCellAlignInfo:customCell:false];
    }
    else
    {
        cell.textLabel.font = [UIFont systemFontOfSize:[self getTextLabelFontSize:true]];
        cell.indentationLevel = 0;
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

    cell.textLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextHeaderColour;
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
        
        if(document.HasMember("icon"))
        {
            std::string icon = document["icon"].GetString();
            std::string iconResourceName = ExampleApp::Helpers::IconResources::GetSmallIconPathForResourceName(icon);
            
            cell.imageView.image = ExampleApp::Helpers::ImageHelpers::LoadImage(iconResourceName);
            cell.imageView.contentMode = UIViewContentModeScaleToFill;
        }
        else
        {
            cell.imageView.image = nil;
        }

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
            subLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextHeaderColour;
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
    [cell setAlignInfo :isRightMenu :!isRightMenu :isHeader :@"menu_background1" :@"menu_background2"];
}


- (NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    return m_currentSections.size();
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return m_currentSections.at(section)->Size();
}

- (CGAffineTransform)computeOpenableArrowTransform:(float)degrees
{
    return CGAffineTransformRotate(CGAffineTransformIdentity, Eegeo::Math::Deg2Rad(degrees));
}

- (void)showOpenableArrowClosed:(UITableViewCell *)cell
{
    const float angle = [m_pView isRightMenu] ? 0.f : 180.f;
    UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];
    openableArrow.transform = [self computeOpenableArrowTransform:angle];
}

- (void)showOpenableArrowOpen:(UITableViewCell *)cell
{
    UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];
    openableArrow.transform = [self computeOpenableArrowTransform:270.f];
}
@end;
