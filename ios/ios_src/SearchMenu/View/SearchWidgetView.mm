// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetView.h"
#include "WidgetSearchResultTableViewCell.h"
#include "IMenuView.h"
#include "SearchMenuView.h"
#include "SearchWidgetMenuContext.h"
#include "WidgetQueryContext.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetView::SearchWidgetView(id<WRLDSearchProvider> searchProvider,
                                               id<WRLDSuggestionProvider> suggestionProvider,
                                               ExampleAppMessaging::TMessageBus& messageBus)
            : m_tagCollection(messageBus)
            , m_menuIsOpen(false)
            , m_searchResultsAreVisible(true)
            , m_searchTextboxIsInFocus(false)
            , m_hasSearchResults(false)
            , m_searchInProgress(false)
            , m_hasPopulatedData(false)
            {
                m_pSearchModel = [[WRLDSearchModel alloc] init];
                m_pMenuModel = [[WRLDSearchMenuModel alloc] init];
                m_pSearchProviderHandle = [m_pSearchModel addSearchProvider: searchProvider];
                m_pSuggestionProviderHandle = [m_pSearchModel addSuggestionProvider: suggestionProvider];

                m_pSearchWidgetViewController = [[WRLDSearchWidgetViewController alloc] initWithSearchModel:m_pSearchModel menuModel: m_pMenuModel];

                [m_pSearchWidgetViewController displaySearchProvider: m_pSearchProviderHandle];
                [m_pSearchWidgetViewController displaySuggestionProvider: m_pSuggestionProviderHandle];

                m_onResultSelection = ^(id<WRLDSearchResultModel> selectedResultModel)
                {
                    WidgetSearchResultModel* selectedResultModelWithIndex = (WidgetSearchResultModel*) selectedResultModel;
                    if (selectedResultModelWithIndex != nil)
                    {
                        this->OnSearchResultSelected((int)selectedResultModelWithIndex.index);
                    }

                    [m_pSearchWidgetViewController resignFocus];
                };

                [[m_pSearchWidgetViewController searchSelectionObserver] addResultSelectedEvent:m_onResultSelection];

                CGRect screenRect = [[UIScreen mainScreen] bounds];
                CGFloat screenWidth = screenRect.size.width;
                CGFloat iphoneMargin = 10;
                CGFloat iPadMargin = 20;
                CGFloat iPadWidgetWidth = 375;
                CGFloat heightIphone = screenRect.size.height - 2*iphoneMargin;
                CGFloat heightIpad = screenRect.size.height - 2*iPadMargin;

                m_widgetAnimationOffset = -100;

                CGRect searchFrame = ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) ?
                CGRectMake(iPadMargin, iPadMargin,  iPadWidgetWidth , heightIpad) :   // ipad
                CGRectMake(iphoneMargin, iphoneMargin, screenWidth - 2*iphoneMargin, heightIphone); // iphone

                UIView *widget = m_pSearchWidgetViewController.view;

                widget.frame = searchFrame;

                CGAffineTransform transform = CGAffineTransformMakeTranslation(0.0,m_widgetAnimationOffset);
                widget.transform = transform;

                NSBundle* resourceBundle = [NSBundle bundleForClass:[WidgetSearchResultTableViewCell class]];
                UINib* nib = [UINib nibWithNibName: @"WidgetSearchResultTableViewCell" bundle:resourceBundle];

                [m_pSearchWidgetViewController registerNib:nib forUseWithResultsTableCellIdentifier:@"WidgetSearchResultTableViewCell"];

                m_onMenuSelection = ^(NSObject* selectedOptionContext)
                {
                    SearchWidgetMenuContext* widgetMenuContext = (SearchWidgetMenuContext*) selectedOptionContext;
                    if (widgetMenuContext != nil)
                    {
                        const std::string menuText = [widgetMenuContext.menuText cStringUsingEncoding: NSUTF8StringEncoding];
                        int sectionIndex = (int) widgetMenuContext.sectionIndex;
                        int itemIndex = (int) widgetMenuContext.itemIndex;

                        this->HandleItemSelected(menuText, sectionIndex, itemIndex);

                        if (m_tagCollection.HasTag(menuText))
                        {
                            [m_pSearchWidgetViewController closeMenu];
                            [m_pSearchWidgetViewController showResultsView];
                        }
                    }
                };


                
                m_menuGroups = [[NSMutableDictionary alloc] init];
                m_menuOptions = [[NSMutableDictionary alloc] init];


                [[m_pSearchWidgetViewController menuObserver] addOptionSelectedEvent:m_onMenuSelection];

                m_onQueryCancelled = ^(WRLDSearchQuery *query)
                {
                    m_searchClearedCallbacks.ExecuteCallbacks();
                };

                [[m_pSearchModel searchObserver] addQueryCancelledEvent:m_onQueryCancelled];

            }

            SearchWidgetView::~SearchWidgetView()
            {

                [m_menuOptions release];
                [m_menuGroups release];
                [m_pMenuModel release];
                [m_pSearchModel release];

                [[m_pSearchModel searchObserver] removeQueryCancelledEvent:m_onQueryCancelled];
                [[m_pSearchWidgetViewController menuObserver] removeOptionSelectedEvent:m_onMenuSelection];
                [[m_pSearchWidgetViewController searchSelectionObserver] removeResultSelectedEvent:m_onResultSelection];
            }

            UIViewController* SearchWidgetView::GetWidgetController() const
            {
                return (UIViewController*)m_pSearchWidgetViewController;
            }

            UIView* SearchWidgetView::GetWidgetView() const
            {
                return (UIView*)m_pSearchWidgetViewController.view;
            }

            void SearchWidgetView::OnSearchResultSelected(int index)
            {
                m_resultSelectedCallbacks.ExecuteCallbacks(index);
            }

            void SearchWidgetView::UpdateMenuSectionViews(Menu::View::TSections& sections)
            {
                if(m_hasPopulatedData != true){
                    PopulateMenuData(sections);
                    m_hasPopulatedData = true;
                    return;
                }
                UpdateDiscoverGroup(sections);
                
                const size_t numSections = sections.size();
                
                for (int sectionIndex = 0; sectionIndex < numSections; sectionIndex++)
                {
                    Menu::View::IMenuSectionViewModel& section = *sections[sectionIndex];
                    
                    NSString* nsName = [NSString stringWithUTF8String:section.Name().c_str()];
                    
                    WRLDMenuOption* option = m_menuOptions[nsName];
                    [option removeAllChildren];
                    
                    if (section.IsExpandable())
                    {
                        AddMenuChildren(option, section, sectionIndex);
                    }
                }
            }
            
            void SearchWidgetView::UpdateDiscoverGroup(Menu::View::TSections& sections){
                NSString *groupName = @"Discover";
                WRLDMenuGroup *group = m_menuGroups[groupName];
                
                BOOL shouldShowDiscover = false;
                
                const size_t numSections = sections.size();
                
                for (int sectionIndex = 0; sectionIndex < numSections; sectionIndex++)
                {
                    if (sectionIndex == 0 || sections[sectionIndex]->IsGroupStart())
                    {
                        Menu::View::IMenuSectionViewModel& section = *sections[sectionIndex];
                        NSString* optionName = [NSString stringWithUTF8String:section.Name().c_str()];
                        if([optionName isEqualToString:groupName]){
                            WRLDMenuOption *option = m_menuOptions[optionName];
                            //TODO: when widget is updated so that it's possible, check if group has options rather than removing option.
                            [group removeOption:option];
                            [group addOption:option];
                            shouldShowDiscover = true;
                        }
                    }
                }
                
                if(shouldShowDiscover != true){
                    [group removeAllOptions];
                }
                
            }
            
            void SearchWidgetView::PopulateMenuData(Menu::View::TSections& sections){
                const size_t numSections = sections.size();
                
                WRLDMenuGroup* group = NULL;
                
                for (int sectionIndex = 0; sectionIndex < numSections; sectionIndex++)
                {
                    if (sectionIndex == 0 || sections[sectionIndex]->IsGroupStart())
                    {
                        group = [[WRLDMenuGroup alloc] init];
                        
                        [m_pMenuModel addMenuGroup:group];
                        
                        Menu::View::IMenuSectionViewModel& section = *sections[sectionIndex];
                       NSString* nsName = [NSString stringWithUTF8String:section.Name().c_str()];
                        
                       [m_menuGroups setObject:group forKey:nsName];
                    }
                    
                    AddMenuSectionToGroup(group, *sections[sectionIndex], sectionIndex);
                }
                
            }
            
            void SearchWidgetView::PerformSearch(const std::string& query, const QueryContext& context)
            {
                NSString* queryString = [NSString stringWithUTF8String:query.c_str()];

                WidgetQueryContext* widgetQueryContext = [[WidgetQueryContext alloc] init];

                widgetQueryContext.clearPreviousResults = (BOOL) context.ClearPreviousResults();
                widgetQueryContext.isTag = (BOOL) context.IsTag();
                widgetQueryContext.shouldTryInterior = (BOOL) context.ShouldTryInterior();
                widgetQueryContext.shouldZoomToBuildingsView = (BOOL) context.ShouldZoomToBuildingsView();
                widgetQueryContext.usesLocation = (BOOL) context.UsesLocation();
                widgetQueryContext.usesRadius = (BOOL) context.UsesRadius();

                widgetQueryContext.tagText = [NSString stringWithUTF8String:context.TagText().c_str()];

                widgetQueryContext.latitude = (CGFloat) context.Location().GetLatitude();
                widgetQueryContext.longtitude = (CGFloat) context.Location().GetLongitude();
                widgetQueryContext.altitude = (CGFloat) context.Location().GetAltitude();
                widgetQueryContext.radius = (CGFloat) context.Radius();

                [m_pSearchModel getSearchResultsForString:queryString withContext:widgetQueryContext];
            }

            void SearchWidgetView::AddMenuSectionToGroup(WRLDMenuGroup* group,
                                                         const Menu::View::IMenuSectionViewModel& section,
                                                         int sectionIndex)
            {
                NSString* nsName = [NSString stringWithUTF8String:section.Name().c_str()];

                WRLDMenuOption* option = AddMenuOption(group, nsName, sectionIndex);
                if (section.IsExpandable())
                {
                    AddMenuChildren(option, section, sectionIndex);
                }
            }

            void SearchWidgetView::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_resultSelectedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_resultSelectedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::HandleItemSelected(const std::string& menuText, int sectionIndex, int itemIndex)
            {
                m_onItemSelectedCallbacks.ExecuteCallbacks(menuText, sectionIndex, itemIndex);
            }

            void SearchWidgetView::InsertOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback)
            {
                m_onItemSelectedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback)
            {
                m_onItemSelectedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::pushControlsOfScreenIfNeeded(){

              bool hasVisibleSearchResults = m_searchResultsAreVisible && (m_hasSearchResults || m_searchInProgress);

               bool shouldTakeFocus = m_searchTextboxIsInFocus ||hasVisibleSearchResults || m_menuIsOpen;

                if( shouldTakeFocus )
                {
                    HandleViewOpenCompleted();
                }
                else
                {
                    HandleViewCloseCompleted();
                }
            }

            void SearchWidgetView::HandleViewOpenCompleted()
            {
                m_onViewOpenedCallbacks.ExecuteCallbacks();
            }

            void SearchWidgetView::HandleViewCloseCompleted()
            {
                m_onViewClosedCallbacks.ExecuteCallbacks();
            }

            void SearchWidgetView::InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClosedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClosedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pSearchWidgetViewController hideResultsView];
                [m_pSearchWidgetViewController closeMenu];
                UIView *widget = (UIView*)m_pSearchWidgetViewController.view;
               
                
                CGAffineTransform transform = CGAffineTransformMakeTranslation(0.0,m_widgetAnimationOffset*value);

                [UIView animateWithDuration:0.3 animations:^{
                    widget.transform = transform;
                }];
            }

            void SearchWidgetView::SetFullyOnScreen()
            {
                UIView *widget = (UIView*)m_pSearchWidgetViewController.view;
                
                [UIView animateWithDuration:0.3 animations:^{
                    widget.transform = CGAffineTransformIdentity;
                }];
            }

            void SearchWidgetView::SetFullyOffScreen()
            {
                [m_pSearchWidgetViewController hideResultsView];
                [m_pSearchWidgetViewController closeMenu];
                UIView *widget = (UIView*)m_pSearchWidgetViewController.view;
                
                CGAffineTransform transform = CGAffineTransformMakeTranslation(0.0,m_widgetAnimationOffset);

                [UIView animateWithDuration:0.3 animations:^{
                    widget.transform = transform;
                }];
            }

            WRLDMenuOption* SearchWidgetView::AddMenuOption(WRLDMenuGroup* group,
                                                            NSString* nsName,
                                                            int sectionIndex)
            {
                SearchWidgetMenuContext* widgetMenuContext = [[SearchWidgetMenuContext alloc] init];

                widgetMenuContext.menuText = nsName;
                widgetMenuContext.sectionIndex = (NSInteger) sectionIndex;
                widgetMenuContext.itemIndex = 0;

                WRLDMenuOption* menuOption = [[WRLDMenuOption alloc] initWithText:nsName
                                                                          context:widgetMenuContext];

                [group addOption:menuOption];
                [m_menuOptions setObject:menuOption forKey:nsName];

                return menuOption;
            }

            void SearchWidgetView::AddMenuChildren(WRLDMenuOption* option,
                                                   const Menu::View::IMenuSectionViewModel& section,
                                                   int sectionIndex)
            {
                for (int childIndex = 0; childIndex < section.GetTotalItemCount(); childIndex++)
                {
                    const Menu::View::MenuItemModel& sectionChild = section.GetItemAtIndex(childIndex);

                    NSString* nsChildName = [NSString stringWithUTF8String:sectionChild.Name().c_str()];

                    std::string fullIconName = "icon1_" + sectionChild.Icon();
                    NSString* nsChildIcon = [NSString stringWithUTF8String:fullIconName.c_str()];

                    SearchWidgetMenuContext* widgetMenuParentContext = (SearchWidgetMenuContext*) option.context;
                    if (widgetMenuParentContext != nil)
                    {
                        SearchWidgetMenuContext* widgetMenuChildContex = [[SearchWidgetMenuContext alloc] init];

                        widgetMenuChildContex.menuText = nsChildName;
                        widgetMenuChildContex.sectionIndex = widgetMenuParentContext.sectionIndex;
                        widgetMenuChildContex.itemIndex = (NSInteger) childIndex;

                        WRLDMenuChild* child = [[WRLDMenuChild alloc] initWithText:nsChildName
                                                                              icon:nsChildIcon
                                                                           context:widgetMenuChildContex];

                        [option addChild:child];
                    }
                }
            }

            void SearchWidgetView::CloseMenu()
            {
                [m_pSearchWidgetViewController hideResultsView];
                [m_pSearchWidgetViewController closeMenu];
            }
        }
    }
}
