using ExampleApp;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public class InteriorsExplorerView : ControlBase
    {
        private IntPtr m_nativeCallerPointer;
        private ListBox m_floorList;
        private TextBlock m_floorName;
        private Button m_dismissButton;
        private Grid m_floorPanel;
        private Grid m_detailsPanel;
        private int m_floorCount;
        private double m_stateChangeAnimationTimeMilliseconds = 200.0;

        static InteriorsExplorerView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(InteriorsExplorerView), new FrameworkPropertyMetadata(typeof(InteriorsExplorerView)));
        }

        public InteriorsExplorerView(IntPtr nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);
            m_nativeCallerPointer = nativeCallerPointer;
        }
        
        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_floorList = (ListBox)GetTemplateChild("FloorList");
            m_floorName = (TextBlock)GetTemplateChild("FloorName");

            m_floorList.SelectionChanged += OnSelectionChanged;

            m_dismissButton = (Button)GetTemplateChild("DismissButton");
            m_dismissButton.Click += OnClickDismiss;

            m_floorPanel = (Grid)GetTemplateChild("FloorPanel");
            m_detailsPanel = (Grid)GetTemplateChild("DetailsPanel");

            m_detailsPanel.Opacity = 0.0f;
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));
            m_floorPanel.RenderTransform = new TranslateTransform(-50.0, currentPosition.Y);

            m_floorList.SelectionMode = SelectionMode.Single;
        }

        private void OnClickDismiss(object sender, RoutedEventArgs e)
        {
            InteriorsExplorerCLIMethods.Dismiss(m_nativeCallerPointer);
        }

        private void OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            InteriorsExplorerCLIMethods.SelectFloor(m_nativeCallerPointer, (m_floorCount - 1) - m_floorList.SelectedIndex);
        }

        public void Destroy()
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            if (mainWindow != null)
            {
                mainWindow.MainGrid.Children.Remove(this);
            }
        }
        public void UpdateFloors(string[] floorNames, int currentlySelectedFloorIndex)
        {
            m_floorList.ItemsSource = floorNames;
            m_floorCount = floorNames.Length;
            m_floorList.SelectedIndex = m_floorCount - 1 - currentlySelectedFloorIndex;
        }
        public void SetFloorName(string name)
        {
            if (m_floorName != null)
            {
                m_floorName.Text = name;
            }
        }
        public void SetSelectedFloor(int floorIndex)
        {
            int selectedIndex = (m_floorCount - 1) - floorIndex;

            if (m_floorList.SelectedIndex != selectedIndex)
            {
                m_floorList.SelectedIndex = selectedIndex;
            }
        }

        public void SetOnScreenStateToIntermediateValue(float intermediateValue)
        {
            float newX = -50 + intermediateValue * 50.0f;
            m_detailsPanel.Opacity = intermediateValue;
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));
            m_floorPanel.RenderTransform = new TranslateTransform(newX, currentPosition.Y);
        }

        public void SetFullyOnScreen()
        {
            AnimateTo(1.0f);
        }

        public void SetFullyOffScreen()
        {
            AnimateTo(0.0f);
        }
        private void AnimateTo(float t)
        {
            if (t > 0.0f)
            {
                Visibility = Visibility.Visible;
            }

            var storyboard = new Storyboard();
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));

            var floorPanelAnimation = new DoubleAnimation();
            floorPanelAnimation.From = currentPosition.X;
            floorPanelAnimation.To = -50.0f + t * 50.0f;
            floorPanelAnimation.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));

            var transform = new TranslateTransform(currentPosition.X, currentPosition.Y);
            m_floorPanel.RenderTransform = transform;
            transform.BeginAnimation(TranslateTransform.XProperty, floorPanelAnimation);

            var detailsPanelAnimation = new DoubleAnimation();
            detailsPanelAnimation.From = m_detailsPanel.Opacity;
            detailsPanelAnimation.To = t;
            detailsPanelAnimation.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));
            
            detailsPanelAnimation.Completed += Storyboard_Completed;

            m_detailsPanel.BeginAnimation(OpacityProperty, detailsPanelAnimation);
        }

        private void Storyboard_Completed(object sender, EventArgs e)
        {
            Visibility = (m_detailsPanel.Opacity == 0.0) ? Visibility.Hidden : Visibility.Visible;
        }

        public void SetTouchEnabled(bool enabled)
        {
            m_floorPanel.IsHitTestVisible = enabled;
            m_detailsPanel.IsHitTestVisible = enabled;
        }

        public void SetFloorPanelEnabled(bool enabled)
        {
            m_floorPanel.IsHitTestVisible = enabled;
        }

        public void Show()
        {
            Visibility = Visibility.Visible;
        }
        public void Hide()
        {
            Visibility = Visibility.Hidden;
        }    
    }
}
