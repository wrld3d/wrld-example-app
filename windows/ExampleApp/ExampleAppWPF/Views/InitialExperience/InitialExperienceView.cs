using System;
using System.Linq;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public class InitialExperienceView : ControlBase
    {
        private struct PositionedDialog
        {
            public PositionedDialog(TutorialTooltipView dialog, TutorialTooltipPositionTracker.OnUpdateTransformEvent dialogPosition)
            {
                Dialog = dialog;
                DialogPosition = dialogPosition;
            }

            public TutorialTooltipView Dialog;
            public TutorialTooltipPositionTracker.OnUpdateTransformEvent DialogPosition;
        };

        private const int DialogGap = 20;

        private IntPtr m_nativeCallerPointer;

        private MainWindow m_mainWindow;

        private readonly string MapModeDialogName = "MapModeDialog";
        private PositionedDialog m_positionedMapModeDialog;
        private TutorialTooltipPositionTracker m_mapModePositionTracker;

        private readonly string CreateReportDialogName = "CreateReportDialog";
        private PositionedDialog m_positionedCreateReportDialog;
        private TutorialTooltipPositionTracker m_createReportPositionTracker;

        private Storyboard m_showAnimation;
        private bool m_hideAnimationRunning;
        private Storyboard m_hideAnimation;

        static InitialExperienceView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(InitialExperienceView), new FrameworkPropertyMetadata(typeof(InitialExperienceView)));
        }

        public InitialExperienceView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_mainWindow = (MainWindow)Application.Current.MainWindow;
            m_mainWindow.AddHandler(UIElement.MouseLeftButtonDownEvent, (RoutedEventHandler)OnMouseLeftButtonDown, true);
            m_mainWindow.AddHandler(UIElement.TouchDownEvent, (RoutedEventHandler)OnMouseLeftButtonDown, true);
            m_mainWindow.MainGrid.Children.Add(this);

            DismissExitIUX();
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            TutorialTooltipView mapModeDialog = (TutorialTooltipView)GetTemplateChild(MapModeDialogName);
            m_positionedMapModeDialog = new PositionedDialog(mapModeDialog, (x, y, w, h) =>
            {
                ((TranslateTransform)mapModeDialog.RenderTransform).X = x - mapModeDialog.GetTooltipWidth() - DialogGap;
                ((TranslateTransform)mapModeDialog.RenderTransform).Y = y + 2;
            });

            FlattenButtonView flattenButtonView = ViewHelpers.FindChildrenOfType<FlattenButtonView>(m_mainWindow.MainGrid.Children).Single();
            m_mapModePositionTracker = new TutorialTooltipPositionTracker(m_mainWindow, flattenButtonView);
            m_mapModePositionTracker.OnUpdateTransform += m_positionedMapModeDialog.DialogPosition;
            mapModeDialog.RenderTransformOrigin = new Point(0.0, 0.0);
            mapModeDialog.RenderTransform = new TranslateTransform();

            TutorialTooltipView createReportDialog = (TutorialTooltipView)GetTemplateChild(CreateReportDialogName);
            m_positionedCreateReportDialog = new PositionedDialog(createReportDialog, (x, y, w, h) =>
            {
                ((TranslateTransform)createReportDialog.RenderTransform).X = x + w + createReportDialog.ArrowPointHeight + DialogGap;
                ((TranslateTransform)createReportDialog.RenderTransform).Y = y - (createReportDialog.GetTooltipHeight() - h) - 2;
            });

            MyPinCreationButtonView myPinCreationButtonView = ViewHelpers.FindChildrenOfType<MyPinCreationButtonView>(m_mainWindow.MainGrid.Children).Single();
            m_createReportPositionTracker = new TutorialTooltipPositionTracker(m_mainWindow, myPinCreationButtonView);
            m_createReportPositionTracker.OnUpdateTransform += m_positionedCreateReportDialog.DialogPosition;
            createReportDialog.RenderTransformOrigin = new Point(0.0, 0.0);
            createReportDialog.RenderTransform = new TranslateTransform();

            m_showAnimation = (Storyboard)FindResource("ShowAnimation");
            m_hideAnimation = ((Storyboard)FindResource("HideAnimation")).Clone();
            m_hideAnimation.Completed += (o, e) =>
            {
                m_hideAnimationRunning = false;
                Visibility = Visibility.Hidden;
            };
        }

        public void Destroy()
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            if (mainWindow != null)
            {
                mainWindow.MainGrid.Children.Remove(this);
            }
        }

        public void OnMouseLeftButtonDown(object sender, RoutedEventArgs e)
        {
            if (IsVisible)
            {
                DismissExitIUX();
            }
        }

        public void ShowExitIUX()
        {
            Visibility = Visibility.Visible;
            m_showAnimation?.Seek(TimeSpan.Zero);
            m_showAnimation?.Begin(this);
        }

        public void DismissExitIUX()
        {
            if(m_hideAnimation != null)
            {
                if (!m_hideAnimationRunning)
                {
                    m_hideAnimationRunning = true;
                    m_hideAnimation.Seek(TimeSpan.Zero);
                    m_hideAnimation.Begin(this);
                }
            }
            else
            {
                Visibility = Visibility.Hidden;
            }
        }
    }
}
