using ExampleApp;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Threading;

namespace ExampleAppWPF
{
    public class SearchMenuView : MenuView
    {
        private double m_screenWidthPx;
        private double m_mainContainerOnScreenWidthPx;
        private TextBox m_editText;
        private MenuListAdapter m_adapter;
        private bool m_isFirstLayout = true;
        private Grid m_mainContainer;
        private Grid m_dragTabContainer;
        private static readonly ResourceDictionary genericResourceDictionary;
        private CustomAppAnimation m_mainContainerAnim;

        private ListBox m_resultsList;
        private MenuListAdapter m_resultListAdapter;
        private Grid m_resultsSpinner;
        private TextBlock m_resultsCount;
        private Button m_resultsClearButton;
        private ScrollViewer m_menuOptionsView;

        private Canvas m_resultsCountContainer;
        private Storyboard m_openResultCountAnim;
        private Storyboard m_closeResultCountAnim;

        static SearchMenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SearchMenuView), new FrameworkPropertyMetadata(typeof(SearchMenuView)));

            var uri = new Uri("/ExampleAppWPF;component/Colours.xaml", UriKind.Relative);
            genericResourceDictionary = (ResourceDictionary)Application.LoadComponent(uri);
        }

        public SearchMenuView(IntPtr nativeCallerPointer) : base(nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);

            Loaded += MainWindow_Loaded;
            mainWindow.SizeChanged += PerformLayout;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);
        }

        private void PerformLayout(object sender, SizeChangedEventArgs e)
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            double onScreenState = (currentPosition.X - m_mainContainerAnim.m_offscreenPos.X) / (m_mainContainerAnim.m_openPos.X - m_mainContainerAnim.m_offscreenPos.X);
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            m_screenWidthPx = mainWindow.MainGrid.ActualWidth;
            var screenWidthPy = mainWindow.MainGrid.ActualHeight;

            double dragTabWidthPx = m_dragTabView.ActualWidth;

            m_mainContainerOffscreenOffsetXPx = -m_dragTabView.Margin.Right;
            double mainContainerWidthPx = m_mainContainer.ActualWidth;
            m_mainContainerOnScreenWidthPx = mainContainerWidthPx - m_mainContainerOffscreenOffsetXPx;

            m_mainContainerAnim.m_widthHeight.X = mainContainerWidthPx + dragTabWidthPx;
            m_mainContainerAnim.m_offscreenPos.X = -(m_screenWidthPx / 2) - (m_mainContainerAnim.m_widthHeight.X / 2);
            m_mainContainerAnim.m_closedPos.X = m_mainContainerAnim.m_offscreenPos.X + ((mainContainerWidthPx + dragTabWidthPx) / 2);
            m_mainContainerAnim.m_openPos.X = m_mainContainerAnim.m_offscreenPos.X + m_mainContainerAnim.m_widthHeight.X;

            double layoutX = m_mainContainerAnim.m_offscreenPos.X;

            if (!m_isFirstLayout)
            {
                layoutX = onScreenState * (m_mainContainerAnim.m_openPos.X - m_mainContainerAnim.m_offscreenPos.X) + m_mainContainerAnim.m_offscreenPos.X;                
            }
                
            RenderTransform = new TranslateTransform(layoutX, currentPosition.Y);
            m_isFirstLayout = false;

            m_mainContainer.MaxHeight = screenWidthPy - m_mainContainer.RenderTransform.Transform(new Point(0.0, 0.0)).Y - 50;
            m_menuOptionsView.MaxHeight = screenWidthPy * 0.75;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_menuOptionsView = (ScrollViewer)GetTemplateChild("MenuOptionsView");
            m_resultsSpinner = (Grid)GetTemplateChild("SearchResultsSpinner");
            m_resultsCount = (TextBlock)GetTemplateChild("SearchResultCount");
            m_resultsCountContainer = (Canvas)GetTemplateChild("SearchResultCountContainer");

            m_resultsClearButton = (Button)GetTemplateChild("SearchClear");
            m_resultsClearButton.Click += OnResultsClear;

            m_list = (ListBox)GetTemplateChild("SecondaryMenuItemList");
            m_list.SelectionChanged += SelectionChanged;

            m_resultsList = (ListBox)GetTemplateChild("SearchResultsList");
            m_resultsList.SelectionChanged += OnResultSelected;
            
            m_dragTabView = (Button)GetTemplateChild("SecondaryMenuDragTabView");
            m_dragTabContainer = (Grid)GetTemplateChild("DragTabParentGrid");

            m_dragTabView.Click += OnIconClick;

            m_editText = (TextBox)GetTemplateChild("SecondaryMenuViewSearchEditTextView");
            m_editText.KeyDown += OnKeyDown;

            m_mainContainer = (Grid)GetTemplateChild("SecondaryMenuViewListContainer");
            m_mainContainerAnim = new CustomAppAnimation(m_mainContainer as FrameworkElement);

            m_menuAnimations.Add(m_mainContainerAnim);

            var fadeInItemStoryboard = ((Storyboard)Template.Resources["FadeInNewItems"]).Clone();
            var fadeOutItemStoryboard = ((Storyboard)Template.Resources["FadeOutOldItems"]).Clone();

            m_openResultCountAnim = ((Storyboard)Template.Resources["OpenSearchCount"]).Clone();
            m_closeResultCountAnim = ((Storyboard)Template.Resources["CloseSearchCount"]).Clone();

            m_adapter = new MenuListAdapter(false, m_list, fadeInItemStoryboard, fadeOutItemStoryboard);
            m_resultListAdapter= new MenuListAdapter(false, m_resultsList, fadeInItemStoryboard, fadeOutItemStoryboard);
        }

        private void ClearSearchResultsListBox()
        {
            m_resultListAdapter.ResetData();

            m_resultListAdapter.CollapseAll();
            m_resultsList.DataContext = null;
            m_resultsList.ItemsSource = null;
        }

        private void OnResultsClear(object sender, RoutedEventArgs e)
        {
            SearchMenuViewCLIMethods.OnSearchCleared(m_nativeCallerPointer);

            m_resultsClearButton.Visibility = Visibility.Hidden;

            ClearSearchResultsListBox();
        }

        private void OnIconClick(object sender, RoutedEventArgs e)
        {
            MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
        }

        private void OnResultSelected(object sender, SelectionChangedEventArgs e)
        {
            var resultsList = sender as ListBox;

            if (resultsList?.SelectedItems.Count > 0)
            {
                SearchMenuViewCLIMethods.HandleSearchItemSelected(m_nativeCallerPointer, resultsList.SelectedIndex);
            }
        }

        private void SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (IsAnimating() || m_adapter.IsAnimating())
            {
                (sender as ListBox).SelectedItem = null;
                return;
            }

            if (e.AddedItems != null && e.AddedItems.Count > 0)
            {
                MenuListItem item = (sender as ListBox).SelectedItem as MenuListItem;
                (sender as ListBox).SelectedItem = null;

                if (item != null)
                {
                    int position = m_adapter.Children.IndexOf(item);

                    int sectionIndex = m_adapter.GetSectionIndex(position);
                    int childIndex = m_adapter.GetItemIndex(position);

                    MenuViewCLIMethods.SelectedItem(m_nativeCallerPointer, sectionIndex, childIndex);
                }
            }
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
                }
            }
        }

        public void SetSearchSection(string category, string[] searchResults)
        {
            m_resultListAdapter.ResetData();

            var groups = new List<string>(searchResults.Length);
            var groupsExpandable = new List<bool>(searchResults.Length);
            var groupToChildren = new Dictionary<string, List<string>>();

            var itemsSource = new List<SearchMenuListItem>();

            foreach (var str in searchResults)
            {
                var jObject = JObject.Parse(str);
                var item = new SearchMenuListItem();
                item.Name = jObject["name"].Value<string>();
                item.Details = jObject["details"].Value<string>();

                JToken iconStringToken;
                var iconString = jObject.TryGetValue("icon", out iconStringToken) ? iconStringToken.Value<string>() : "misc";
                item.Icon = new System.Windows.Media.Imaging.BitmapImage(ViewHelpers.MakeUriForImage(string.Format("icon1_{0}.png", iconString)));
                itemsSource.Add(item);

                groups.Add(str);
                groupsExpandable.Add(false);
                groupToChildren.Add(str, new List<string>());
            }

            m_resultListAdapter.SetData(groups, groupsExpandable, groupToChildren);

            m_resultsList.DataContext = m_resultListAdapter;

            m_resultsList.ItemsSource = itemsSource;

            m_resultsSpinner.Visibility = Visibility.Hidden;
            m_resultsClearButton.Visibility = Visibility.Visible;
        }

        public override void AnimateToClosedOnScreen()
        {
            base.AnimateToClosedOnScreen();
            m_mainContainer.Visibility = Visibility.Hidden;
            m_closeResultCountAnim.Begin(m_resultsCountContainer);
        }

        public override void AnimateToOpenOnScreen()
        {
            base.AnimateToOpenOnScreen();
            m_mainContainer.Visibility = Visibility.Visible;
            m_openResultCountAnim.Begin(m_resultsCountContainer);
        }

        public void DisableEditText()
        {
            Dispatcher.Invoke(() =>
            {
                m_editText.IsEnabled = false;
            });
        }
        public void EnableEditText()
        {
            Dispatcher.Invoke(() =>
            {
                m_editText.IsEnabled = true;
            });
        }

        public void SetEditText(string text, bool isCategory)
        {
            m_editText.Text = text;
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
            }
        }

        protected override void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap)
        {
            m_adapter.SetData(groups, groupsExpandable, groupToChildrenMap);

            m_list.DataContext = m_adapter;
        }
    }
}
