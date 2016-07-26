using ExampleApp;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public class InteriorsExplorerView : ControlBase
    {
        private IntPtr m_nativeCallerPointer;
        private Slider m_floorSlider;
        private TickBarVerticalWithLabels m_sliderTickBar;
        private TextBlock m_floorName;
        private Button m_dismissButton;
        private Grid m_floorPanel;
        private Grid m_detailsPanel;
        
        private int m_selectedFloorIndex;
        private double m_panelOffscreenOffsetX;
        private double m_stateChangeAnimationTimeMilliseconds = 200.0;
        private bool m_dragInProgress = false;
        private string[] m_floorShortNames = new string[] { };

        private const float DefaultOffscreenOffsetX = 100.0f;

        private int FloorCount { get { return m_floorShortNames.Length; } }
        private bool FloorSelectionEnabled { get { return FloorCount > 1; } }

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

            m_panelOffscreenOffsetX = DefaultOffscreenOffsetX;

            m_floorSlider = GetTemplateChild("FloorSlider") as Slider;
            m_floorSlider.ValueChanged += OnSliderValueChanged;

            m_floorSlider.ApplyTemplate();

            m_sliderTickBar = GetTickBar(m_floorSlider);

            var sliderThumb = GetThumb(m_floorSlider);

            sliderThumb.DragStarted += OnSliderDragStarted;
            sliderThumb.DragCompleted += OnSliderDragCompleted;

            m_floorName = (TextBlock)GetTemplateChild("FloorName");

            m_dismissButton = (Button)GetTemplateChild("DismissButton");
            m_dismissButton.Click += OnClickDismiss;

            m_floorPanel = (Grid)GetTemplateChild("FloorPanel");

            m_detailsPanel = (Grid)GetTemplateChild("DetailsPanel");

            m_detailsPanel.Opacity = 0.0f;
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));
            m_floorPanel.RenderTransform = new TranslateTransform(m_panelOffscreenOffsetX, currentPosition.Y);

            SetTouchEnabled(false);
            Hide();
        }

        public void PlaySliderShakeAnim()
        {
            var position = m_floorSlider.RenderTransform.Transform(new Point());
            var offset = m_floorSlider.ActualWidth / 3.0;

            var anim = new DoubleAnimation();
            anim.From = position.X - offset;
            anim.To = position.X;
            anim.EasingFunction = new ElasticEase()
            {
                EasingMode = EasingMode.EaseOut,
                Springiness = 2
            };
            anim.Duration = new Duration(TimeSpan.FromMilliseconds(1100));

            var transform = new TranslateTransform(position.X - offset, position.Y);

            m_floorSlider.RenderTransform = transform;
            transform.BeginAnimation(TranslateTransform.XProperty, anim);
        }

        private void OnAnimCompleted(object sender, EventArgs e)
        {
            GetThumb(m_floorSlider).RenderTransform = new ScaleTransform(1.0, 1.0);
        }

        private static Thumb GetThumb(Slider slider)
        {
            var track = slider.Template.FindName("PART_Track", slider) as Track;
            return track == null ? null : track.Thumb;
        }

        private static TickBarVerticalWithLabels GetTickBar(Slider slider)
        {
            var tickBar = slider.Template.FindName("SliderTickBar", slider);
            return tickBar == null ? null : tickBar as TickBarVerticalWithLabels;
        }

        private void OnClickDismiss(object sender, RoutedEventArgs e)
        {
            InteriorsExplorerCLIMethods.Dismiss(m_nativeCallerPointer);
        }

        public void Destroy()
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            if (mainWindow != null)
            {
                mainWindow.MainGrid.Children.Remove(this);
            }
        }
        public void UpdateFloors(string[] floorShortNames, int currentlySelectedFloorIndex)
        {
            m_floorShortNames = floorShortNames;

            m_sliderTickBar.TickLabels = string.Join(",", floorShortNames);

            m_selectedFloorIndex = currentlySelectedFloorIndex;

            m_floorSlider.Minimum = 0;
            m_floorSlider.Maximum = FloorCount - 1;
            SetSelectedFloor(currentlySelectedFloorIndex);
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
            m_selectedFloorIndex = floorIndex;
            if (!m_dragInProgress)
            {
                m_floorSlider.Value = m_selectedFloorIndex;
                UpdateFloorSliderTagFromValue();
            }
        }

        public void SetOnScreenStateToIntermediateValue(float transitionParam)
        {
            double newX = CalcPanelX(transitionParam);
            m_detailsPanel.Opacity = transitionParam;
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));
            m_floorPanel.RenderTransform = new TranslateTransform(newX, currentPosition.Y);
        }

        private double CalcPanelX(double t)
        {
            t = Math.Min(Math.Max(t, 0.0), 1.0);
            double newX = m_panelOffscreenOffsetX - t * m_panelOffscreenOffsetX;
            return newX;
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
            floorPanelAnimation.BeginTime = TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds * 5);
            floorPanelAnimation.From = currentPosition.X;
            floorPanelAnimation.To = CalcPanelX(FloorSelectionEnabled ? t : 0.0f);
            floorPanelAnimation.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));

            var floorPanelTransform = new TranslateTransform(currentPosition.X, currentPosition.Y);
            m_floorPanel.RenderTransform = floorPanelTransform;
            floorPanelTransform.BeginAnimation(TranslateTransform.XProperty, floorPanelAnimation);

            var dismissButtonTransform = new TranslateTransform(CalcPanelX(1.0 - t), 0);
            m_dismissButton.RenderTransform = dismissButtonTransform;
            floorPanelAnimation.To = t;
            dismissButtonTransform.BeginAnimation(TranslateTransform.XProperty, floorPanelAnimation);

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

        private void OnSliderDragStarted(object sender, DragStartedEventArgs e)
        {
            m_dragInProgress = true;
            SetFloorSelectionDrag(m_floorSlider.Value);
        }

        private void OnSliderDragCompleted(object sender, DragCompletedEventArgs e)
        {
            m_dragInProgress = false;

            var floorIndex = (int)Math.Round(m_floorSlider.Value);
            m_floorSlider.Value = floorIndex;

            InteriorsExplorerCLIMethods.SelectFloor(m_nativeCallerPointer, floorIndex);
        }

        private void OnSliderValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (m_dragInProgress)
            {
                SetFloorSelectionDrag(e.NewValue);
            }
        }

        private void SetFloorSelectionDrag(double sliderValue)
        {
            double dragParam = Math.Min(1.0, sliderValue / m_floorSlider.Maximum);
            InteriorsExplorerCLIMethods.SetFloorSelectionDrag(m_nativeCallerPointer, dragParam);
            UpdateFloorSliderTagFromValue();
        }

        private void UpdateFloorSliderTagFromValue()
        {
            var floorIndex = (int)Math.Round(m_floorSlider.Value);
            m_floorSlider.Tag = m_floorShortNames[floorIndex];

        }
    }
}
