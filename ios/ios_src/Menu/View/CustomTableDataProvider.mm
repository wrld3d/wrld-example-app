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

static const float HeaderCellFontSize = 22.0f;
static const float SubSectionCellFontSize = 16.0f;

static NSString *HeaderCellIdentifier = @"headercell";
static NSString *SubSectionCellIdentifier = @"subsectioncell";

@interface CustomTableDataProvider()
{
    std::map<CustomTableView*, size_t> m_tableSectionMap;
    std::vector<size_t> m_cachedTableSizes;
}

@end

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
            if((*sections)[i] != m_currentSections[i] || (*sections)[i]->GetTotalItemCount() != m_cachedTableSizes[i])
            {
                sectionsUpdated = true;
                break;
            }
        }
    }
    
    if(sectionsUpdated)
    {
        m_currentSections = *sections;
        
        m_cachedTableSizes.resize(m_currentSections.size());
        
        for(int i = 0; i < m_cachedTableSizes.size(); ++i)
        {
            m_cachedTableSizes[i] = m_currentSections[i]->GetTotalItemCount();
        }
        
        for(std::map<CustomTableView*, size_t>::const_iterator it = m_tableSectionMap.begin(); it != m_tableSectionMap.end(); ++it)
        {
            [it->first reloadData];
        }
        
        [m_pView refreshTableHeights];
    }
}

- (float)getRealHeightForTable:(CustomTableView*)customTableView
{
    int numberOfHeaders = 0;
    int numberOfSubSectionCells = 0;
    
    const ExampleApp::Menu::View::IMenuSectionViewModel& section = *(m_currentSections[m_tableSectionMap[customTableView]]);
    
    if(section.IsExpandable())
    {
        ++numberOfHeaders;
        if(section.IsExpanded())
        {
            numberOfSubSectionCells += section.GetTotalItemCount();
        }
    }
    else
    {
        numberOfHeaders += section.GetTotalItemCount();
    }

    return ((CellConstants::SectionHeaderCellHeight * numberOfHeaders + CellConstants::SubSectionCellHeight * numberOfSubSectionCells));
}

- (void)dealloc
{
    [self.pOpenableMenuArrow release];
    [super dealloc];
}

- (id)initWithParams:(MenuView*)view
                    :(NSMutableDictionary*)tableViewMap
{
    m_pView = view;
    
    for(int i = 0; i < [tableViewMap count]; ++i)
    {
        CustomTableView* tableView = tableViewMap[@(i)];
        
        [tableView setDataSource:self];
        [tableView setDelegate:self];
        
        m_tableSectionMap[tableView] = i;
    }

    self.pOpenableMenuArrow = ExampleApp::Helpers::ImageHelpers::LoadImage(@"sub_menu_arrow_off");
    return self;
}

- (UITableViewCell *)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    CustomTableView* customTableView = static_cast<CustomTableView*>(tableView);
    
    const ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(m_tableSectionMap[customTableView]);
    const NSInteger index = section.IsExpandable() ? indexPath.row - 1 : indexPath.row;
    const bool isExpandableHeader = section.IsExpandable() && indexPath.row == 0;
    const bool isHeader = isExpandableHeader | !section.IsExpandable();
    
    NSString *CurrentCellIdentifier = isHeader ? HeaderCellIdentifier : SubSectionCellIdentifier;
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CurrentCellIdentifier];
    if(cell == nil)
    {
        cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CurrentCellIdentifier] autorelease];
        
        [(CustomTableViewCell*)cell initCell:(CGFloat)[customTableView getCellWidth]
                                            :(CGFloat)[customTableView getCellInset]
                                            :indexPath
                                            :customTableView
                                            :self];
        
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
        
        UIImageView* pOpenableMenuArrowView = [[[UIImageView alloc] initWithImage:self.pOpenableMenuArrow] autorelease];
        pOpenableMenuArrowView.tag = SubItemCellOpenableMenuArrowTag;
        
        const float openableArrowWidth = pOpenableMenuArrowView.frame.size.width;
        const float openableArrowHeight = pOpenableMenuArrowView.frame.size.height;
        
        const float openableArrowRightInset = 18.0f + openableArrowWidth / 2.0f;
        const float openableArrowTopInset = (CellConstants::SectionHeaderCellHeight - openableArrowHeight) * 0.5f;
        
        const float openableArrowX = [customTableView getCellWidth] - openableArrowRightInset;
        const float openableArrowY = openableArrowTopInset;
        
        pOpenableMenuArrowView.frame = CGRectMake(openableArrowX,
                                                  openableArrowY,
                                                  pOpenableMenuArrowView.frame.size.width,
                                                  pOpenableMenuArrowView.frame.size.height);
        
        [cell.contentView addSubview:pOpenableMenuArrowView];

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
    [self populateCellWithJson:json :cell :customTableView :isHeader];

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
    
    size_t sectionIndex = m_tableSectionMap[(CustomTableView*)tableView];

    ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(sectionIndex);

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
            // Commented following code line out to fix arrow animation. Fixes MPLY-6376.
            // (first animation call fails at start and sets final value for animation)
            // relying on animation in willDisplayCell that is called right after and will succeed
            //[self showOpenableArrowOpen:cell];
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
            
            for(std::map<CustomTableView*, size_t>::const_iterator it = m_tableSectionMap.begin(); it != m_tableSectionMap.end(); ++it)
            {
                if(it->first != tableView)
                {
                    [self collapseSectionForTable:it->first];
                }
            }
        }
    }
    else
    {
        ExampleApp::Menu::View::MenuViewInterop* interop = [m_pView getInterop];
        interop->HandleItemSelected(static_cast<int>(sectionIndex), static_cast<int>(indexPath.row));
    }
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    CustomTableViewCell* customCell = (CustomTableViewCell*)cell;
    
    if(![customCell requiresVisualRefresh])
    {
        return;
    }
    
    size_t sectionIndex = m_tableSectionMap[(CustomTableView*)tableView];
    ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections.at(sectionIndex);
    
    UIImageView *openableArrow = (UIImageView*)[cell.contentView viewWithTag:SubItemCellOpenableMenuArrowTag];
    
    cell.indentationLevel = 0;
    
    bool isExpandableHeader = section.IsExpandable() && indexPath.row == 0;
    bool isHeader = isExpandableHeader || !section.IsExpandable();
    bool hasSeparator = isHeader && sectionIndex != 0;
    
    openableArrow.hidden = !isExpandableHeader;
    [self setCellInfo:customCell :isHeader :hasSeparator];
    
    if(isExpandableHeader)
    {
        if(section.IsExpanded())
        {
            [self showOpenableArrowOpen :cell];
        }
        else
        {
            [self showOpenableArrowClosed :cell];
        }
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

- (void) populateCellWithJson:(std::string)json :(UITableViewCell*)cell :(CustomTableView*)tableView :(bool)isHeader
{
    rapidjson::Document document;
    if (!document.Parse<0>(json.c_str()).HasParseError())
    {
        std::string name = document["name"].GetString();
        
        CGRect imageFrame = CGRectZero;
        
        float textInsetX;
        
        const float textHeight = isHeader ? CellConstants::SectionHeaderCellHeight : CellConstants::SubSectionCellHeight;
        
        if(document.HasMember("icon") && !isHeader)
        {
            const float imageSize = 36.0f;
            const float imageInsetX = 4.0f;
            const float imageInsetY = (textHeight*0.5f) - (imageSize*0.5f);
            
            textInsetX = imageSize + imageInsetX * 2.0f;
            
            std::string icon = document["icon"].GetString();
            std::string iconResourceName = ExampleApp::Helpers::IconResources::GetSmallIconPathForResourceName(icon);
            
            cell.imageView.image = ExampleApp::Helpers::ImageHelpers::LoadImage(iconResourceName);
            cell.imageView.contentMode = UIViewContentModeScaleToFill;
            
            imageFrame = CGRectMake(imageInsetX,
                                    imageInsetY,
                                    imageSize,
                                    imageSize);
        }
        else
        {
            textInsetX = 9.0f;
            cell.imageView.image = nil;
        }
        
        const bool hasDetails = document.HasMember("details");
        const float textY = hasDetails ? 4.0f : 0.f;
        const float textWidth = [tableView getCellWidth] - textInsetX;
        
        cell.textLabel.text = [NSString stringWithUTF8String:name.c_str()];
        cell.textLabel.font = [UIFont systemFontOfSize: [self getTextLabelFontSize:isHeader]];
        cell.textLabel.textColor = isHeader ? ExampleApp::Helpers::ColorPalette::TableHeaderTextColor : ExampleApp::Helpers::ColorPalette::TableSubCellTextColor;
        [cell.textLabel sizeToFit];
        
        const float titleTextHeight = hasDetails ? cell.textLabel.frame.size.height : textHeight;
        
        CGRect textFrame = CGRectMake(textInsetX,
                                      textY,
                                      textWidth,
                                      titleTextHeight);
        
        CGRect detailTextFrame = CGRectZero;
        
        std::string details = "";
        if (hasDetails)
        {
            details = document["details"].GetString();
            cell.detailTextLabel.text = [NSString stringWithUTF8String:details.c_str()];
            cell.detailTextLabel.font = [UIFont systemFontOfSize:11.0f];
            cell.detailTextLabel.textColor = ExampleApp::Helpers::ColorPalette::TableSearchDetailTextColor;
            [cell.detailTextLabel sizeToFit];
            
            const float detailTextY = 24.0f;
            detailTextFrame = CGRectMake(textInsetX,
                                         detailTextY,
                                         textWidth,
                                         cell.detailTextLabel.frame.size.height);
            
            
        }

        [(CustomTableViewCell*)cell setHasDetails: hasDetails];
        [(CustomTableViewCell*)cell setContentFrames:imageFrame
                                                    :textFrame
                                                    :detailTextFrame];
    }
}

- (float)getTextLabelFontSize :(bool)headline
{
    return headline ? HeaderCellFontSize : SubSectionCellFontSize;
}

- (void) setCellInfo:(CustomTableViewCell*)cell :(bool)isHeader :(bool)hasSeparator
{
    UIColor* titleTextColor = isHeader ? ExampleApp::Helpers::ColorPalette::TableHeaderTextColor : ExampleApp::Helpers::ColorPalette::TableSubCellTextColor;
    titleTextColor = [cell hasDetails] ? ExampleApp::Helpers::ColorPalette::TableSearchTextColor: titleTextColor;
    
    [cell setInfo :hasSeparator
                  :ExampleApp::Helpers::ColorPalette::UiBorderColor
                  :isHeader ? ExampleApp::Helpers::ColorPalette::UiBorderColor : ExampleApp::Helpers::ColorPalette::TableSubCellColor
                  :isHeader ? ExampleApp::Helpers::ColorPalette::TableHeaderPressColor : ExampleApp::Helpers::ColorPalette::TableSubCellPressColor
                  :titleTextColor
                  :isHeader ? ExampleApp::Helpers::ColorPalette::TableHeaderTextHighlightColor : ExampleApp::Helpers::ColorPalette::TableSubCellTextColor
                  :(UIImageView*)[cell.contentView viewWithTag:SubItemCellOpenableMenuArrowTag]];
}


- (NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    if(m_tableSectionMap.find((CustomTableView*)tableView) == m_tableSectionMap.end() || m_currentSections.size() == 0)
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
    return m_currentSections.at(m_tableSectionMap[(CustomTableView*)tableView])->Size();
}

- (void)collapseAll
{
    for(std::map<CustomTableView*, size_t>::const_iterator it = m_tableSectionMap.begin(); it != m_tableSectionMap.end(); ++it)
    {
        [self collapseSectionForTable:it->first];
    }
}

- (void)collapseSectionForTable:(CustomTableView*)tableView
{
    size_t sectionIndex = m_tableSectionMap[tableView];
    
    if (sectionIndex < m_currentSections.size())
    {
        ExampleApp::Menu::View::IMenuSectionViewModel& section = *m_currentSections[sectionIndex];
        
        if(section.IsExpandable() && section.IsExpanded())
        {
            NSInteger rows;
            
            NSMutableArray *tmpArray = [NSMutableArray array];
            
            [self showOpenableArrowClosed:[tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0]]];
            
            rows = section.Size();
            section.Contract();
            
            for(int i = 1; i < rows; ++i)
            {
                NSIndexPath *tmpIndexPath = [NSIndexPath indexPathForRow:i inSection:0];
                [tmpArray addObject:tmpIndexPath];
            }
            
            [tableView deleteRowsAtIndexPaths:tmpArray withRowAnimation:UITableViewRowAnimationNone];
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
    UIImageView *openableArrow = (UIImageView*)[cell.contentView viewWithTag:SubItemCellOpenableMenuArrowTag];
    
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
    UIImageView *openableArrow = (UIImageView*)[cell.contentView viewWithTag:SubItemCellOpenableMenuArrowTag];
    [UIView animateWithDuration:0.2f
                          delay:0.0f
                        options:UIViewAnimationCurveEaseInOut
                     animations:^{
                         openableArrow.transform = [self computeOpenableArrowTransform:angle];
                     }
                     completion:nil];
}
@end;
