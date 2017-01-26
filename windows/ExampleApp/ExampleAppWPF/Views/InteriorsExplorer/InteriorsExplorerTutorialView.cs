using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public class InteriorsExplorerTutorialView : ButtonBase
    {
        private const int DialogGap = 20;
        private const int VerticalDialogGap = 40;

        private TutorialTooltipView m_searchMenuDialog;
        private TutorialTooltipView m_locateMeDialog;
        private TutorialTooltipView m_elevatorDialog;

        private TutorialTooltipPositionTracker m_searchMenuDialogPositioner;
        private TutorialTooltipPositionTracker m_locateMeDialogPositioner;
        private TutorialTooltipPositionTracker m_elevatorDialogPositioner;

        private Storyboard m_hideAnimation;

        static InteriorsExplorerTutorialView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(
                typeof(InteriorsExplorerTutorialView),
                new FrameworkPropertyMetadata(typeof(InteriorsExplorerTutorialView)));
        }

        public InteriorsExplorerTutorialView()
        {
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            
            MainWindow mainWindow = (MainWindow) Application.Current.MainWindow;
            mainWindow.AddHandler(UIElement.MouseLeftButtonDownEvent, (RoutedEventHandler) OnMouseLeftButtonDown, true);
            mainWindow.AddHandler(UIElement.TouchDownEvent, (RoutedEventHandler) OnMouseLeftButtonDown, true);

            m_searchMenuDialog = (TutorialTooltipView)GetTemplateChild("SearchMenuDialog");
            m_locateMeDialog = (TutorialTooltipView)GetTemplateChild("LocateMeDialog");
            m_elevatorDialog = (TutorialTooltipView)GetTemplateChild("ElevatorDialog");

            m_hideAnimation = (Storyboard)FindResource("HideAnimation");
        }

        public void OnMouseLeftButtonDown(object sender, RoutedEventArgs e)
        {
            if (IsVisible)
            {
                if (m_hideAnimation != null)
                {
                    m_hideAnimation.Seek(TimeSpan.Zero);
                    BeginStoryboard(m_hideAnimation);
                }
                else
                {
                    Hide();
                }
            }
        }

		public void Show()
		{
			Visibility = Visibility.Visible;
		}

		public void Hide()
		{
			Visibility = Visibility.Hidden;
        }

        public void SetTooltipControls(Window rootWindow, FrameworkElement searchMenuButton, FrameworkElement compassButton, FrameworkElement floorSliderButton)
        {
            m_searchMenuDialogPositioner = MakeTooltipPositioner(rootWindow, m_searchMenuDialog, searchMenuButton);
            m_searchMenuDialogPositioner.OnUpdateTransform += (x, y, w, h) =>
            {
                ((TranslateTransform)m_searchMenuDialog.RenderTransform).X = x + w + m_searchMenuDialog.GetPointHeight() + DialogGap;
                ((TranslateTransform)m_searchMenuDialog.RenderTransform).Y = y;
            };

            m_locateMeDialogPositioner = MakeTooltipPositioner(rootWindow, m_locateMeDialog, compassButton);
            m_locateMeDialogPositioner.OnUpdateTransform += (x, y, w, h) =>
            {
                ((TranslateTransform)m_locateMeDialog.RenderTransform).X = x - m_locateMeDialog.GetTooltipWidth() / 2.0 + w / 2.0;
                ((TranslateTransform)m_locateMeDialog.RenderTransform).Y = y - m_locateMeDialog.GetTooltipHeight() - VerticalDialogGap;
            };

            m_elevatorDialogPositioner = MakeTooltipPositioner(rootWindow, m_elevatorDialog, floorSliderButton);
            m_elevatorDialogPositioner.OnUpdateTransform += (x, y, w, h) =>
            {
                ((TranslateTransform)m_elevatorDialog.RenderTransform).X = x - m_elevatorDialog.GetTooltipWidth() - DialogGap;
                ((TranslateTransform)m_elevatorDialog.RenderTransform).Y = y;
            };
        }

        private TutorialTooltipPositionTracker MakeTooltipPositioner(Window rootWindow, Control tooltip, FrameworkElement element)
        {
            TutorialTooltipPositionTracker positioner = new TutorialTooltipPositionTracker(rootWindow, element);
            tooltip.RenderTransformOrigin = new Point(0.0, 0.0);
            tooltip.IsVisibleChanged += (o, e) => positioner.EnableChangeHooks(m_searchMenuDialog.IsVisible);
            tooltip.RenderTransform = new TranslateTransform();
            positioner.EnableChangeHooks(false);
            return positioner;
        }

	}
}
