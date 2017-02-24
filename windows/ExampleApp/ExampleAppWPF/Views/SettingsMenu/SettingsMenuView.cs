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
using System.Windows.Shapes;

namespace ExampleAppWPF
{
    public class SettingsMenuView : MenuView
    {
        private MenuListAdapter m_adapter;
        private ControlClickHandler m_menutItemHandler;

        private WindowInteractionTouchHandler m_touchHandler;

        static SettingsMenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SettingsMenuView), new FrameworkPropertyMetadata(typeof(SettingsMenuView)));
        }

        public SettingsMenuView(IntPtr nativeCallerPointer, bool isInKioskMode) : base(nativeCallerPointer, isInKioskMode)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged += PerformLayout;
            mainWindow.MainGrid.Children.Add(this);
            Loaded += SettingsMenuView_Loaded;
            m_touchHandler = new WindowInteractionTouchHandler(this, false, true, true);
        }

        private void SettingsMenuView_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_list = (ListBox)GetTemplateChild("SettingsMenuItemList");
            m_menutItemHandler = new ControlClickHandler(OnSelectionChanged, m_list);

            m_menuIcon = (Button)GetTemplateChild("SettingsMenuIconButton");

            m_menuIcon.Click += OnIconClick;

            m_mainContainer = (Grid)GetTemplateChild("SettingsMenuMainContainer");

            var itemShutterOpenStoryboard = ((Storyboard)Template.Resources["ItemShutterOpen"]).Clone();
            var itemShutterCloseStoryboard = ((Storyboard)Template.Resources["ItemShutterClose"]).Clone();

            var slideInItemStoryboard = ((Storyboard)Template.Resources["SlideInNewItems"]).Clone();
            var slideOutItemStoryboard = ((Storyboard)Template.Resources["SlideOutOldItems"]).Clone();

            m_menuViewContainer = (Grid)GetTemplateChild("SettingsMenuViewContainer");
            m_backgroundRectangle = (Rectangle)GetTemplateChild("BackgroundRect");

            m_menuIconGrid = (Grid)GetTemplateChild("SettingsIconGrid");

            string settingsAnimString = "SettingsAnim";

            string openMenuViewIconString = "OpenMenuViewIcon";
            m_openMenuIconAnim = ((Storyboard)Template.Resources[openMenuViewIconString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_openMenuIconAnim, settingsAnimString + openMenuViewIconString);
            string closeMenuViewIconString = "CloseMenuViewIcon";
            m_closeMenuIconAnim = ((Storyboard)Template.Resources[closeMenuViewIconString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_closeMenuIconAnim, settingsAnimString + closeMenuViewIconString);

            string openMenuContainerString = "OpenMenuContainer";
            m_openMenuContainerAnim = ((Storyboard)Template.Resources[openMenuContainerString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_openMenuContainerAnim, settingsAnimString + openMenuContainerString);
            string closeMenuContainerString = "CloseMenuContainer";
            m_closeMenuContainerAnim = ((Storyboard)Template.Resources[closeMenuContainerString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_closeMenuContainerAnim, settingsAnimString + closeMenuContainerString);

            string openBackgroundRectString = "OpenBackgroundRect";
            m_openBackgroundRect = ((Storyboard)Template.Resources[openBackgroundRectString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_openBackgroundRect, settingsAnimString + openBackgroundRectString);
            string closeBackgroundRectString = "CloseBackgroundRect";
            m_closeBackgroundRect = ((Storyboard)Template.Resources[closeBackgroundRectString]).Clone();
            XamlHelpers.UpdateThicknessAnimationMarginValue(m_closeBackgroundRect, settingsAnimString + closeBackgroundRectString);

            m_adapter = new MenuListAdapter(false, m_list,slideInItemStoryboard, slideOutItemStoryboard, itemShutterOpenStoryboard, itemShutterCloseStoryboard, "SettingsMenuItemPanel", m_isInKioskMode);

            PerformLayout(null, null);
        }

        private void OnIconClick(object sender, RoutedEventArgs e)
        {
            MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
        }

        private void OnSelectionChanged(object sender, MouseEventArgs e)
        {
            if (IsAnimating() || m_adapter.IsAnimating())
            {
                (sender as ListBox).SelectedItem = null;
                return;
            }

            var item = m_list.SelectedItem as MenuListItem;
            if (item != null)
            {
                var sectionChildIndices = m_adapter.GetSectionAndChildIndicesFromSelection(m_list.SelectedIndex);
                MenuViewCLIMethods.SelectedItem(m_nativeCallerPointer, sectionChildIndices.Item1, sectionChildIndices.Item2);
            }
        }

        public new void PerformLayout(object sender, SizeChangedEventArgs e)
        {
            var screenWidth = m_mainWindow.MainGrid.ActualWidth;
            var totalWidth = m_mainContainer.ActualWidth + m_menuIcon.ActualWidth;

            m_onScreenPos = (screenWidth / 2);
            m_offScreenPos = (screenWidth / 2) + (totalWidth / 2);

            base.PerformLayout(sender, e);
        }


        protected override void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap)
        {
            m_adapter.SetData(m_list.ItemsSource, groups, groupsExpandable, groupToChildrenMap);
        }

        public override void AnimateToOpenOnScreen()
        {
            m_backgroundRectangle.RenderTransformOrigin = new Point(-1.0, 0.0);
            base.AnimateToOpenOnScreen();
        }

        public override void AnimateToClosedOnScreen()
        {
            m_backgroundRectangle.RenderTransformOrigin = new Point(0.0, 0.0);
            base.AnimateToClosedOnScreen();
        }
    }
}
