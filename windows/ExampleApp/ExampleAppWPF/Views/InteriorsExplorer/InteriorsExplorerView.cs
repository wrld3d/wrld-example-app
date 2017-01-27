using ExampleApp;
using System;
using System.Linq;
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
		private Grid m_container;
        private Slider m_floorSlider;
        private Thumb m_sliderThumb;
        private TickBarVerticalWithLabels m_sliderTickBar;
        private TextBlock m_floorName;
        private Button m_dismissButton;
        private Grid m_floorPanel;
        private Grid m_detailsPanel;
        private InteriorsExplorerTutorialView m_tutorialView;
        
        private int m_selectedFloorIndex;
        private double m_panelOffscreenOffsetX;
        private double m_stateChangeAnimationTimeMilliseconds = 200.0;
        private bool m_dragInProgress = false;
        private bool m_animationInProgress = false;
        private string[] m_floorShortNames = new string[] {};

        private int FloorCount { get { return m_floorShortNames.Length; } }
        private bool FloorSelectionEnabled { get { return FloorCount > 1; } }

        private bool m_showTutorialView = false;

        static InteriorsExplorerView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(InteriorsExplorerView), new FrameworkPropertyMetadata(typeof(InteriorsExplorerView)));            
        }

        public InteriorsExplorerView(IntPtr nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);
            m_nativeCallerPointer = nativeCallerPointer;

            mainWindow.ContentRendered += (o, e) =>
            {
                SearchMenuView searchMenuView = ViewHelpers.FindChildrenOfType<SearchMenuView>(mainWindow.MainGrid.Children).Single();
                CompassView compassView = ViewHelpers.FindChildrenOfType<CompassView>(mainWindow.MainGrid.Children).Single();
                m_tutorialView.SetTooltipControls(mainWindow,
                                                  searchMenuView.GetSearchButton(),
                                                  compassView.GetCompassElement(),
                                                  m_sliderThumb);
            };
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_panelOffscreenOffsetX = ((double)Application.Current.Resources["SliderThumbSize"]) * 2;
			
			m_container = GetTemplateChild("Container") as Grid;

			m_floorSlider = GetTemplateChild("FloorSlider") as Slider;
            m_floorSlider.ValueChanged += OnSliderValueChanged;

            m_floorSlider.ApplyTemplate();

            m_sliderTickBar = GetTickBar(m_floorSlider);

            m_sliderThumb = GetThumb(m_floorSlider);

            m_sliderThumb.DragStarted += OnSliderDragStarted;
            m_sliderThumb.DragCompleted += OnSliderDragCompleted;

            m_floorName = (TextBlock)GetTemplateChild("FloorName");

            m_dismissButton = (Button)GetTemplateChild("DismissButton");
            m_dismissButton.Click += OnClickDismiss;

            m_floorPanel = (Grid)GetTemplateChild("FloorPanel");

            m_detailsPanel = (Grid)GetTemplateChild("DetailsPanel");

            m_detailsPanel.Opacity = 0.0f;
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));
            m_floorPanel.RenderTransform = new TranslateTransform(m_panelOffscreenOffsetX, currentPosition.Y);

            var dismissButtonPosition = m_dismissButton.RenderTransform.Transform(new Point());
            m_dismissButton.RenderTransform = new TranslateTransform(m_panelOffscreenOffsetX, dismissButtonPosition.Y);

            m_tutorialView = (InteriorsExplorerTutorialView) GetTemplateChild("InteriorsExplorerTutorialView");
			m_tutorialView.Hide();

            SetTouchEnabled(false);
            Hide();
        }

        public void PlaySliderShakeAnim()
        {
            if(m_animationInProgress)
            {
                return;
            }

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
            anim.Completed += OnAnimCompleted;

            var transform = new TranslateTransform(position.X - offset, position.Y);

            m_floorSlider.RenderTransform = transform;
            transform.BeginAnimation(TranslateTransform.XProperty, anim);

            m_animationInProgress = true;
        }

        private void OnAnimCompleted(object sender, EventArgs e)
        {
            m_animationInProgress = false;
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
            System.Diagnostics.Debug.Assert(floorShortNames != null, "floorShortNames cannot be null");
            m_floorShortNames = floorShortNames;

            m_sliderTickBar.TickLabels = string.Join(",", floorShortNames);

			m_selectedFloorIndex = currentlySelectedFloorIndex;

            m_floorSlider.Minimum = 0;
            m_floorSlider.Maximum = FloorCount - 1;
			SetSelectedFloor(currentlySelectedFloorIndex);

			m_floorPanel.Visibility = FloorSelectionEnabled ? Visibility.Visible : Visibility.Hidden;
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

				Point dismissButtonPosition = m_dismissButton.TransformToAncestor(Application.Current.MainWindow).Transform(new Point());
				Point sliderPosition = m_floorSlider.TransformToAncestor(Application.Current.MainWindow).Transform(new Point());

				double sliderHeight = m_sliderTickBar.ActualHeight - m_sliderTickBar.ReservedSpace;
				double sliderFloorSpacing = sliderHeight * m_sliderTickBar.TickFrequency / Math.Max(FloorCount - 1, 1);
			}
        }

        public void SetOnScreenStateToIntermediateValue(float transitionParam)
        {
            double newX = CalcPanelX(transitionParam);
            m_detailsPanel.Opacity = transitionParam;
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));
            m_floorPanel.RenderTransform = new TranslateTransform(newX, currentPosition.Y);

            var dismissButtonPosition = m_dismissButton.RenderTransform.Transform(new Point());
            m_dismissButton.RenderTransform = new TranslateTransform(newX, dismissButtonPosition.Y);
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
            bool onScreen = false;

            if (t > 0.0f)
            {
                Visibility = Visibility.Visible;
                onScreen = true;
            }

            var storyboard = new Storyboard();
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));

            double delayMilliseconds = onScreen ? m_stateChangeAnimationTimeMilliseconds * 5 : 0.0;

            var floorPanelAnimation = new DoubleAnimation();
            floorPanelAnimation.BeginTime = TimeSpan.FromMilliseconds(delayMilliseconds);
            floorPanelAnimation.From = currentPosition.X;
            floorPanelAnimation.To = CalcPanelX(FloorSelectionEnabled ? t : 0.0f);
            floorPanelAnimation.Completed += Storyboard_Completed;
            floorPanelAnimation.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));

            var floorPanelTransform = new TranslateTransform(currentPosition.X, currentPosition.Y);
            m_floorPanel.RenderTransform = floorPanelTransform;
            floorPanelTransform.BeginAnimation(TranslateTransform.XProperty, floorPanelAnimation);

            var dismissButtonPosition = m_dismissButton.RenderTransform.Transform(new Point());
            var dismissButtonTransform = new TranslateTransform(dismissButtonPosition.X, dismissButtonPosition.Y);
            m_dismissButton.RenderTransform = dismissButtonTransform;
            floorPanelAnimation.From = dismissButtonPosition.X;
            floorPanelAnimation.To = CalcPanelX(t);
            dismissButtonTransform.BeginAnimation(TranslateTransform.XProperty, floorPanelAnimation);

            var detailsPanelAnimation = new DoubleAnimation();
            detailsPanelAnimation.From = m_detailsPanel.Opacity;
            detailsPanelAnimation.To = t;
            detailsPanelAnimation.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));

            m_detailsPanel.BeginAnimation(OpacityProperty, detailsPanelAnimation);
        }

        private void Storyboard_Completed(object sender, EventArgs e)
        {
            Visibility = m_detailsPanel.Opacity == 0.0 ? Visibility.Hidden : Visibility.Visible;

            if (m_detailsPanel.Opacity != 0.0 && m_showTutorialView)
            {
                m_tutorialView.Show();
            }
            m_showTutorialView = false;
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

        public void AddTutorialDialogs(bool showExitDialog, bool showChangeFloorDialog)
        {
            m_showTutorialView = true;
            //m_tutorialView.Show(showExitDialog, showChangeFloorDialog);
        }

        public void RemoveTutorialDialogs()
        {
            m_showTutorialView = false;
            m_tutorialView.Hide();
        }

		public bool GetCanShowChangeFloorTutorialDialog()
		{
			return FloorCount > 1;
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
