using ExampleApp;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Threading.Tasks;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace ExampleAppWPF
{
    public class SearchMenuView : MenuView, INotifyPropertyChanged
    {
        private TextBox m_editText;
        private MenuListAdapter m_adapter;
        private Grid m_searchBox;

        private ListBox m_resultsList;
        private ScrollViewer m_resultsListScrollViewer;
        private MenuListAdapter m_resultListAdapter;
        private Grid m_resultsSpinner;
        private TextBlock m_resultsCount;
        private Button m_resultsClearButton;
        private ScrollViewer m_menuOptionsView;
        private FrameworkElement m_searchArrow;
        private FrameworkElement m_resultsSeparator;
        private RepeatButton m_searchResultsScrollButton;
        private Image m_searchResultsFade;
        private Grid m_searchResultsButtonAndFadeContainer;

        private Grid m_resultsCountContainer;

        private bool m_searchInFlight;
        private bool m_hasResults;
        private bool m_hasTagSearch;

        private double m_scrollSpeed;

        private ControlClickHandler m_menuListClickHandler;
        private ControlClickHandler m_resultsListClickHandler;

        private Storyboard m_searchInputOpen;
        private Storyboard m_searchInputClose;

        private Storyboard m_searchInputTextOpen;
        private Storyboard m_searchInputTextClose;

        private Storyboard m_searchArrowOpen;
        private Storyboard m_searchArrowClosed;

        private WindowInteractionTouchHandler m_touchHandler;

        private TouchDevice m_searchResultsListCurrentTouchDevice;

        private bool m_editingText;

        public event PropertyChangedEventHandler PropertyChanged;

        private ImageSource m_searchIconOffImageSource;
        private ImageSource m_searchIconOnImageSource;
        private ImageSource m_closeIconOffImageSource;
        private ImageSource m_closeIconOnImageSource;
        private ImageSource m_iconOffImageSource;
        private ImageSource m_iconOnImageSource;

        public ImageSource SearchMenuIconOffImageSource
        {
            get
            {
                return m_iconOffImageSource;
            }
            set
            {
                m_iconOffImageSource = value;
                OnPropertyChanged("SearchMenuIconOffImageSource");
            }
        }

        public ImageSource SearchMenuIconOnImageSource
        {
            get
            {
                return m_iconOnImageSource;
            }
            set
            {
                m_iconOnImageSource = value;
                OnPropertyChanged("SearchMenuIconOnImageSource");
            }
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        static SearchMenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SearchMenuView), new FrameworkPropertyMetadata(typeof(SearchMenuView)));
        }

        public SearchMenuView(IntPtr nativeCallerPointer, bool isInKioskMode) : base(nativeCallerPointer, isInKioskMode)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);

            Loaded += MainWindow_Loaded;
            mainWindow.SizeChanged += PerformLayout;

            m_searchInFlight = false;
            m_hasResults = false;
            m_hasTagSearch = false;
            m_touchHandler = new WindowInteractionTouchHandler(this, false, true, true);
            m_editingText = false;
        }

        public Button GetSearchButton()
        {
            return m_menuIcon;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);

            m_menuViewContainer.SizeChanged += OnMenuContainerSizeChanged;
            
            m_resultsListScrollViewer = (ScrollViewer) VisualTreeHelper.GetChild(VisualTreeHelper.GetChild(m_resultsList, 0), 0);
            m_resultsListScrollViewer.ScrollChanged += OnSearchResultsScrolled;
            m_resultsListScrollViewer.ManipulationBoundaryFeedback += OnResultsListBoundaryFeedback;
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
            m_resultsList.MaxHeight = CalcResultOptionsViewMaxHeight();
            m_menuOptionsView.MaxHeight = CalcMenuOptionsViewMaxHeight();
        }

        private double CalcResultOptionsViewMaxHeight()
        {
            var menuViewHeight = m_menuViewContainer.ActualHeight;
            var searchBoxBackgroundDefaultHeight = m_backgroundRectangle.ActualHeight;
            var menuOptionsViewDefaultHeight = m_menuOptionsView.ActualHeight;
            var separatorHeight = m_resultsSeparator.ActualHeight;
            var seperatorCount = 2;

            return Math.Max(0.0, menuViewHeight - searchBoxBackgroundDefaultHeight - menuOptionsViewDefaultHeight - seperatorCount * separatorHeight);
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
            m_resultsList.MaxHeight = CalcResultOptionsViewMaxHeight();
            m_menuOptionsView.MaxHeight = CalcMenuOptionsViewMaxHeight();
            return base.ArrangeOverride(arrangeBounds);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_menuOptionsView = (ScrollViewer)GetTemplateChild("MenuOptionsView");

            m_resultsSpinner = (Grid)GetTemplateChild("SearchResultsSpinner");
            m_resultsCount = (TextBlock)GetTemplateChild("SearchResultCount");
            m_resultsCountContainer = (Grid)GetTemplateChild("SearchResultCountContainer");
            m_menuViewContainer = (Grid)GetTemplateChild("SearchMenuViewContainer");
            m_backgroundRectangle = (Rectangle)GetTemplateChild("BackgroundRect");
            m_searchBox = (Grid)GetTemplateChild("SearchBox");
            m_searchArrow = (FrameworkElement)GetTemplateChild("SearchArrow");
            m_resultsSeparator = (FrameworkElement)GetTemplateChild("ResultsListSeparator");
            m_searchResultsFade = (Image)GetTemplateChild("SearchResultsFade");
            m_searchResultsButtonAndFadeContainer = (Grid)GetTemplateChild("SearchResultsButtonAndFadeContainer");

            m_searchResultsScrollButton = (RepeatButton)GetTemplateChild("SearchResultsScrollButton");
            m_searchResultsScrollButton.Click += OnResultsScrollButtonMouseDown;
            m_searchResultsScrollButton.PreviewMouseWheel += OnResultsMenuScrollWheel;
            m_searchResultsScrollButton.MouseUp += OnResultsScrollButtonMouseUp;
            m_searchResultsScrollButton.MouseLeave += OnResultsScrollButtonMouseLeave;

            m_resultsClearButton = (Button)GetTemplateChild("SearchClear");
            m_resultsClearButton.Click += OnResultsClear;

            m_list = (ListBox)GetTemplateChild("SecondaryMenuItemList");
            m_menuListClickHandler = new ControlClickHandler(OnMenuListItemSelected, m_list);
            m_list.PreviewMouseWheel += OnMenuScrollWheel;

            m_resultsList = (ListBox)GetTemplateChild("SearchResultsList");
            m_resultsList.TouchDown += new EventHandler<TouchEventArgs>(OnSearchResultsListTouchDown);
            m_resultsList.TouchUp += new EventHandler<TouchEventArgs>(OnSearchResultsListTouchUp);
            m_resultsList.TouchLeave += new EventHandler<TouchEventArgs>(OnSearchResultsListTouchLeave);
            m_resultsList.LostTouchCapture += new EventHandler<TouchEventArgs>(OnSearchResultsListLostTouchCapture);
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

            string searchAnimString = "SearchAnim";

            string openMenuViewIconString = "OpenSearchViewIcon";
            m_openMenuIconAnim = ((Storyboard)Template.Resources[openMenuViewIconString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_openMenuIconAnim, searchAnimString + openMenuViewIconString);
            string closeMenuViewIconString = "CloseSearchViewIcon";
            m_closeMenuIconAnim = ((Storyboard)Template.Resources[closeMenuViewIconString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_closeMenuIconAnim, searchAnimString + closeMenuViewIconString);

            string openMenuContainerString = "OpenSearchContainer";
            m_openMenuContainerAnim = ((Storyboard)Template.Resources[openMenuContainerString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_openMenuContainerAnim, searchAnimString + openMenuContainerString);
            string closeMenuContainerString = "CloseSearchContainer";
            m_closeMenuContainerAnim = ((Storyboard)Template.Resources[closeMenuContainerString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_closeMenuContainerAnim, searchAnimString + closeMenuContainerString);

            string openBackgroundRectString = "OpenBackgroundRect";
            m_openBackgroundRect = ((Storyboard)Template.Resources[openBackgroundRectString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_openBackgroundRect, searchAnimString + openBackgroundRectString);
            string closeBackgroundRectString = "CloseBackgroundRect";
            m_closeBackgroundRect = ((Storyboard)Template.Resources[closeBackgroundRectString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_closeBackgroundRect, searchAnimString + closeBackgroundRectString);

            string openSearchInputBoxString = "OpenSearchInputBox";
            m_searchInputOpen = ((Storyboard)Template.Resources[openSearchInputBoxString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_searchInputOpen, searchAnimString + openSearchInputBoxString);
            m_searchInputClose = ((Storyboard)Template.Resources["CloseSearchInputBox"]).Clone();

            m_searchInputTextOpen = ((Storyboard)Template.Resources["OpenSearchInputBoxText"]).Clone();
            m_searchInputTextClose = ((Storyboard)Template.Resources["CloseSearchInputBoxText"]).Clone();

            string openSearchArrowString = "OpenSearchArrow";
            m_searchArrowOpen = ((Storyboard)Template.Resources[openSearchArrowString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_searchArrowOpen, searchAnimString + openSearchArrowString);
            string closeSearchArrowString = "CloseSearchArrow";
            m_searchArrowClosed = ((Storyboard)Template.Resources[closeSearchArrowString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_searchArrowClosed, searchAnimString + closeSearchArrowString);

            m_adapter = new MenuListAdapter(false, m_list, slideInItemStoryboard, slideOutItemStoryboard, itemShutterOpenStoryboard, itemShutterCloseStoryboard, "SubMenuItemPanel", m_isInKioskMode);
            m_resultListAdapter = new MenuListAdapter(false, m_resultsList, slideInItemStoryboard, slideOutItemStoryboard, itemShutterOpenStoryboard, itemShutterCloseStoryboard, "SearchResultPanel", m_isInKioskMode);

            m_scrollSpeed = (double) Application.Current.Resources["ScrollViewButtonScrollSpeed"];

            m_searchIconOffImageSource = (ImageSource) Application.Current.Resources["ButtonSearchOffImage"];
            m_searchIconOnImageSource = (ImageSource) Application.Current.Resources["ButtonSearchOnImage"];
            m_closeIconOffImageSource = (ImageSource) Application.Current.Resources["ButtonSearchCloseOffImage"];
            m_closeIconOnImageSource = (ImageSource) Application.Current.Resources["ButtonSearchCloseOnImage"];
            SearchMenuIconOffImageSource = m_searchIconOffImageSource;
            SearchMenuIconOnImageSource = m_searchIconOnImageSource;
        }

        public void RemoveSearchQueryResults()
        {
            HideSearchResultCount();
            if (!m_editingText)
            {
                m_editText.Text = String.Empty;
            }
            m_hasTagSearch = false;
        }

        private void OnSearchResultsScrolled(object sender, RoutedEventArgs e)
        {
            if (m_resultsListScrollViewer.VerticalOffset == m_resultsListScrollViewer.ScrollableHeight)
            {
                m_searchResultsButtonAndFadeContainer.Visibility = Visibility.Collapsed;
                m_searchResultsFade.Visibility = Visibility.Hidden;
                m_searchResultsScrollButton.Visibility = Visibility.Hidden;
            }
            else
            {
                m_searchResultsButtonAndFadeContainer.Visibility = Visibility.Visible;
                m_searchResultsFade.Visibility = Visibility.Visible;
                m_searchResultsScrollButton.Visibility = Visibility.Visible;
            }

            m_resultsList.Items.Refresh();
        }

        private void OnResultsScrollButtonMouseDown(object sender, RoutedEventArgs e)
        {
            m_resultsListScrollViewer.IsEnabled = false;
            m_resultsListScrollViewer.ScrollToVerticalOffset(m_resultsListScrollViewer.VerticalOffset + m_scrollSpeed);
        }

        private void OnResultsScrollButtonMouseUp(object sender, RoutedEventArgs e)
        {
            m_resultsListScrollViewer.IsEnabled = true;
        }

        private void OnResultsScrollButtonMouseLeave(object sender, RoutedEventArgs e)
        {
            m_resultsListScrollViewer.IsEnabled = true;
        }

        private void OnResultsListBoundaryFeedback(object sender, ManipulationBoundaryFeedbackEventArgs e)
        {
            e.Handled = true;

            m_resultsList.Items.Refresh();
        }

        private void OnSearchBoxTextChanged(object sender, TextChangedEventArgs e)
        {
            if (m_editText.Text?.Length > 0)
            {
                m_resultsClearButton.Visibility = Visibility.Visible;
                m_editText.Foreground = Colour.black;
                m_editingText = true;

            }
            else if(!m_hasResults)
            {
                m_resultsClearButton.Visibility = Visibility.Hidden;
                m_editText.Foreground = Colour.darkgrey;
            }

            ShowCloseButtonView(m_editText.Text.Length == 0);

            m_hasTagSearch = false;
        }

        private void OnMenuScrollWheel(object sender, MouseWheelEventArgs e)
        {
            m_menuOptionsView.ScrollToVerticalOffset(m_menuOptionsView.VerticalOffset - e.Delta);
            e.Handled = true;
        }

        private void OnResultsMenuScrollWheel(object sender, MouseWheelEventArgs e)
        {
            m_resultsListScrollViewer.ScrollToVerticalOffset(m_resultsListScrollViewer.VerticalOffset - e.Delta);
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

            m_resultsList.Items.Refresh();
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
            if (m_hasTagSearch)
            {
                m_editText.Text = string.Empty;
            }
        }

        private void OnSearchResultsListTouchDown(object sender, TouchEventArgs touchEventArgs)
        {
            m_resultsList.CaptureTouch(touchEventArgs.TouchDevice);

            if(m_searchResultsListCurrentTouchDevice == null)
            {
                CaptureSearchResultsListTouchDevice(touchEventArgs);
            }
            else
            {
                touchEventArgs.Handled = true;
            }
        }

        private void OnSearchResultsListTouchUp(object sender, TouchEventArgs touchEventArgs)
        {
            m_resultsList.ReleaseTouchCapture(touchEventArgs.TouchDevice);

            if (m_searchResultsListCurrentTouchDevice != null && m_searchResultsListCurrentTouchDevice.Id == touchEventArgs.TouchDevice.Id)
            {
                ReleaseSearchResultsListCurrentTouchDevice();
            }
        }

        private void OnSearchResultsListTouchLeave(object sender, TouchEventArgs touchEventArgs)
        {
            m_resultsList.ReleaseTouchCapture(touchEventArgs.TouchDevice);

            if (m_searchResultsListCurrentTouchDevice != null && m_searchResultsListCurrentTouchDevice.Id == touchEventArgs.TouchDevice.Id)
            {
                ReleaseSearchResultsListCurrentTouchDevice();
            }
        }

        private void OnSearchResultsListLostTouchCapture(object sender, TouchEventArgs touchEventArgs)
        {
            if (m_searchResultsListCurrentTouchDevice != null && m_searchResultsListCurrentTouchDevice.Id == touchEventArgs.TouchDevice.Id)
            {
                CaptureSearchResultsListTouchDevice(touchEventArgs);
            }
        }

        private void ReleaseSearchResultsListCurrentTouchDevice()
        {
            if (m_searchResultsListCurrentTouchDevice != null)
            {
                TouchDevice currentTouchDevice = m_searchResultsListCurrentTouchDevice;
                m_searchResultsListCurrentTouchDevice = null;
                m_resultsListScrollViewer.ReleaseTouchCapture(currentTouchDevice);

                if(m_resultsList.SelectedIndex < 0)
                {
                    m_resultsList.Items.Refresh();
                }
            }
        }

        private void CaptureSearchResultsListTouchDevice(TouchEventArgs touchEventArgs)
        {
            if (m_resultsListScrollViewer.CaptureTouch(touchEventArgs.TouchDevice))
            {
                m_searchResultsListCurrentTouchDevice = touchEventArgs.TouchDevice;
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
            m_hasTagSearch = false;

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
                Encoding enc = Encoding.GetEncoding("Windows-1252");
                byte[] bytes = Encoding.UTF8.GetBytes(m_editText.Text);
                string queryText = enc.GetString(bytes);

                if (queryText.Length > 0)
                {
                    SearchMenuViewCLIMethods.PerformedSearchQuery(m_nativeCallerPointer, queryText);

                    m_resultsSpinner.Visibility = Visibility.Visible;
                    m_resultsClearButton.Visibility = Visibility.Hidden;

                    m_searchInFlight = true;
                }
            }
        }

        public void SetSearchSection(string tag, string[] searchResults)
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
                var iconTagName = jObject.TryGetValue("icon", out iconStringToken) ? iconStringToken.Value<string>() : "";
                item.Icon = IconProvider.GetIconForTag(iconTagName, m_isInKioskMode);
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

            ShowCloseButtonView(false);
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

            ShowCloseButtonView(m_editText.Text.Length == 0);
        }

        public void SetSearchInProgress()
        {
            Dispatcher.Invoke(() =>
            {
                m_resultsSpinner.Visibility = Visibility.Visible;
                m_resultsClearButton.Visibility = Visibility.Hidden;
            });
            m_editingText = false;
        }
        public void SetSearchEnded()
        {
            Dispatcher.Invoke(() =>
            {
                m_resultsSpinner.Visibility = Visibility.Hidden;
                m_resultsClearButton.Visibility = Visibility.Visible;
            });
        }

        public void SetEditText(string text, bool isTag)
        {
            if(!m_editText.IsFocused)
            {
                byte[] bytes = Encoding.Default.GetBytes(text);
                string encodedText = Encoding.UTF8.GetString(bytes);
                m_editText.Text = encodedText;
            }
            m_hasTagSearch = isTag;
        }

        public string GetEditText()
        {
            return m_editText.Text;
        }
        
        public void SetSearchResultCount(int count)
        {
            m_resultsCount.Text = count.ToString();
            m_resultsCountContainer.Visibility = Visibility.Visible;
            m_searchResultsFade.Visibility = Visibility.Visible;
            m_searchResultsScrollButton.Visibility = Visibility.Visible;
            m_resultsListScrollViewer.ScrollToTop();

            m_searchInFlight = false;
            m_hasResults = true;

            if (count == 0)
            {
                m_resultListAdapter.CollapseAndClearAll();
                m_searchArrow.Visibility = Visibility.Hidden;
                m_resultsSeparator.Visibility = Visibility.Collapsed;

                return;
            }
        }

        public void HideSearchResultCount()
        {
            m_searchResultsButtonAndFadeContainer.Visibility = Visibility.Collapsed;
            m_searchResultsFade.Visibility = Visibility.Hidden;
            m_searchResultsScrollButton.Visibility = Visibility.Hidden;
            m_resultsCountContainer.Visibility = Visibility.Hidden;
            m_resultsSpinner.Visibility = Visibility.Hidden;
            ClearSearchResultsListBox();

            m_searchInFlight = false;
            m_hasResults = false;
        }

        protected override void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap)
        {
            m_adapter.SetData(m_list.ItemsSource, groups, groupsExpandable, groupToChildrenMap);
            m_resultsList.MaxHeight = CalcResultOptionsViewMaxHeight();
        }

        private void ShowCloseButtonView(bool shouldShowCloseView)
        {
            if(shouldShowCloseView)
            {
                SearchMenuIconOffImageSource = m_closeIconOffImageSource;
                SearchMenuIconOnImageSource = m_closeIconOnImageSource;
            }
            else
            {
                SearchMenuIconOffImageSource = m_searchIconOffImageSource;
                SearchMenuIconOnImageSource = m_searchIconOnImageSource;
            }
        }

        public bool HasTagSearch()
        {
            return m_hasTagSearch;
        }
    }
}
