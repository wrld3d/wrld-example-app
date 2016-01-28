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
        private Image m_dragInteractionDirectionArrow;
        private MenuListAdapter m_adapter;
        private bool m_isFirstLayout = true;

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
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);
        }

        private void PerformLayout(object sender, SizeChangedEventArgs e)
        {
            if (m_dragInteractionDirectionArrow != null)
            {
                var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
                double onScreenState = (currentPosition.X - m_offscreenXPx) / (m_openXPx - m_offscreenXPx);
                MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
                m_screenWidthPx = mainWindow.MainGrid.ActualWidth;

                FrameworkElement listContainerView = (FrameworkElement)GetTemplateChild("SecondaryMenuViewListContainer");
                double dragTabWidthPx = m_dragTabView.ActualWidth;

                m_mainContainerOffscreenOffsetXPx = -m_dragTabView.Margin.Right;
                double mainContainerWidthPx = listContainerView.ActualWidth;
                m_mainContainerOnScreenWidthPx = mainContainerWidthPx - m_mainContainerOffscreenOffsetXPx;

                m_totalWidthPx = mainContainerWidthPx + dragTabWidthPx;
                m_offscreenXPx = m_screenWidthPx - Padding.Right;
                m_closedXPx = m_screenWidthPx - /*m_activity.dipAsPx*/(m_mainContainerVisibleOnScreenWhenClosedDip) - dragTabWidthPx;
                m_openXPx = m_screenWidthPx - m_mainContainerOnScreenWidthPx - dragTabWidthPx - Padding.Right;

                double layoutX = m_offscreenXPx;

                if (!m_isFirstLayout)
                {
                    layoutX = onScreenState * (m_openXPx - m_offscreenXPx) + m_offscreenXPx;                
                }
                
                RenderTransform = new TranslateTransform(layoutX, currentPosition.Y);
                m_isFirstLayout = false;
            }
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_dragInteractionDirectionArrow = (Image)GetTemplateChild("SecondaryMenuDragInteractionArrow");
            m_list = (ListBox)GetTemplateChild("SecondaryMenuItemList");
            m_list.SelectionChanged += SelectionChanged;
            
            m_dragTabView = (Image)GetTemplateChild("SecondaryMenuDragTabView");
            
            m_dragTabClickHandler = new ControlClickHandler(m_dragTabView, OnDragTabMouseClick);

            m_dragTabView.MouseLeftButtonDown += OnDragTabMouseLeftButtonDown;
            m_dragTabView.MouseLeftButtonUp += OnDragTabMouseLeftButtonUp;

            m_editText = (TextBox)GetTemplateChild("SecondaryMenuViewSearchEditTextView");
            m_editText = (TextBox)GetTemplateChild("SecondaryMenuViewSearchEditTextView");
            m_editText.KeyDown += OnKeyDown;

            var fadeInItemStoryboard = ((Storyboard)Template.Resources["FadeInNewItems"]).Clone();
            var fadeOutItemStoryboard = ((Storyboard)Template.Resources["FadeOutOldItems"]).Clone();
            
            m_adapter = new MenuListAdapter(false, m_list, fadeInItemStoryboard, fadeOutItemStoryboard);
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
                    //SecondaryMenuViewCLIMethods.PerformSearchQuery(m_nativeCallerPointer, queryText);
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
                ShowInteractionArrowOpen();
            }

            if (newXPx > m_closedXPx)
            {
                newXPx = m_closedXPx;
                ShowInteractionArrowClosed();
            }

            double normalisedDragState = Math.Abs(newXPx + (-m_closedXPx)) / (Math.Abs(m_openXPx - m_closedXPx));
            float clampedNormalisedDragState = Math.Max(Math.Min((float)normalisedDragState, 1.0f), 0.0f);

            MenuViewCLIMethods.ViewDragInProgress(m_nativeCallerPointer, clampedNormalisedDragState);

            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            RenderTransform = new TranslateTransform(newXPx, currentPosition.Y);
            Debug.WriteLine("ACTION_MOVE x: {0}, clamp: {1}", newXPx, clampedNormalisedDragState);
        }

        public override void AnimateToClosedOnScreen()
        {
            ShowInteractionArrowClosed();
            base.AnimateToClosedOnScreen();
        }

        public override void AnimateToOpenOnScreen()
        {
            ShowInteractionArrowOpen();
            base.AnimateToOpenOnScreen();
        }

        void ShowInteractionArrowOpen()
        {
            m_dragInteractionDirectionArrow.RenderTransform = new RotateTransform(180);
            m_dragInteractionDirectionArrow.RenderTransformOrigin = new Point(0.5, 0.5);
        }

        void ShowInteractionArrowClosed()
        {
            m_dragInteractionDirectionArrow.RenderTransform = new RotateTransform(0);
            m_dragInteractionDirectionArrow.RenderTransformOrigin = new Point(0.5, 0.5);
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
