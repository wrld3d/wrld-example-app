using ExampleApp;
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
        private bool m_isMouseDown = false;
        private static readonly ResourceDictionary genericResourceDictionary;

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
            double onScreenState = (currentPosition.X - m_offscreenXPx) / (m_openXPx - m_offscreenXPx);
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            m_screenWidthPx = mainWindow.MainGrid.ActualWidth;

            double dragTabWidthPx = m_dragTabView.ActualWidth;

            m_mainContainerOffscreenOffsetXPx = -m_dragTabView.Margin.Right;
            double mainContainerWidthPx = m_mainContainer.ActualWidth;
            m_mainContainerOnScreenWidthPx = mainContainerWidthPx - m_mainContainerOffscreenOffsetXPx;

            m_totalWidthPx = mainContainerWidthPx + dragTabWidthPx;
            m_offscreenXPx = -(m_screenWidthPx / 2) - (m_totalWidthPx / 2);
            m_closedXPx = m_offscreenXPx + ((mainContainerWidthPx + dragTabWidthPx) / 2);
            m_openXPx = m_offscreenXPx + m_totalWidthPx;

            double layoutX = m_offscreenXPx;

            if (!m_isFirstLayout)
            {
                layoutX = onScreenState * (m_openXPx - m_offscreenXPx) + m_offscreenXPx;                
            }
                
            RenderTransform = new TranslateTransform(layoutX, currentPosition.Y);
            m_isFirstLayout = false;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_list = (ListBox)GetTemplateChild("SecondaryMenuItemList");
            m_list.SelectionChanged += SelectionChanged;
            
            m_dragTabView = (Image)GetTemplateChild("SecondaryMenuDragTabView");
            m_dragTabContainer = (Grid)GetTemplateChild("DragTabParentGrid");

            m_dragTabView.MouseLeftButtonDown += OnMouseLeftButtonDown;
            m_dragTabView.MouseLeftButtonUp += OnMouseLeftButtonUp;
            m_dragTabView.MouseLeave += OnMouseLeave;

            m_editText = (TextBox)GetTemplateChild("SecondaryMenuViewSearchEditTextView");
            m_editText = (TextBox)GetTemplateChild("SecondaryMenuViewSearchEditTextView");
            m_editText.KeyDown += OnKeyDown;

            m_mainContainer = (Grid)GetTemplateChild("SecondaryMenuViewListContainer");

            var fadeInItemStoryboard = ((Storyboard)Template.Resources["FadeInNewItems"]).Clone();
            var fadeOutItemStoryboard = ((Storyboard)Template.Resources["FadeOutOldItems"]).Clone();
            
            m_adapter = new MenuListAdapter(false, m_list, fadeInItemStoryboard, fadeOutItemStoryboard);
        }

        private void OnMouseLeave(object sender, MouseEventArgs e)
        {
            m_dragTabContainer.Background = (SolidColorBrush)genericResourceDictionary["Gold"];
            m_isMouseDown = false;
        }

        private void OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            m_dragTabContainer.Background = (SolidColorBrush)genericResourceDictionary["Highlight"];
            m_isMouseDown = true;
        }

        private void OnMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if(m_isMouseDown)
            {
                m_dragTabContainer.Background = (SolidColorBrush)genericResourceDictionary["Gold"];
                MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
            }
        }

        private void SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (IsAnimating() || IsDragging() || m_adapter.IsAnimating())
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
                }
            }
        }

        protected override void HandleDragFinish(int xPx, int yPx)
        {
            m_dragInProgress = false;

            double xRatioForStateChange = StartedClosed(m_controlStartPosXPx) ? 0.35f : 0.65f;
            double threshold = (m_screenWidthPx - (m_mainContainerOnScreenWidthPx * xRatioForStateChange));
            bool open = xPx < threshold;
            double upXPx = (open ? m_openXPx : m_closedXPx);
            Debug.WriteLine("ACTION_UP  x: {0}", upXPx);

            AnimateViewToX(upXPx);
            MenuViewCLIMethods.ViewDragCompleted(m_nativeCallerPointer);
        }

        protected override void HandleDragUpdate(int xPx, int yPx)
        {
            double newXPx = m_controlStartPosXPx + (xPx - m_dragStartPosXPx);

            if (newXPx < (m_screenWidthPx - m_totalWidthPx))
            {
                newXPx = m_screenWidthPx - m_totalWidthPx;
            }

            if (newXPx > m_closedXPx)
            {
                newXPx = m_closedXPx;
            }

            double normalisedDragState = Math.Abs(newXPx + (-m_closedXPx)) / (Math.Abs(m_openXPx - m_closedXPx));
            float clampedNormalisedDragState = Math.Max(Math.Min((float)normalisedDragState, 1.0f), 0.0f);

            MenuViewCLIMethods.ViewDragInProgress(m_nativeCallerPointer, clampedNormalisedDragState);

            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            RenderTransform = new TranslateTransform(newXPx, currentPosition.Y);
            Debug.WriteLine("ACTION_MOVE x: {0}, clamp: {1}", newXPx, clampedNormalisedDragState);
        }

        public void SetSearchSection(string[] searchResults)
        {

        }

        public override void AnimateToClosedOnScreen()
        {
            base.AnimateToClosedOnScreen();
            m_mainContainer.Visibility = Visibility.Hidden;
        }

        public override void AnimateToOpenOnScreen()
        {
            base.AnimateToOpenOnScreen();
            m_mainContainer.Visibility = Visibility.Visible;
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

        }

        public void SetSearchResultCount(int count)
        {

        }

        void CollapseAll()
        {

        }

        protected override void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap)
        {
            m_adapter.SetData(groups, groupsExpandable, groupToChildrenMap);

            if (m_list.DataContext != m_adapter)
            {
                m_list.DataContext = m_adapter;
            }
        }
    }
}
