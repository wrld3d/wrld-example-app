// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuDataProvider.h"
#include "CustomTableViewCell.h"
#include "UIColors.h"
#include "MenuView.h"
#include "MenuItemModel.h"
#include "IconResources.h"


#include <sstream>

@implementation SearchResultMenuDataProvider

CGFloat const SearchResultRowHeight = 53.0f;

- (void) setCellAlignInfo:(CustomTableViewCell*)cell :(bool)isHeader
{
    bool isRightMenu = [m_pView isRightMenu];
    [cell setAlignInfo :isRightMenu :false :isHeader];
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
        ExampleApp::Menu::View::MenuItemModel item = section.GetItemAtIndex(index);

        std::string name = item.Name();
        std::string details = item.Details();
        std::string icon = item.Icon();

        cell.textLabel.text = [NSString stringWithUTF8String:name.c_str()];
        cell.detailTextLabel.text = [NSString stringWithUTF8String:details.c_str()];
        cell.detailTextLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;

        std::string iconResourceName = ExampleApp::Helpers::IconResources::GetSearchResultIconPathForResourceName(icon);
        cell.imageView.image = [UIImage imageNamed: [NSString stringWithUTF8String:iconResourceName.c_str()]];
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
    return 16.f;
}

@end
