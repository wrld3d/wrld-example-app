// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuDataProvider.h"

#include "CellConstants.h"
#include "CustomTableViewCell.h"
#include "IconResources.h"
#include "ImageHelpers.h"
#include "MenuView.h"
#include "UIColors.h"
#include "UIHelpers.h"

@implementation SearchResultMenuDataProvider

CGFloat const SearchResultRowHeight = SECTION_HEADER_CELL_HEIGHT;

- (void) setCellAlignInfo:(CustomTableViewCell*)cell :(bool)isHeader
{
    bool isRightMenu = [m_pView isRightMenu];
    
    [cell setAlignInfo :isRightMenu
                       :false
                       :isHeader
                       :ExampleApp::Helpers::UIHelpers::UsePhoneLayout() ? @"search_result_background_small" : @"search_result_background"
                       :@""];
}

- (UITableViewCell *)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    std::stringstream ss;

    static NSString *CellIdentifier = @"cell";

    CustomTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if(cell == nil)
    {
        cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
        [cell initCell: m_pView.pTableview.bounds.size.width :(CustomTableView*)tableView];
    }

    const ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);
    NSInteger index = section.IsExpandable() ? indexPath.row - 1 : indexPath.row;

    if(section.IsExpandable() && indexPath.row == 0)
    {
        ss << section.Name();
        cell.textLabel.text = [NSString stringWithUTF8String:ss.str().c_str()];
        ss.clear();
    }
    else
    {
        ExampleApp::Menu::View::MenuItemModel item = section.GetItemAtIndex(static_cast<int>(index));

        cell.textLabel.text = [NSString stringWithUTF8String:item.Name().c_str()];
        [cell.textLabel sizeToFit];
        cell.detailTextLabel.text = [NSString stringWithUTF8String:item.Details().c_str()];
        cell.detailTextLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        
        std::string iconResourceName = ExampleApp::Helpers::IconResources::GetSearchResultIconPathForResourceName(item.Icon());
        cell.imageView.image = ExampleApp::Helpers::ImageHelpers::LoadImage(iconResourceName);
        cell.imageView.contentMode = UIViewContentModeScaleToFill;
    }

    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return SearchResultRowHeight;
}

- (float)getTextLabelFontSize:(bool)headline
{
    return 12.f;
}

@end
