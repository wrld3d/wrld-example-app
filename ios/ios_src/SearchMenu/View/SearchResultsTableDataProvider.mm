// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultsTableDataProvider.h"
#include "CellConstants.h"
#include "CustomTableViewCell.h"
#include "SearchMenuView.h"
#include "UIColors.h"
#include "IconResources.h"
#include "document.h"
#include "SearchMenuViewInterop.h"
#include "MenuSectionViewModel.h"
#include "ImageHelpers.h"
#include "UIHelpers.h"

static NSString *CellIdentifier = @"searchCell";

@interface SearchResultsTableDataProvider()
{
    SearchMenuView* m_pView;
    ExampleApp::Menu::View::IMenuSectionViewModel* m_pSearchResultsSection;
}
@end

@implementation SearchResultsTableDataProvider

- (void)updateSearchResultsSection:(nonnull ExampleApp::Menu::View::IMenuSectionViewModel*)section
{
    if(m_pSearchResultsSection == NULL)
    {
        m_pSearchResultsSection = section;
        [m_pView.pSearchResultsTableView reloadData];
        
        return;
    }
    
    m_pSearchResultsSection = section;
    
    // delete existing rows
    if([m_pView.pSearchResultsTableView numberOfSections] > 0 && [m_pView.pSearchResultsTableView numberOfRowsInSection:0] > 0)
    {
        const NSInteger rows = [m_pView.pSearchResultsTableView numberOfRowsInSection:0];
        
        NSIndexPath* tempPaths[rows];
        
        for(NSInteger i = 0; i < rows; ++i)
        {
            NSIndexPath *tempIndexPath = [NSIndexPath indexPathForRow:i inSection:0];
            tempPaths[i] = tempIndexPath;
        }
        
        [m_pView.pSearchResultsTableView deleteRowsAtIndexPaths:[NSArray arrayWithObjects:tempPaths count:rows] withRowAnimation:UITableViewRowAnimationNone];
    }
    
    // insert new rows
    if(m_pSearchResultsSection->Size() > 0)
    {
        const NSInteger rows = m_pSearchResultsSection->Size();
        
        NSIndexPath* tempPaths[rows];
        
        for(NSInteger i = 0; i < rows; ++i)
        {
            NSIndexPath *tempIndexPath = [NSIndexPath indexPathForRow:i inSection:0];
            tempPaths[i] = tempIndexPath;
        }
        
        [m_pView.pSearchResultsTableView insertRowsAtIndexPaths:[NSArray arrayWithObjects:tempPaths count:rows] withRowAnimation:UITableViewRowAnimationNone];
    }
}

- (float)getRealTableHeight
{
    if(m_pSearchResultsSection == NULL)
    {
        return 0.0f;
    }
    
    return CellConstants::SearchSectionCellHeight * [m_pView.pSearchResultsTableView numberOfRowsInSection:0];
}

- (void)dealloc
{
    [super dealloc];
}

- (nonnull id)initWithParams:(nonnull SearchMenuView*)view
{
    m_pView = view;
    m_pSearchResultsSection = NULL;

    CustomTableView* tableView = m_pView.pSearchResultsTableView;
    [tableView setDataSource:self];
    [tableView setDelegate:self];
    
    return self;
}

- (UITableViewCell *)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if(cell == nil)
    {
        cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
        
        cell.selectionStyle = UITableViewCellSelectionStyleGray;

        if ([cell respondsToSelector:@selector(layoutMargins)])
        {
            cell.layoutMargins = UIEdgeInsetsZero;
        }

        if ([cell respondsToSelector:@selector(separatorInset)])
        {
            [cell setSeparatorInset:UIEdgeInsetsZero];
        }
    }
    
    [(CustomTableViewCell*)cell initCell:(CGFloat)[m_pView.pSearchResultsTableView getCellWidth]
                                        :(CGFloat)[m_pView.pSearchResultsTableView getCellInset]
                                        :indexPath
                                        :(CustomTableView*)tableView
                                        :self];
    
    if(indexPath.row < m_pSearchResultsSection->Size())
    {
        ExampleApp::Menu::View::MenuItemModel item = m_pSearchResultsSection->GetItemAtIndex(static_cast<int>(indexPath.row));
        std::string json = item.SerializeJson();
        [self populateCellWithJson :json :cell];
    }
    else
    {
        NSLog(@"Search results table attempting to fetch out of bounds result.");
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

    ExampleApp::SearchMenu::View::SearchMenuViewInterop* interop = [m_pView getSearchMenuInterop];
    interop->HandleSearchItemSelected(static_cast<int>(indexPath.row));
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    CustomTableViewCell* customCell = (CustomTableViewCell*)cell;
    
    if(![customCell requiresVisualRefresh])
    {
        return;
    }
    
    cell.indentationLevel = 0;
    
    [self setCellInfo:customCell];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return CellConstants::SearchSectionCellHeight;
}

- (void) populateCellWithJson:(std::string)json :(UITableViewCell*)cell
{
    rapidjson::Document document;
    if (!document.Parse<0>(json.c_str()).HasParseError())
    {
        std::string name = document["name"].GetString();
        
        const float imageSize = 36.0f;
        const float imageInset = 6.0f;
        
        const std::string icon = document.HasMember("icon") ? document["icon"].GetString() : "misc";
        const std::string iconResourceName = ExampleApp::Helpers::IconResources::GetSmallIconPathForResourceName(icon);
        
        cell.imageView.image = ExampleApp::Helpers::ImageHelpers::LoadImage(iconResourceName);
        cell.imageView.contentMode = UIViewContentModeScaleToFill;
        CGRect imageFrame = CGRectMake(imageInset,
                                       imageInset,
                                       imageSize,
                                       imageSize);
        
        const float textInsetX = 48.0f;
        const float textY = 4.0f;
        const float detailTextY = 24.0f;
        const float textWidth = [m_pView.pSearchResultsTableView getCellWidth] - textInsetX;
        
        cell.textLabel.text = [NSString stringWithUTF8String:name.c_str()];
        cell.textLabel.font = [UIFont systemFontOfSize:15.0f];
        cell.textLabel.textColor = ExampleApp::Helpers::ColorPalette::TableSearchTextColor;
        [cell.textLabel sizeToFit];
        
        CGRect textFrame = CGRectMake(textInsetX,
                                      textY,
                                      textWidth,
                                      cell.textLabel.frame.size.height);
        
        std::string details = "";
        if (document.HasMember("details"))
        {
            details = document["details"].GetString();
        }
        
        cell.detailTextLabel.text = [NSString stringWithUTF8String:details.c_str()];
        cell.detailTextLabel.font = [UIFont systemFontOfSize:11.0f];
        cell.detailTextLabel.textColor = ExampleApp::Helpers::ColorPalette::TableSearchDetailTextColor;
        [cell.detailTextLabel sizeToFit];
        
        CGRect detailTextFrame = CGRectMake(textInsetX,
                                            detailTextY,
                                            textWidth,
                                            cell.detailTextLabel.frame.size.height);
        
        [(CustomTableViewCell*)cell setContentFrames:imageFrame
                                                    :textFrame
                                                    :detailTextFrame];
    }
}

- (void) setCellInfo:(CustomTableViewCell*)cell
{
    [cell setInfo :false
                  :ExampleApp::Helpers::ColorPalette::UiBorderColor
                  :ExampleApp::Helpers::ColorPalette::TableSearchCellColor
                  :ExampleApp::Helpers::ColorPalette::TableSubCellPressColor
                  :ExampleApp::Helpers::ColorPalette::TableSearchTextColor
                  :ExampleApp::Helpers::ColorPalette::TableSearchTextColor
                  :nil];
}


- (NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    if(m_pSearchResultsSection == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(m_pSearchResultsSection == NULL)
    {
        return 0;
    }
    else
    {
        return m_pSearchResultsSection->Size();
    }
}

@end;
