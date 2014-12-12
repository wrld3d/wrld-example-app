// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <sstream>
#include "IMenuModel.h"
#include "IMenuViewModel.h"
#include "MenuViewController.h"
#include "MenuView.h"
#include "IModalityModel.h"
#include "IMenuSectionViewModel.h"
#include "ImageHelpers.h"
#include "document.h"
#include "IconResources.h"
#include "UIColors.h"
#include "CustomTableViewCell.h"
#include "MenuSectionViewModel.h"
#include "CellConstants.h"

#import <QuartzCore/QuartzCore.h>

@interface MenuViewController()<UIGestureRecognizerDelegate>
{
	UIPanGestureRecognizer* _panGestureRecognizer;
	UITapGestureRecognizer* _tapGestureRecogniser;
	bool _dragging;
}
@end

@implementation MenuViewController

NSInteger const SubItemCellShadowViewTag = 1;
NSInteger const SubItemCellShadowFlippedViewTag = 2;
NSInteger const SubItemCellOpenableMenuArrowTag = 3;

- (id)initWithParams:(ExampleApp::Menu::IMenuModel *)pMenuModel
    :(ExampleApp::Menu::IMenuViewModel *)pMenuViewModel
    :(MenuView*)pMenuView
    :(ExampleApp::Modality::IModalityModel*)pModalityModel
    :(bool)isRightMenu

{
	if(self = [super init])
	{
		m_isRightMenu = isRightMenu;
		self.pMenuView = pMenuView;
		[self.pMenuView setController:self];
        
        m_pMenuModel = pMenuModel;
        
        m_pMenuViewModel = pMenuViewModel;
        m_pModalityModel = pModalityModel;

		size_t numberOfSections = pMenuViewModel->SectionsCount();
        size_t numberOfCells = [self getTotalNumberOfCellsInTableView];

		[self.pMenuView initialiseViews:numberOfSections numberOfCells: numberOfCells];

		[self.pMenuView setFrame:[self view].frame];
		self.view = pMenuView;

		_dragging = false;

		m_pInterop = Eegeo_NEW((ExampleApp::MenuView::MenuViewControllerInterop<ExampleApp::Menu::MenuItemModel, MenuViewController>))(self, *pMenuModel, *pMenuViewModel);

		_panGestureRecognizer = [[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(dragTabGesture:)] autorelease];
		[_panGestureRecognizer setDelegate:self];

		_tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapTabGesture:)] autorelease];
		[_tapGestureRecogniser setDelegate:self];

		[[self.pMenuView pTableview] setDataSource:self];
		[[self.pMenuView pTableview] setDelegate:self];
		[[self.pMenuView pDragTab] addGestureRecognizer: _panGestureRecognizer];
		[[self.pMenuView pDragTab] addGestureRecognizer: _tapGestureRecogniser];

		if(m_pMenuViewModel->IsFullyOnScreen())
		{
			[self.pMenuView setOpenStateToIntermediateValue:m_pMenuViewModel->OpenState()];
		}
		if ([self.pMenuView.pTableview respondsToSelector:@selector(layoutMargins)])
		{
			self.pMenuView.pTableview.layoutMargins = UIEdgeInsetsZero;
		}

		if ([self.pMenuView.pTableview respondsToSelector:@selector(separatorInset)])
		{
			[self.pMenuView.pTableview setSeparatorInset:UIEdgeInsetsZero];
		}

		self.pSubItemShadow = [UIImage imageNamed:@"shadow_01"];
		self.pSubItemShadowFlipped = [UIImage imageNamed:@"shadow_01_flip"];
		self.pOpenableMenuArrow = [UIImage imageNamed:@"arrow2"];
	}

	return self;
}

- (void)dealloc
{
	Eegeo_DELETE m_pInterop;
	[self.pSubItemShadow release];
	[self.pSubItemShadowFlipped release];
	[self.pOpenableMenuArrow release];
	[self.pMenuView release];
	[super dealloc];
}

-(void)update:(float)deltaSeconds
{
	if([self.pMenuView isAnimating])
	{
		[self.pMenuView updateAnimation:deltaSeconds];

		if(m_pMenuViewModel->HasReactorControl())
		{
			const float normalisedAnimationProgress = [self.pMenuView animationValue];
			m_pMenuViewModel->UpdateOpenState(normalisedAnimationProgress);
		}
	}

	if(m_pMenuViewModel->IsFullyOpen())
	{
		[[self.pMenuView pTableview] setUserInteractionEnabled:YES];
	}
	else
	{
		[[self.pMenuView pTableview] setUserInteractionEnabled:NO];
	}
}

-(void)handleItemAdded
{
    size_t numberOfSections = m_pMenuViewModel->SectionsCount();
    size_t numberOfCells = [self getTotalNumberOfCellsInTableView];
    
    [self.pMenuView refreshTableHeights: numberOfSections numberOfCells:numberOfCells];
    
	[[self.pMenuView pTableview] reloadData];
}

-(void)handleItemRemoved
{
    size_t numberOfSections = m_pMenuViewModel->SectionsCount();
    size_t numberOfCells = [self getTotalNumberOfCellsInTableView];
    
    [self.pMenuView refreshTableHeights: numberOfSections numberOfCells:numberOfCells];
    
	[[self.pMenuView pTableview] reloadData];
}

- (void) handleScreenStateChanged:(float)onScreenState
{
	if(m_pMenuViewModel->IsFullyOffScreen() && !_dragging)
	{
		[self.pMenuView animateToRemovedFromScreen];
	}
	else if(m_pMenuViewModel->IsFullyOnScreen() && !_dragging)
	{
		[self.pMenuView animateToClosedOnScreen];
	}
	else
	{
		[self.pMenuView setOnScreenStateToIntermediateValue:onScreenState];
	}
}

- (void) handleOpenStateChanged:(float)openState
{
	if(m_pMenuViewModel->IsFullyClosed() && !_dragging)
	{
		[self.pMenuView animateToClosedOnScreen];
	}
	else if(m_pMenuViewModel->IsFullyOpen() && !_dragging)
	{
		[self.pMenuView animateToOpenOnScreen];
	}
	else
	{
		[self.pMenuView setOpenStateToIntermediateValue:openState];
	}
}

- (void) handleViewOpenCompleted
{
	if(!m_pMenuViewModel->IsFullyOpen())
	{
		m_pMenuViewModel->Open();
	}

	if(m_pMenuViewModel->HasReactorControl())
	{
		m_pMenuViewModel->ReleaseReactorControl();
	}
}

- (void) handleViewCloseCompleted
{
	if(!m_pMenuViewModel->IsFullyClosed())
	{
		m_pMenuViewModel->Close();
	}

	if(m_pMenuViewModel->HasReactorControl())
	{
		m_pMenuViewModel->ReleaseReactorControl();
	}
}

- (void) handleDraggingViewInProgress:(float)normalisedDragState
{
	m_pMenuViewModel->UpdateOpenState(normalisedDragState);
}

- (void)dragTabGesture:(UIPanGestureRecognizer *)recognizer
{
	if(!m_pMenuViewModel->TryAcquireReactorControl())
	{
		return;
	}

	CGPoint positionAbs = [recognizer locationInView:[self.pMenuView superview]];
	CGPoint velocity = [recognizer velocityInView:[self.pMenuView superview]];

	switch(recognizer.state)
	{
	case UIGestureRecognizerStateBegan:
		_dragging = true;
		[self.pMenuView beginDrag:positionAbs velocity:velocity];
		break;

	case UIGestureRecognizerStateChanged:
		[self.pMenuView updateDrag:positionAbs velocity:velocity];
		break;

	case UIGestureRecognizerStateEnded:
		_dragging = false;
		[self.pMenuView completeDrag:positionAbs velocity:velocity];
		break;

	case UIGestureRecognizerStateCancelled:
		_dragging = false;
		[self.pMenuView completeDrag:positionAbs velocity:velocity];
		break;

	default:
		break;
	}
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    if([self.pMenuView isAnimating])
    {
        return NO;
    }
    
	return !m_pModalityModel->IsModalEnabled() || m_pMenuViewModel->IsFullyOpen();
}

- (void)tapTabGesture:(UITapGestureRecognizer *)recognizer
{
	if(!m_pMenuViewModel->TryAcquireReactorControl())
	{
		return;
	}

	if(m_pMenuViewModel->IsFullyClosed())
	{
		[self.pMenuView animateToOpenOnScreen];
	}
	else if(m_pMenuViewModel->IsFullyOpen())
	{
		[self.pMenuView animateToClosedOnScreen];
	}
	else
	{
		m_pMenuViewModel->ReleaseReactorControl();
	}
}

- (size_t)getTotalNumberOfCellsInTableView
{
    size_t numberOfCells = 0;
    
    for (int i = 0; i < m_pMenuViewModel->SectionsCount(); ++i)
    {
        ExampleApp::Menu::IMenuSectionViewModel& menuSectionViewModel = m_pMenuViewModel->GetMenuSection(i);
        numberOfCells += menuSectionViewModel.GetTotalItemCount();
    }
    
    return numberOfCells;
}

- (NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
	return m_pMenuViewModel->SectionsCount();
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	return m_pMenuViewModel->GetMenuSection(section).Size();
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
        
        if (m_isRightMenu)
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

- (UITableViewCell *)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    std::stringstream ss;
    
    ExampleApp::Menu::IMenuSectionViewModel& section = m_pMenuViewModel->GetMenuSection(indexPath.section);
    const NSInteger index = section.IsExpandable() ? indexPath.row - 1 : indexPath.row;
    const bool isExpandableHeader = section.IsExpandable() && indexPath.row == 0;
    const bool isLastExpandableSection = section.IsExpandable() && indexPath.section == m_pMenuViewModel->SectionsCount() - 1;
    const bool flippedShadowIsVisible = !isLastExpandableSection;
    
    static NSString *CellIdentifier = @"cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if(cell == nil)
    {
        cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
        [(CustomTableViewCell*)cell initCell: self.pMenuView.pTableview.bounds.size.width :tableView];
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
        
        UIImageView* pShadowView = [[[UIImageView alloc] initWithImage:self.pSubItemShadow] autorelease];
        pShadowView.autoresizingMask = m_isRightMenu ? UIViewAutoresizingFlexibleRightMargin : UIViewAutoresizingFlexibleLeftMargin;
        pShadowView.tag = SubItemCellShadowViewTag;
        pShadowView.frame = CGRectMake(0, 0, cell.bounds.size.width, 32);
        [cell addSubview:pShadowView];
        
        UIImageView* pShadowFlippedView = [[[UIImageView alloc] initWithImage:self.pSubItemShadowFlipped] autorelease];
        pShadowFlippedView.tag = SubItemCellShadowFlippedViewTag;
        pShadowFlippedView.frame = CGRectMake(0, 0, cell.bounds.size.width, 32);
        pShadowFlippedView.autoresizingMask = m_isRightMenu ? UIViewAutoresizingFlexibleRightMargin : UIViewAutoresizingFlexibleLeftMargin;
        [cell addSubview:pShadowFlippedView];
        
        UIImageView* pOpenableMenuArrowView = [[[UIImageView alloc] initWithImage:self.pOpenableMenuArrow] autorelease];
        pOpenableMenuArrowView.tag = SubItemCellOpenableMenuArrowTag;
        
        const float tableWidth = self.pMenuView.pTableview.bounds.size.width;
        const float openableArrowX = m_isRightMenu ? (tableWidth - 20.f) : 0.f;
        pOpenableMenuArrowView.frame = CGRectMake(openableArrowX, (SECTION_HEADER_CELL_HEIGHT*0.5f) - 8.f, 16.f, 16.f);
        [cell addSubview:pOpenableMenuArrowView];
        
        if ([cell respondsToSelector:@selector(layoutMargins)]) {
            cell.layoutMargins = UIEdgeInsetsZero;
        }
        
        if ([cell respondsToSelector:@selector(separatorInset)]) {
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
        ExampleApp::Menu::MenuItemModel item = section.GetItemAtIndex(index);
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
    
    if(_dragging)
    {
        return;
    }

	ExampleApp::Menu::IMenuSectionViewModel& section = m_pMenuViewModel->GetMenuSection(indexPath.section);

	if(section.IsExpandable() && indexPath.row == 0)
	{
		// only first row toggles expand/collapse.
		NSInteger rows;

		NSMutableArray *tmpArray = [NSMutableArray array];

		if(section.IsExpanded())
		{
			rows = section.Size();
			m_pMenuViewModel->GetMenuSection(indexPath.section).Contract();
			[self showOpenableArrowClosed:cell];
		}
		else
		{
			m_pMenuViewModel->GetMenuSection(indexPath.section).Expand();
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
		NSInteger index = section.IsExpandable() ? indexPath.row - 1 : indexPath.row;
		ExampleApp::Menu::MenuItemModel item = section.GetItemAtIndex(index);
		item.Select();
	}
}

- (float)getTextLabelFontSize:(bool)headline
{
	return headline ? 25.0 : 20.f;
}


- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
	ExampleApp::Menu::IMenuSectionViewModel& section = m_pMenuViewModel->GetMenuSection(indexPath.section);
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
        
		if(section.IsExpanded() && section.Size() > 1)
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

- (void) setCellAlignInfo:(CustomTableViewCell*)cell :(bool)isHeader
{
	[cell setAlignInfo :m_isRightMenu :!m_isRightMenu :isHeader];
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
	const float angle = m_isRightMenu ? 180.f : 0.f;
	UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];
	openableArrow.transform = [self computeOpenableArrowTransform:angle];
}

- (void)showOpenableArrowOpen:(UITableViewCell *)cell
{
	UIImageView *openableArrow = (UIImageView*)[cell viewWithTag:SubItemCellOpenableMenuArrowTag];
	openableArrow.transform = [self computeOpenableArrowTransform:90.f];
}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	ExampleApp::Menu::IMenuSectionViewModel& section = m_pMenuViewModel->GetMenuSection(indexPath.section);

	if(section.IsExpandable() && indexPath.row != 0)
	{
		return SUB_SECTION_CELL_HEIGHT;
	}
	else
	{
		return SECTION_HEADER_CELL_HEIGHT;
	}
}

@end


