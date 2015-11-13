using ExampleApp;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class SearchMenuView : MenuView
    {
        protected Button m_closeButtonView;
        protected ProgressBar m_progressSpinner;
        protected TextBlock m_numResultsText;
        protected FrameworkElement m_searchMenuViewListContainer;

        protected double m_totalHeightPx;

        protected double m_dragStartPosYPx;
        protected double m_controlStartPosYPx;

        private bool m_inAttractMode = false;

        private Image m_headerCategoryImage;
        private TextBlock m_headerText;

        static SearchMenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SearchMenuView), new FrameworkPropertyMetadata(typeof(SearchMenuView)));
        }

        public SearchMenuView(IntPtr nativeCallerPointer) : base(nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged += PerformLayout;
            mainWindow.MainGrid.Children.Add(this);
            Loaded += SearchMenuView_Loaded;
        }

        private void SearchMenuView_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            m_searchMenuViewListContainer = (FrameworkElement)GetTemplateChild("SearchMenuViewListContainer");
            m_list = (ListBox)GetTemplateChild("SearchMenuItemList");
            m_list.SelectionChanged += OnItemSelected;

            m_dragTabView = (Button)GetTemplateChild("SearchMenuDragTabView");
            m_dragTabView.Click += MenuView_Click;
            m_dragTabView.MouseMove += MenuView_MouseMove;

            m_closeButtonView = (Button)GetTemplateChild("SearchMenuCloseButton");
            m_closeButtonView.Click += CloseButtonClicked;

            m_progressSpinner = (ProgressBar)GetTemplateChild("SearchMenuSpinner");
            m_progressSpinner.Visibility = Visibility.Hidden;

            m_numResultsText = (TextBlock)GetTemplateChild("SearchMenuNumResultsText");
            m_numResultsText.Visibility = Visibility.Hidden;

            m_headerText = (TextBlock)GetTemplateChild("SearchMenuHeaderText");

            //m_headerCategoryImage = (Image)GetTemplateChild("SearchMenuHeaderCategoryIcon");

            PerformLayout(null, null);
        }
        private void OnItemSelected(object sender, SelectionChangedEventArgs e)
        {
            if (IsAnimating() || IsDragging())
            {
                (sender as ListBox).SelectedItem = null;
                return;
            }

            if (e.AddedItems != null && e.AddedItems.Count > 0)
            {
                var item = (sender as ListBox).SelectedItem as SearchMenuListItem;
                (sender as ListBox).SelectedItem = null;

                if (item != null)
                {
                    int position = m_list.Items.IndexOf(item);
                    MenuViewCLIMethods.SelectedItem(m_nativeCallerPointer, 0, position);
                }
            }
        }

        private void CloseButtonClicked(object sender, RoutedEventArgs e)
        {
            SearchMenuViewCLIMethods.HandleClosed(m_nativeCallerPointer);
        }

        public void UpdateHeader(String searchText, bool pendingQueryResult, int numResults)
        {
            Dispatcher.Invoke(() =>
            {
                if (pendingQueryResult)
                {
                    m_progressSpinner.Visibility = Visibility.Visible;
                    m_numResultsText.Visibility = Visibility.Hidden;
                }
                else
                {
                    m_numResultsText.Text = numResults.ToString();
                    m_numResultsText.Visibility = Visibility.Visible;
                    m_progressSpinner.Visibility = Visibility.Hidden;
                }

                if (m_headerCategoryImage != null)
                {
                    //m_headerCategoryImage.
                }

                m_headerText.Text = searchText;
            });
        }

        public void SetAttractMode(bool attractModeEnabled)
        {
            m_inAttractMode = attractModeEnabled;
            UpdateAttractMode();
        }

        private void UpdateAttractMode()
        {
            //m_dragTabView.clearAnimation();

            if (m_inAttractMode)
            {

                var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
                var animation = new DoubleAnimation();
                animation.From = currentPosition.Y;
                animation.To = currentPosition.Y - 10;
                animation.Duration = new Duration(TimeSpan.FromMilliseconds(300));
                animation.EasingFunction = new SineEase();
                animation.RepeatBehavior = RepeatBehavior.Forever;
                animation.AutoReverse = true;

                var transform = new TranslateTransform(currentPosition.X, currentPosition.Y);
                m_dragTabView.RenderTransform = transform;
                transform.BeginAnimation(TranslateTransform.YProperty, animation);
            }
        }


        protected override void HandleDragFinish(int xPx, int yPx)
        {
            m_dragInProgress = false;

            float minimumXValueToClose = StartedClosed(m_controlStartPosXPx) ? 0.35f : 0.65f;
            bool close = xPx < (m_totalWidthPx * minimumXValueToClose);
            double upXPx = close ? m_closedXPx : m_openXPx;
            Debug.WriteLine("ACTION_UP x: {0}", upXPx);

            AnimateViewToX(upXPx);
            MenuViewCLIMethods.ViewDragCompleted(m_nativeCallerPointer);
            UpdateAttractMode();
        }

        protected override void HandleDragUpdate(int xPx, int yPx)
        {
            //m_dragTabView.clearAnimation();

            double newXPx = m_controlStartPosXPx + (xPx - m_dragStartPosXPx);

            if (newXPx > m_mainContainerOffscreenOffsetXPx)
            {
                newXPx = m_mainContainerOffscreenOffsetXPx;
            }

            if (newXPx < m_closedXPx)
            {
                newXPx = m_closedXPx;
            }

            float normalisedDragState = (float)((newXPx + (-m_closedXPx)) / (Math.Abs(m_openXPx - m_closedXPx)));
            float clampedNormalisedDragState = Math.Max(Math.Min(normalisedDragState, 1.0f), 0.0f);

            MenuViewCLIMethods.ViewDragInProgress(m_nativeCallerPointer, clampedNormalisedDragState);

            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            RenderTransform = new TranslateTransform(newXPx, currentPosition.Y);
            Debug.WriteLine("ACTION_MOVE x: {0}, clamp: {1}", newXPx, clampedNormalisedDragState);
        }

        private void PerformLayout(object sender, SizeChangedEventArgs e)
        {
            if (m_dragTabView != null && m_searchMenuViewListContainer != null)
            {
                double dragTabWidthPx = m_dragTabView.ActualWidth;

                var listContainerPosition = m_searchMenuViewListContainer.RenderTransform.Transform(new Point(0.0, 0.0));
                m_mainContainerOffscreenOffsetXPx = -(listContainerPosition.X - m_searchMenuViewListContainer.ActualWidth * 0.5);
                double mainContainerWidthPx = m_searchMenuViewListContainer.ActualWidth;
                double mainContainerOnScreenWidthPx = mainContainerWidthPx;// - m_mainContainerOffscreenOffsetXPx;

                MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
                double windowWidth = mainWindow.ActualWidth;
                double totalWidth = mainContainerWidthPx + dragTabWidthPx;

                m_openXPx = 0;
                m_closedXPx = -mainContainerWidthPx;
                m_offscreenXPx = m_closedXPx - dragTabWidthPx;
                m_totalWidthPx = totalWidth;

                var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
                RenderTransform = new TranslateTransform(m_offscreenXPx, 0.0);
            }
        }


        protected override void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap)
        {
            List<string> searchData;
            
            if (groupToChildrenMap.TryGetValue("Search", out searchData))
            {
                var itemsSource = new List<SearchMenuListItem>();
                var jsonObjects = from json in searchData select JObject.Parse(json);

                foreach (var jsonObject in jsonObjects)
                {
                    var item = new SearchMenuListItem();
                    item.Name = jsonObject["name"].Value<string>();

                    JToken detailsToken;
                    item.Details = jsonObject.TryGetValue("details", out detailsToken) ?  detailsToken.Value<string>() : "";

                    JToken iconStringToken;
                    var iconString = jsonObject.TryGetValue("icon", out iconStringToken) ? iconStringToken.Value<string>() : "misc";
                    item.Icon = new BitmapImage(new Uri(string.Format("pack://application:,,,/ExampleAppWPF;component/Assets/icon1_{0}.png", iconString), UriKind.Absolute));

                    itemsSource.Add(item);
                }

                m_list.ItemsSource = itemsSource;
            }
        }
    }
}
