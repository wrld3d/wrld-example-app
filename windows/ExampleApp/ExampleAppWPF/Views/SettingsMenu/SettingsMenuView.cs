using ExampleApp;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class SettingsMenuView : MenuView
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
        private CustomAppAnimation m_mainContainerAnim;

        static SettingsMenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SettingsMenuView), new FrameworkPropertyMetadata(typeof(SettingsMenuView)));
            var uri = new Uri("/ExampleAppWPF;component/Colours.xaml", UriKind.Relative);
            genericResourceDictionary = (ResourceDictionary)Application.LoadComponent(uri);
        }

        public SettingsMenuView(IntPtr nativeCallerPointer) : base(nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged += PerformLayout;
            mainWindow.MainGrid.Children.Add(this);
            Loaded += SettingsMenuView_Loaded;
        }

        private void SettingsMenuView_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);
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

            m_mainContainer = (Grid)GetTemplateChild("SecondaryMenuViewListContainer");
            m_mainContainerAnim = new CustomAppAnimation(m_mainContainer as FrameworkElement);
            m_mainContainer.RenderTransformOrigin = new Point(0.5, 0.5);

            m_menuAnimations.Add(m_mainContainerAnim);

            var fadeInItemStoryboard = ((Storyboard)Template.Resources["FadeInNewItems"]).Clone();
            var fadeOutItemStoryboard = ((Storyboard)Template.Resources["FadeOutOldItems"]).Clone();

            m_adapter = new MenuListAdapter(false, m_list, fadeInItemStoryboard, fadeOutItemStoryboard);

            PerformLayout(null, null);
        }

        private void OnResultSelected(object sender, SelectionChangedEventArgs e)
        {
            //throw new NotImplementedException();
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
            if (m_isMouseDown)
            {
                m_dragTabContainer.Background = (SolidColorBrush)genericResourceDictionary["Gold"];
                MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
            }
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
            m_mainContainerAnim.m_offscreenPos.X = (m_screenWidthPx / 2) + (m_mainContainerAnim.m_widthHeight.X / 2);
            m_mainContainerAnim.m_closedPos.X = m_mainContainerAnim.m_offscreenPos.X - ((mainContainerWidthPx + dragTabWidthPx) / 2);
            m_mainContainerAnim.m_openPos.X = m_mainContainerAnim.m_offscreenPos.X - m_mainContainerAnim.m_widthHeight.X;

            double layoutX = m_mainContainerAnim.m_offscreenPos.X;

            if (!m_isFirstLayout)
            {
                layoutX = onScreenState * (m_mainContainerAnim.m_openPos.X - m_mainContainerAnim.m_offscreenPos.X) + m_mainContainerAnim.m_offscreenPos.X;
            }

            RenderTransform = new TranslateTransform(layoutX, currentPosition.Y);
            m_isFirstLayout = false;
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
