// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetView.h"
#include "WidgetSearchResultTableViewCell.h"
#include "IMenuView.h"
#include "SearchMenuView.h"
#include "SwallowSectionOption.h"
#include "SwallowSectionChild.h"
namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetView::SearchWidgetView(
                                               id<WRLDSearchProvider> searchProvider,
                                               id<WRLDSuggestionProvider> suggestionProvider):
            
            m_menuIsOpen(false)
            , m_searchResultsAreVisible(true)
            , m_searchTextboxIsInFocus(false)
            , m_hasSearchResults(false)
            , m_searchInProgress(false)
            {
                m_pSearchModel = [[WRLDSearchModel alloc] init];
                m_pMenuModel = [[WRLDSearchMenuModel alloc] init];
                m_pSearchProviderHandle = [m_pSearchModel addSearchProvider: searchProvider];
                m_pSuggestionProviderHandle = [m_pSearchModel addSuggestionProvider: suggestionProvider];
                
                m_pSearchWidgetViewController = [[WRLDSearchWidgetViewController alloc] initWithSearchModel:m_pSearchModel menuModel: m_pMenuModel];
                
                [m_pSearchWidgetViewController displaySearchProvider: m_pSearchProviderHandle];
                [m_pSearchWidgetViewController displaySuggestionProvider: m_pSuggestionProviderHandle];
                
                void (^onResultSelection) (id<WRLDSearchResultModel>) = ^(id<WRLDSearchResultModel> selectedResultModel)
                {
                    WidgetSearchResultModel* selectedResultModelWithIndex = (WidgetSearchResultModel*) selectedResultModel;
                    if (selectedResultModelWithIndex != nil)
                    {
                        this->OnSearchResultSelected((int)selectedResultModelWithIndex.index);
                    }
                    
                    [m_pSearchWidgetViewController resignFocus];
                };
                
                [[m_pSearchWidgetViewController searchSelectionObserver] addResultSelectedEvent:onResultSelection];
                
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
            }
            
            SearchWidgetView::~SearchWidgetView()
            {
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
                const size_t numSections = sections.size();
                [m_pMenuModel removeAllGroups];
                
                WRLDMenuGroup* group = NULL;
                
                for (int sectionIndex = 0; sectionIndex < numSections; sectionIndex++)
                {
                    if (sectionIndex == 0 || sections[sectionIndex]->IsGroupStart())
                    {
                        group = [[WRLDMenuGroup alloc] init];
                        
                        [m_pMenuModel addMenuGroup:group];
                    }
                    
                    AddMenuSectionToGroup(group, *sections[sectionIndex], sectionIndex);
                }
            }
            
            void SearchWidgetView::PerformSearch(const std::string& query, const QueryContext& context)
            {
            }
            
            void SearchWidgetView::AddMenuSectionToGroup(WRLDMenuGroup* group,
                                                         const Menu::View::IMenuSectionViewModel& section,
                                                         int sectionIndex)
            {
                NSString* nsName = [NSString stringWithCString:section.Name().c_str()
                                                      encoding:[NSString defaultCStringEncoding]];
                
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
                WRLDMenuOption* option = [[SwallowSectionOption alloc] initWithText:nsName section:sectionIndex];
                
                [group addOption:option];
                
                return option;
            }
            
            void SearchWidgetView::AddMenuChildren(WRLDMenuOption* option,
                                                   const Menu::View::IMenuSectionViewModel& section,
                                                   int sectionIndex)
            {
                for (int childIndex = 0; childIndex < section.GetTotalItemCount(); childIndex++)
                {
                    const Menu::View::MenuItemModel& sectionChild = section.GetItemAtIndex(childIndex);
                    
                    NSString* nsChildName = [NSString stringWithCString:sectionChild.Name().c_str()
                                                               encoding:[NSString defaultCStringEncoding]];
                    NSString* nsChildIcon = [NSString stringWithCString:sectionChild.Icon().c_str()
                                                               encoding:[NSString defaultCStringEncoding]];
                    
                    WRLDMenuChild* child = [[SwallowSectionChild alloc] initWithText:nsChildName
                                                                                icon:nsChildIcon
                                                                             section:sectionIndex
                                                                               child:(childIndex + 1)];
                    
                    [option addChild:child];
                }
            }
            
           
            
            void SearchWidgetView::CloseMenu()
            {
                
            }
        }
    }
}
