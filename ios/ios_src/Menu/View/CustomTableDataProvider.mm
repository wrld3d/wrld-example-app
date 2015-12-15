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
#include "UIHelpers.h"
#include <sstream>

static NSString *CellIdentifier = @"cell";
static NSString *SearchCellIdentifier = @"searchCell";

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

- (float)getRealTableHeight
{
    int numberOfHeaders = 0;
    int numberOfCells = 0;
    
    for(ExampleApp::Menu::View::TSections::iterator it = m_currentSections.begin(); it != m_currentSections.end(); ++it)
    {
        if((*it)->IsExpandable())
        {
            ++numberOfHeaders;
            if((*it)->IsExpanded())
            {
                numberOfCells += (*it)->GetTotalItemCount();
            }
        }
        else
        {
            numberOfHeaders += (*it)->GetTotalItemCount();
        }
    }
    
    return SECTION_HEADER_CELL_HEIGHT * numberOfHeaders + SUB_SECTION_CELL_HEIGHT * numberOfCells;
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
    
    NSString *CurrentCellIdentifier = section.IsSearchResult() ? SearchCellIdentifier : CellIdentifier;
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CurrentCellIdentifier];
    if(cell == nil)
    {
        if(!section.IsSearchResult())
        {
            cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CurrentCellIdentifier] autorelease];
        }
        else
        {
            cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CurrentCellIdentifier] autorelease];
        }
        
        [(CustomTableViewCell*)cell initCell: m_pView.pTableview.bounds.size.width :(CustomTableView*)tableView];
        cell.selectionStyle = UITableViewCellSelectionStyleGray;

        UIImageView* pOpenableMenuArrowView = [[[UIImageView alloc] initWithImage:self.pOpenableMenuArrow] autorelease];
        pOpenableMenuArrowView.tag = SubItemCellOpenableMenuArrowTag;

        const float tableWidth = static_cast<float>(m_pView.pTableview.bounds.size.width);
        const float openableArrowX = (tableWidth - 20.f);
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
        [self populateCellWithJson :json :cell :isHeader :section.IsSearchResult()];
    }
    else
    {
        ExampleApp::Menu::View::MenuItemModel item = section.GetItemAtIndex(static_cast<int>(index));
        std::string json = item.SerializeJson();
        [self populateCellWithJson :json :cell :isHeader :section.IsSearchResult()];
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
        interop->HandleItemSelected(static_cast<int>(indexPath.section), static_cast<int>(indexPath.row));
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
        cell.textLabel.font = [UIFont systemFontOfSize:[self getTextLabelFontSize:false :section.IsSearchResult()]];
        cell.indentationLevel = 0;

        openableArrow.hidden = true;
        [self setCellInfo:customCell:false:section.IsSearchResult()];
    }
    else
    {
        cell.textLabel.font = [UIFont systemFontOfSize:[self getTextLabelFontSize:true:section.IsSearchResult()]];
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

        [self setCellInfo:customCell:true:section.IsSearchResult()];
    }

    cell.textLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextHeaderColour;
    [cell setBackgroundColor:ExampleApp::Helpers::ColorPalette::WhiteTone];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);

    if(!section.IsSearchResult())
    {
        if(section.IsExpandable() && indexPath.row != 0)
        {
            return SUB_SECTION_CELL_HEIGHT;
        }
        else
        {
            return SECTION_HEADER_CELL_HEIGHT;
        }
    }
    else
    {
        return SEARCH_SECTION_CELL_HEIGHT;
    }
}

- (void) populateCellWithJson:(std::string)json :(UITableViewCell*)cell :(bool)isHeader :(bool)isSearchResult
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
        
        if(!isSearchResult)
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
            subLabel.font = [UIFont systemFontOfSize: [self getTextLabelFontSize: isHeader:isSearchResult]];
            [cell.contentView addSubview: subLabel];
        }
        else
        {
            cell.textLabel.text = [NSString stringWithUTF8String:name.c_str()];
            [cell.textLabel sizeToFit];
            
            std::string details = document["details"].GetString();
            
            cell.detailTextLabel.text = [NSString stringWithUTF8String:details.c_str()];
            cell.detailTextLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        }
    }
}

- (float)getTextLabelFontSize :(bool)headline :(bool)isSearchResult
{
    if(!isSearchResult)
    {
        return headline ? 25.0 : 20.f;
    }
    else
    {
        return 12.0f;
    }
}

- (void) setCellInfo:(CustomTableViewCell*)cell :(bool)isHeader :(bool)isSearchResult
{
    if(!isSearchResult)
    {
        [cell setInfo :isHeader
                      :@"menu_background1"
                      :@"menu_background1"];
    }
    else
    {
        [cell setInfo :isHeader
                      :ExampleApp::Helpers::UIHelpers::UsePhoneLayout() ? @"search_result_background_small" : @"search_result_background"
                      :@""];
    }
}


- (NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    return m_currentSections.size();
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return m_currentSections.at(section)->Size();
}

- (void)collapseAll
{
    for(int i = 0; i < m_currentSections.size(); ++i)
    {
        if(m_currentSections[i]->IsExpandable() && m_currentSections[i]->IsExpanded())
        {
            NSInteger rows;
            
            NSMutableArray *tmpArray = [NSMutableArray array];
            
            rows = m_currentSections[i]->Size();
            m_currentSections[i]->Contract();
            
            [self showOpenableArrowClosed:[m_pView.pTableview cellForRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:i]]];
            
            for(int j = 1; j < rows; ++j)
            {
                NSIndexPath *tmpIndexPath = [NSIndexPath indexPathForRow:j inSection:i];
                [tmpArray addObject:tmpIndexPath];
            }
            
            [m_pView.pTableview deleteRowsAtIndexPaths:tmpArray withRowAnimation:UITableViewRowAnimationNone];
        }
    }
}

- (CGAffineTransform)computeOpenableArrowTransform:(float)degrees
{
    return CGAffineTransformRotate(CGAffineTransformIdentity, Eegeo::Math::Deg2Rad(degrees));
}

- (void)showOpenableArrowClosed:(UITableViewCell *)cell
{
    const float angle = 0.f;
    UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];
    openableArrow.transform = [self computeOpenableArrowTransform:angle];
}

- (void)showOpenableArrowOpen:(UITableViewCell *)cell
{
    UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];
    openableArrow.transform = [self computeOpenableArrowTransform:270.f];
}
@end;
