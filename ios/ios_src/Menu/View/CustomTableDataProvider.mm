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

static NSString *HeaderCellIdentifier = @"headercell";
static NSString *SubSectionCellIdentifier = @"subsectioncell";

@implementation CustomTableDataProvider

NSInteger const SubItemCellOpenableMenuArrowTag = 1;

- (void)updateMenuSections:(ExampleApp::Menu::View::TSections*)sections
{
    bool sectionsUpdated = false;
    
    if(sections->size() != m_currentSections.size())
    {
        sectionsUpdated = true;
    }
    else
    {
        for(int i = 0; i < sections->size(); ++i)
        {
            if((*sections)[i] != m_currentSections[i])
            {
                sectionsUpdated = true;
                break;
            }
        }
    }
    
    if(sectionsUpdated)
    {
        m_currentSections = *sections;
        
        [m_pView.pTableView reloadData];
        [m_pView refreshTableHeights];
    }
}

- (float)getRealTableHeight
{
    int numberOfHeaders = 0;
    int numberOfSubSectionCells = 0;
    
    for(ExampleApp::Menu::View::TSections::iterator it = m_currentSections.begin(); it != m_currentSections.end(); ++it)
    {
        if((*it)->IsExpandable())
        {
            ++numberOfHeaders;
            if((*it)->IsExpanded())
            {
                numberOfSubSectionCells += (*it)->GetTotalItemCount();
            }
        }
        else
        {
            numberOfHeaders += (*it)->GetTotalItemCount();
        }
    }
    
    return CellConstants::SectionHeaderCellHeight * numberOfHeaders + CellConstants::SubSectionCellHeight * numberOfSubSectionCells;
}

- (void)dealloc
{
    [self.pOpenableMenuArrow release];
    [super dealloc];
}

- (id)initWithParams:(MenuView*)view
{
    m_pView = view;

    CustomTableView* tableView = m_pView.pTableView;
    [tableView setDataSource:self];
    [tableView setDelegate:self];

    self.pOpenableMenuArrow = ExampleApp::Helpers::ImageHelpers::LoadImage(@"sub_menu_arrow");
    return self;
}

- (UITableViewCell *)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    const ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);
    const NSInteger index = section.IsExpandable() ? indexPath.row - 1 : indexPath.row;
    const bool isExpandableHeader = section.IsExpandable() && indexPath.row == 0;
    const bool isHeader = isExpandableHeader | !section.IsExpandable();
    
    NSString *CurrentCellIdentifier = isHeader ? HeaderCellIdentifier : SubSectionCellIdentifier;
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CurrentCellIdentifier];
    if(cell == nil)
    {
        cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CurrentCellIdentifier] autorelease];
        
        [(CustomTableViewCell*)cell initCell:(CGFloat)[m_pView.pTableView getCellWidth]
                                            :(CGFloat)[m_pView.pTableView getCellInset]
                                            :isHeader ? 0.0 : 4.0
                                            : 6.0
                                            :(CustomTableView*)tableView];
        
        cell.selectionStyle = UITableViewCellSelectionStyleGray;

        UIImageView* pOpenableMenuArrowView = [[[UIImageView alloc] initWithImage:self.pOpenableMenuArrow] autorelease];
        pOpenableMenuArrowView.tag = SubItemCellOpenableMenuArrowTag;

        const float tableWidth = static_cast<float>(m_pView.pTableView.bounds.size.width);
        const float openableArrowX = (tableWidth - 30.f);
        pOpenableMenuArrowView.frame = CGRectMake(openableArrowX,
                                                  (CellConstants::SectionHeaderCellHeight*0.5f) - 8.f,
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
    
    std::string json = isExpandableHeader ? section.SerializeJson() : section.GetItemAtIndex(static_cast<int>(index)).SerializeJson();
    [self populateCellWithJson:json :cell :isHeader];

    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(self.rowSelectionDelegate != NULL)
    {
        [self.rowSelectionDelegate onRowSelected];
    }
    
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
            if(self.rowSelectionDelegate != NULL)
            {
                [self.rowSelectionDelegate onSectionContracted];
            }
            
            [tableView deleteRowsAtIndexPaths:tmpArray withRowAnimation:UITableViewRowAnimationNone];
        }
        else
        {
            if(self.rowSelectionDelegate != NULL)
            {
                [self.rowSelectionDelegate onSectionExpanded];
            }
            
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
    
    bool isHeader = (section.IsExpandable() && indexPath.row == 0) || !section.IsExpandable();

    if(isHeader)
    {
        cell.textLabel.font = [UIFont systemFontOfSize:[self getTextLabelFontSize:true]];
        cell.textLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextHeaderColour;
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

        [self setCellInfo:customCell:true];
    }
    else
    {
        cell.textLabel.font = [UIFont systemFontOfSize:[self getTextLabelFontSize:false]];
        cell.textLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColour;
        [cell.textLabel sizeToFit];
        
        cell.detailTextLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColour;
        
        cell.indentationLevel = 0;
        
        openableArrow.hidden = true;
        [self setCellInfo:customCell:false];
    }
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(indexPath.section);
    
    if(section.IsExpandable() && indexPath.row != 0)
    {
        return CellConstants::SubSectionCellHeight;
    }
    else
    {
        return CellConstants::SectionHeaderCellHeight;
    }
}

- (void) populateCellWithJson:(std::string)json :(UITableViewCell*)cell :(bool)isHeader
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
        
        for (UIView* subview in cell.contentView.subviews)
        {
            [subview removeFromSuperview];
        }
        
        const float subLabelWidth = 160.0f;
        const float subLabelHeight = isHeader ? CellConstants::SectionHeaderCellHeight : CellConstants::SubSectionCellHeight;
        const float subLabelInset = 16.0f;
        const float subLabelImageInset = 8.0f + subLabelHeight;
        const float subLabelX = static_cast<float>(cell.imageView.image != nil ? subLabelImageInset : subLabelInset);
        
        UILabel *subLabel = [[UILabel alloc] initWithFrame:CGRectMake(subLabelX, 0, subLabelWidth, subLabelHeight)];
        subLabel.backgroundColor = [UIColor clearColor];
        subLabel.textAlignment = NSTextAlignmentLeft;
        subLabel.text = [NSString stringWithUTF8String:name.c_str()];
        subLabel.textColor = isHeader ? ExampleApp::Helpers::ColorPalette::UiTextHeaderColour : ExampleApp::Helpers::ColorPalette::UiTextCopyColour;
        subLabel.highlightedTextColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        subLabel.font = [UIFont systemFontOfSize: [self getTextLabelFontSize:isHeader]];
        [cell.contentView addSubview: subLabel];
    }
}

- (float)getTextLabelFontSize :(bool)headline
{
    return headline ? 25.0 : 20.f;
}

- (void) setCellInfo:(CustomTableViewCell*)cell :(bool)isHeader
{
    [cell setInfo :isHeader
                  :ExampleApp::Helpers::ColorPalette::BorderHudColor
                  :isHeader ? ExampleApp::Helpers::ColorPalette::BorderHudColor : ExampleApp::Helpers::ColorPalette::MainHudColor
                  :isHeader ? ExampleApp::Helpers::ColorPalette::ButtonPressColor : ExampleApp::Helpers::ColorPalette::TableSubCellPressColor];
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
            
            [self showOpenableArrowClosed:[m_pView.pTableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:i]]];
            
            rows = m_currentSections[i]->Size();
            m_currentSections[i]->Contract();
            
            for(int j = 1; j < rows; ++j)
            {
                NSIndexPath *tmpIndexPath = [NSIndexPath indexPathForRow:j inSection:i];
                [tmpArray addObject:tmpIndexPath];
            }
            
            [m_pView.pTableView deleteRowsAtIndexPaths:tmpArray withRowAnimation:UITableViewRowAnimationNone];
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
    
    [UIView animateWithDuration:0.2f
                          delay:0.0f
                        options:UIViewAnimationCurveEaseInOut
                     animations:^{
                         openableArrow.transform = [self computeOpenableArrowTransform:angle];
                     }
                     completion:nil];
}

- (void)showOpenableArrowOpen:(UITableViewCell *)cell
{
    const float angle = 270.0f;
    UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];
    [UIView animateWithDuration:0.2f
                          delay:0.0f
                        options:UIViewAnimationCurveEaseInOut
                     animations:^{
                         openableArrow.transform = [self computeOpenableArrowTransform:angle];
                     }
                     completion:nil];
}
@end;
