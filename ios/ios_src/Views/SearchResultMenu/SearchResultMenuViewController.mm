// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <sstream>
#include "IMenuModel.h"
#include "IMenuViewModel.h"
#include "SearchResultMenuViewController.h"
#include "MenuView.h"
#include "IModalityModel.h"
#include "IMenuSectionViewModel.h"
#include "ISearchResultRepository.h"
#include "ISearchService.h"
#include "SearchResultMenuViewControllerInterop.h"
#include "document.h"
#include "SearchResultMenuView.h"
#include "ISearchQueryPerformer.h"
#include "IconResources.h"
#include "ISearchResultMenuViewModel.h"
#include "CustomTableViewCell.h"
#include "UIColors.h"
#include "SearchResultViewClearedMessage.h"

@interface SearchResultMenuViewController()<UIGestureRecognizerDelegate>
{
	UITapGestureRecognizer* _closedViewTapHandler;
	ExampleApp::SearchResultMenu::SearchResultMenuViewControllerInterop* m_pControllerInterop;
	SearchResultMenuView* m_pSearchResultMenuView;
}
@end

@implementation SearchResultMenuViewController

CGFloat const SearchResultRowHeight = 53.0f;

- (id)initWithParams:(ExampleApp::CategorySearch::ICategorySearchRepository*) pCategorySearchRepository
    :(ExampleApp::Menu::IMenuModel *)pMenuModel
    :(ExampleApp::Menu::IMenuViewModel *)pMenuViewModel
    :(ExampleApp::SearchResultMenu::ISearchResultMenuViewModel *)pSearchResultMenuViewModel
    :(SearchResultMenuView*)pMenuView
    :(ExampleApp::Modality::IModalityModel*)pModalityModel
    :(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*)pUiToNativeMessageBus
    :(ExampleApp::ExampleAppMessaging::NativeToUiMessageBus*)pNativeToUiMessageBus

{
	if(self = [super initWithParams:pMenuModel:pMenuViewModel:pMenuView:pModalityModel:false])
	{
		m_pSearchResultMenuViewModel = pSearchResultMenuViewModel;
		m_pSearchResultMenuView = pMenuView;
		m_pCategorySearchRepository = pCategorySearchRepository;
		m_pUiToNativeMessageBus = pUiToNativeMessageBus;
		m_pControllerInterop = Eegeo_NEW(ExampleApp::SearchResultMenu::SearchResultMenuViewControllerInterop)(self,

		                       *m_pCategorySearchRepository,
		                       *pNativeToUiMessageBus);

		_closedViewTapHandler = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_closedViewTapHandler:)] autorelease];
		[_closedViewTapHandler setDelegate:self];
		[[m_pSearchResultMenuView pClearResults] addGestureRecognizer: _closedViewTapHandler];
	}

	return self;
}

- (void)dealloc
{
	Eegeo_DELETE m_pControllerInterop;
	[super dealloc];
}

- (void)updateHeaderInResponseToQueryIssued:(std::string)query
{
	[m_pSearchResultMenuView updateViewForQuery:query :YES: 0];
}

- (void)updateHeaderInResponseToQueryResultsReceived:(std::string)query :(size_t)resultsReceived
{
	[m_pSearchResultMenuView updateViewForQuery:query :NO: resultsReceived];
}

- (void)_closedViewTapHandler:(UITapGestureRecognizer *)recognizer
{
	m_pUiToNativeMessageBus->Publish(ExampleApp::SearchResultMenu::SearchResultViewClearedMessage());
	m_pMenuViewModel->RemoveFromScreen();
}

- (void)dragTabGesture:(UIPanGestureRecognizer *)recognizer
{
	if(m_pSearchResultMenuViewModel->CanInteract())
	{
		[super dragTabGesture: recognizer];
	}
}

- (void)tapTabGesture:(UITapGestureRecognizer *)recognizer
{
	if(m_pSearchResultMenuViewModel->CanInteract())
	{
		[super tapTabGesture: recognizer];
	}
}

- (void) setCellAlignInfo:(CustomTableViewCell*)cell :(bool)isHeader
{
	[cell setAlignInfo :m_isRightMenu :false :isHeader];
}

- (UITableViewCell *)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	// TODO: This is mostly identical to MenuViewController - Will clean this bit up when we finalize the
	// view for Search Results Menu in ios.

	std::stringstream ss;

	static NSString *CellIdentifier = @"cell";

	CustomTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	if(cell == nil)
	{
		cell = [[[CustomTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
		cell.selectionStyle = UITableViewCellSelectionStyleGray;
		[cell initCell: static_cast<float>(self.pMenuView.pTableview.bounds.size.width) :tableView];
	}

	ExampleApp::Menu::IMenuSectionViewModel& section = m_pMenuViewModel->GetMenuSection(static_cast<int>(indexPath.section));
	int index = static_cast<int>(section.IsExpandable() ? indexPath.row - 1 : indexPath.row);

	if(section.IsExpandable() && indexPath.row == 0)
	{
		ss << section.Name();
		cell.textLabel.text = [NSString stringWithUTF8String:ss.str().c_str()];
		ss.clear();
	}
	else
	{
		ExampleApp::Menu::MenuItemModel item = section.GetItemAtIndex(index);

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


