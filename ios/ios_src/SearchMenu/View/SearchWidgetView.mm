// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetView.h"
#include "WidgetSearchResultTableViewCell.h"

#include "SwallowSectionOption.h"
#include "SwallowSectionChild.h"
namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetView::SearchWidgetView(SearchMenuView* view,
                                               id<WRLDSearchProvider> searchProvider,
                                               id<WRLDSuggestionProvider> suggestionProvider):
            m_pView(view)
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
                };
                
                [[m_pSearchWidgetViewController searchSelectionObserver] addResultSelectedEvent:onResultSelection];
                
                CGRect searchFrame = ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) ?
                CGRectMake(20, 20, 375, CGRectGetHeight(m_pView.bounds) - 40) :   // ipad
                CGRectMake(10, 10, CGRectGetWidth(m_pView.bounds) - 20, CGRectGetHeight(m_pView.bounds) - 20); // iphone
                
                m_pSearchWidgetViewController.view.frame = searchFrame;
                
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
            
            void SearchWidgetView::UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged)
            {
                if (!contentsChanged)
                {
                    return;
                }
                const size_t numSections = sections.size();
                [m_pMenuModel removeAllGroups];
                bool first = true;
                const int numGroups = 4;
                int groupSizes[numGroups] = {5, 2, 1, 2};
                for (int sectionIndex = 0, g = 0; g < numGroups; g++)
                {
                    WRLDMenuGroup* group = [[WRLDMenuGroup alloc] init];
                    [m_pMenuModel addMenuGroup:group];
                    
                    if (first)
                    {
                        first = false;
                        AddMenuOption(group, @"Show me the closest...", sectionIndex);
                    }
                    while (--groupSizes[g] >= 0)
                    {
                        if (sectionIndex >= numSections)
                        {
                            return;
                        }
                        AddMenuSectionToGroup(group, *sections[sectionIndex], sectionIndex);
                        sectionIndex++;
                    }
                }
            }
            
            void SearchWidgetView::SetFullyOnScreenOpen()
            {
            }
            
            void SearchWidgetView::SetFullyOnScreenClosed()
            {
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
            }
            
            void SearchWidgetView::SetFullyOnScreen()
            {
                
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
            
            void SearchWidgetView::SetFullyOffScreen()
            {
            }
            
            void SearchWidgetView::CloseMenu()
            {
            }
        }
    }
}
