using ExampleApp;
using ExampleAppWPF.Views.SearchMenu;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace ExampleAppWPF
{
    public class SearchMenuView : MenuView
    {
        private TextBox m_editText;
        private MenuListAdapter m_adapter;
        private Grid m_searchBox;
        
        private ListBox m_resultsList;
        private MenuListAdapter m_resultListAdapter;
        private Grid m_resultsSpinner;
        private TextBlock m_resultsCount;
        private Button m_resultsClearButton;
        private ScrollViewer m_menuOptionsView;
        private ScrollViewer m_resultsOptionsView;
        private FrameworkElement m_searchArrow;
        private FrameworkElement m_resultsSeparator;

        private Grid m_resultsCountContainer;

        private bool m_searchInFlight;
        private bool m_hasResults;
        private bool m_hasCategorySearch;

        private ControlClickHandler m_menuListClickHandler;
        private ControlClickHandler m_resultsListClickHandler;

        private Storyboard m_searchInputOpen;
        private Storyboard m_searchInputClose;

        private Storyboard m_searchInputTextOpen;
        private Storyboard m_searchInputTextClose;

        private Storyboard m_searchArrowOpen;
        private Storyboard m_searchArrowClosed;

        static SearchMenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SearchMenuView), new FrameworkPropertyMetadata(typeof(SearchMenuView)));
        }

        public SearchMenuView(IntPtr nativeCallerPointer) : base(nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);

            Loaded += MainWindow_Loaded;
            mainWindow.SizeChanged += PerformLayout;

            m_searchInFlight = false;
            m_hasResults = false;
            m_hasCategorySearch = false;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);

            m_menuViewContainer.SizeChanged += OnMenuContainerSizeChanged;
        }

        private new void PerformLayout(object sender, SizeChangedEventArgs e)
        {
            var screenWidth = m_mainWindow.MainGrid.ActualWidth;
            var totalWidth = m_mainContainer.ActualWidth + m_menuIcon.ActualWidth;

            m_onScreenPos = -(screenWidth / 2);
            m_offScreenPos = -(screenWidth / 2) - (totalWidth / 2);

            base.PerformLayout(sender, e);
        }


        private void OnMenuContainerSizeChanged(object sender, SizeChangedEventArgs e)
        {
            m_resultsOptionsView.MaxHeight = CalcResultOptionsViewMaxHeight();
            m_menuOptionsView.MaxHeight = CalcMenuOptionsViewMaxHeight();
        }

        private double CalcResultOptionsViewMaxHeight()
        {
            var menuViewHeight = m_menuViewContainer.ActualHeight;
            var searchBoxBackgroundDefaultHeight = m_backgroundRectangle.ActualHeight;
            var menuOptionsViewDefaultHeight = m_menuOptionsView.ActualHeight;
            var separatorHeight = m_resultsSeparator.ActualHeight;

            return Math.Max(0.0, menuViewHeight - searchBoxBackgroundDefaultHeight - menuOptionsViewDefaultHeight + 2 * separatorHeight);
        }

        private double CalcMenuOptionsViewMaxHeight()
        {
            var menuViewHeight = m_menuViewContainer.ActualHeight;
            var searchBoxBackgroundDefaultHeight = m_backgroundRectangle.ActualHeight;
            var separatorHeight = m_resultsSeparator.ActualHeight;

            return Math.Max(0.0, menuViewHeight - searchBoxBackgroundDefaultHeight + 2 * separatorHeight);
        }

        protected override Size ArrangeOverride(Size arrangeBounds)
        {
            m_resultsOptionsView.MaxHeight = CalcResultOptionsViewMaxHeight();
            m_menuOptionsView.MaxHeight = CalcMenuOptionsViewMaxHeight();
            return base.ArrangeOverride(arrangeBounds);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_menuOptionsView = (ScrollViewer)GetTemplateChild("MenuOptionsView");

            m_resultsOptionsView = (ScrollViewer)GetTemplateChild("ResultsMenuOptionsView");
            m_resultsOptionsView.TouchDown += OnResultsListTouchDown;
            m_resultsOptionsView.TouchUp += OnResultsListTouchUp;
            m_resultsOptionsView.ManipulationBoundaryFeedback += OnResultsListBoundaryFeedback;

            m_resultsSpinner = (Grid)GetTemplateChild("SearchResultsSpinner");
            m_resultsCount = (TextBlock)GetTemplateChild("SearchResultCount");
            m_resultsCountContainer = (Grid)GetTemplateChild("SearchResultCountContainer");
            m_menuViewContainer = (Grid)GetTemplateChild("SearchMenuViewContainer");
            m_backgroundRectangle = (Rectangle)GetTemplateChild("BackgroundRect");
            m_searchBox = (Grid)GetTemplateChild("SearchBox");
            m_searchArrow = (FrameworkElement)GetTemplateChild("SearchArrow");
            m_resultsSeparator = (FrameworkElement)GetTemplateChild("ResultsListSeparator");

            m_resultsClearButton = (Button)GetTemplateChild("SearchClear");
            m_resultsClearButton.Click += OnResultsClear;

            m_list = (ListBox)GetTemplateChild("SecondaryMenuItemList");
            m_menuListClickHandler = new ControlClickHandler(OnMenuListItemSelected, m_list);
            m_list.PreviewMouseWheel += OnMenuScrollWheel;

            m_resultsList = (ListBox)GetTemplateChild("SearchResultsList");
            m_resultsListClickHandler = new ControlClickHandler(OnResultsListItemsSelected, m_resultsList);
            m_resultsList.PreviewMouseWheel += OnResultsMenuScrollWheel;

            m_menuIcon = (Button)GetTemplateChild("SecondaryMenuDragTabView");
            m_menuIconGrid = (Grid)GetTemplateChild("SearchIconGrid");

            m_menuIcon.Click += OnIconClick;

            m_editText = (TextBox)GetTemplateChild("SearchInputBox");
            m_editText.KeyDown += OnKeyDown;
            m_editText.GotFocus += OnSearchBoxSelected;
            m_editText.LostFocus += OnSearchBoxUnSelected;
            m_editText.TextChanged += OnSearchBoxTextChanged;

            m_mainContainer = (Grid)GetTemplateChild("SerchMenuMainContainer");

            var itemShutterOpenStoryboard = ((Storyboard)Template.Resources["ItemShutterOpen"]).Clone();
            var itemShutterCloseStoryboard = ((Storyboard)Template.Resources["ItemShutterClose"]).Clone();

            var slideInItemStoryboard = ((Storyboard)Template.Resources["SlideInNewItems"]).Clone();
            var slideOutItemStoryboard = ((Storyboard)Template.Resources["SlideOutOldItems"]).Clone();

            m_openSearchIconAnim = ((Storyboard)Template.Resources["OpenSearchViewIcon"]).Clone();
            m_closeMenuIconAnim = ((Storyboard)Template.Resources["CloseSearchViewIcon"]).Clone();

            m_openSearchContainerAnim = ((Storyboard)Template.Resources["OpenSearchContainer"]).Clone();
            m_closeMenuContainerAnim = ((Storyboard)Template.Resources["CloseSearchContainer"]).Clone();

            m_openBackgroundRect = ((Storyboard)Template.Resources["OpenBackgroundRect"]).Clone();
            m_closeBackgroundRect = ((Storyboard)Template.Resources["CloseBackgroundRect"]).Clone();

            m_searchInputOpen = ((Storyboard)Template.Resources["OpenSearchInputBox"]).Clone();
            m_searchInputClose = ((Storyboard)Template.Resources["CloseSearchInputBox"]).Clone();

            m_searchInputTextOpen = ((Storyboard)Template.Resources["OpenSearchInputBoxText"]).Clone();
            m_searchInputTextClose = ((Storyboard)Template.Resources["CloseSearchInputBoxText"]).Clone();

            m_searchArrowOpen = ((Storyboard)Template.Resources["OpenSearchArrow"]).Clone();
            m_searchArrowClosed  = ((Storyboard)Template.Resources["CloseSearchArrow"]).Clone();

            m_adapter = new MenuListAdapter(false, m_list, slideInItemStoryboard, slideOutItemStoryboard, itemShutterOpenStoryboard, itemShutterCloseStoryboard, "SubMenuItemPanel");
            m_resultListAdapter = new MenuListAdapter(false, m_resultsList, slideInItemStoryboard, slideOutItemStoryboard, itemShutterOpenStoryboard, itemShutterCloseStoryboard, "SearchResultPanel");

            TouchMove += OnTouchMove;

        }

        private void OnResultsListBoundaryFeedback(object sender, ManipulationBoundaryFeedbackEventArgs e)
        {
            e.Handled = true;
        }

        private void OnResultsListTouchUp(object sender, TouchEventArgs e)
        {
            m_resultsOptionsView.ReleaseTouchCapture(e.TouchDevice);
        }

        private void OnResultsListTouchDown(object sender, TouchEventArgs e)
        {
            m_resultsOptionsView.CaptureTouch(e.TouchDevice);
        }

        private void OnTouchMove(object sender, TouchEventArgs e)
        {
            e.Handled = true;
        }

        private void OnSearchBoxTextChanged(object sender, TextChangedEventArgs e)
        {
            if (m_editText.Text?.Length > 0)
            {
                m_resultsClearButton.Visibility = Visibility.Visible;
                m_editText.Foreground = Colour.black;

            }
            else if(!m_hasResults)
            {
                m_resultsClearButton.Visibility = Visibility.Hidden;
                m_editText.Foreground = Colour.darkgrey;
            }
        }

        private void OnMenuScrollWheel(object sender, MouseWheelEventArgs e)
        {
            m_menuOptionsView.ScrollToVerticalOffset(m_menuOptionsView.VerticalOffset - e.Delta);
            e.Handled = true;
        }

        private void OnResultsMenuScrollWheel(object sender, MouseWheelEventArgs e)
        {
            m_resultsOptionsView.ScrollToVerticalOffset(m_resultsOptionsView.VerticalOffset - e.Delta);
            e.Handled = true;
        }

        private void OnMenuListItemSelected(object sender, MouseEventArgs e)
        {
            if (m_searchInFlight || IsAnimating() || m_adapter.IsAnimating())
            {
                (sender as ListBox).SelectedItem = null;
                return;
            }

            var item = m_list.SelectedItem as MenuListItem;
            if (item != null)
            {
                var sectionChildIndices = m_adapter.GetSectionAndChildIndicesFromSelection(m_list.SelectedIndex);

                if (item.IsExpandable)
                {
                    SearchMenuViewCLIMethods.OnSearchCleared(m_nativeCallerPointer);
                }

                MenuViewCLIMethods.SelectedItem(m_nativeCallerPointer, sectionChildIndices.Item1, sectionChildIndices.Item2);
            }
        }

        private void OnResultsListItemsSelected(object sender, MouseEventArgs e)
        {
            if (m_resultsList.SelectedItems?.Count > 0)
            {
                SearchMenuViewCLIMethods.HandleSearchItemSelected(m_nativeCallerPointer, m_resultsList.SelectedIndex);
            }
        }

        private void OnSearchBoxUnSelected(object sender, RoutedEventArgs e)
        {
            if(m_editText.Text.Replace(" ", null) == string.Empty)
            {
                m_editText.Text = string.Empty;
            }
        }

        private void OnSearchBoxSelected(object sender, RoutedEventArgs e)
        {
            if (m_hasCategorySearch)
            {
                m_editText.Text = string.Empty;
            }
        }

        private void ClearSearchResultsListBox()
        {
            m_resultListAdapter.CollapseAndClearAll();

            m_resultsCountContainer.Visibility = Visibility.Hidden;
            m_resultsClearButton.Visibility = Visibility.Hidden;
            m_searchArrow.Visibility = Visibility.Hidden;
            m_resultsSeparator.Visibility = Visibility.Collapsed;
        }

        private void OnResultsClear(object sender, RoutedEventArgs e)
        {
            ClearSearch();
        }

        private void ClearSearch()
        {
            m_hasResults = false;
            m_hasCategorySearch = false;

            if (m_resultsList.Items?.Count > 0)
            {
                SearchMenuViewCLIMethods.OnSearchCleared(m_nativeCallerPointer);
            }
            else
            {
                m_editText.Text = string.Empty;
            }

            ClearSearchResultsListBox();

            //m_editText.Text = m_defaultEditText;
            m_editText.Text = String.Empty;
            m_editText.Foreground = Colour.darkgrey;
        }

        private void OnIconClick(object sender, RoutedEventArgs e)
        {
            MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                string queryText = m_editText.Text;

                if (queryText.Length > 0)
                {
                    SearchMenuViewCLIMethods.PerformedSearchQuery(m_nativeCallerPointer, queryText);

                    m_resultsSpinner.Visibility = Visibility.Visible;
                    m_resultsClearButton.Visibility = Visibility.Hidden;

                    m_searchInFlight = true;
                }
            }
        }

        public void SetSearchSection(string category, string[] searchResults)
        {
            var groups = new List<string>(searchResults.Length);
            var groupsExpandable = new List<bool>(searchResults.Length);
            var groupToChildren = new Dictionary<string, List<string>>();

            var itemsSource = new List<SearchMenuListItem>();

            foreach (var str in searchResults)
            {
                var jObject = JObject.Parse(str);
                var item = new SearchMenuListItem();
                item.Name = jObject["name"] != null ? jObject["name"].Value<string>() : string.Empty;
                item.Details = jObject["details"] != null ? jObject["details"].Value<string>() : string.Empty;

                JToken iconStringToken;
                var iconCategoryName = jObject.TryGetValue("icon", out iconStringToken) ? iconStringToken.Value<string>() : "";
                item.Icon = SearchMenuResultIconProvider.GetIconForCategory(iconCategoryName);
                itemsSource.Add(item);

                groups.Add(str);
                groupsExpandable.Add(false);

                if (!groupToChildren.ContainsKey(str))
                {
                    groupToChildren.Add(str, new List<string>());
                }
            }


            m_resultListAdapter.SetData(itemsSource, groups, groupsExpandable, groupToChildren);

            m_resultsSpinner.Visibility = Visibility.Hidden;
            m_resultsClearButton.Visibility = Visibility.Visible;
            m_searchArrow.Visibility = Visibility.Visible;
            m_resultsSeparator.Visibility = Visibility.Visible;

            m_searchInFlight = false;
        }

        public override void AnimateToClosedOnScreen()
        {
            if (m_openState != MENU_CLOSED && m_openState != MENU_CLOSING)
            {
                if(m_isOffScreen)
                {
                    m_searchBox.Visibility = Visibility.Hidden;

                    if (m_searchArrow.Visibility == Visibility.Visible)
                    {
                        m_searchArrowClosed.Begin(m_searchArrow); 
                    }
                }
                else
                {
                    m_searchBox.Visibility = Visibility.Visible;

                    m_searchInputClose.Begin(m_searchBox);
                    m_searchInputTextClose.Begin(m_editText);
                    m_searchArrowClosed.Begin(m_searchArrow);
                }

                base.AnimateToClosedOnScreen();
                m_mainWindow.EnableInput();
            }
        }

        public override void AnimateToOpenOnScreen()
        {
            if (m_openState != MENU_OPEN && m_openState != MENU_OPENING)
            {
                m_searchBox.Visibility = Visibility.Visible;

                m_searchInputOpen.Begin(m_searchBox);
                m_searchInputTextOpen.Begin(m_editText);
                m_searchArrowOpen.Begin(m_searchArrow);

                base.AnimateToOpenOnScreen();
                m_mainWindow.EnableInput(); 
            }
        }

        public void SetSearchInProgress()
        {
            Dispatcher.Invoke(() =>
            {
                m_resultsSpinner.Visibility = Visibility.Visible;
            });
        }
        public void SetSearchEnded()
        {
            Dispatcher.Invoke(() =>
            {
                m_resultsSpinner.Visibility = Visibility.Hidden;
            });
        }

        public void SetEditText(string text, bool isCategory)
        {
            if(!m_editText.IsFocused)
            {
                m_editText.Text = text;
            }
            m_hasCategorySearch = isCategory;
            
        }
        
        public void SetSearchResultCount(int count)
        {
            if(count > 0)
            {
                m_resultsCount.Text = count.ToString();
                m_resultsCountContainer.Visibility = Visibility.Visible;
            }
            else
            {
                m_resultsCountContainer.Visibility = Visibility.Hidden;
                m_resultsSpinner.Visibility = Visibility.Hidden;
                ClearSearchResultsListBox();
            }

            m_searchInFlight = false;
            m_hasResults = count > 0;
        }

        protected override void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap)
        {
            m_adapter.SetData(m_list.ItemsSource, groups, groupsExpandable, groupToChildrenMap);
        }
    }
}
