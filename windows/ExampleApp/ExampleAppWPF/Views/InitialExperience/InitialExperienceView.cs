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

        private readonly string DropPinDialogName = "DropPinDialog";
        private PositionedDialog m_positionedDropPinDialog;
        private TutorialTooltipPositionTracker m_dropPinPositionTracker;

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

            TutorialTooltipView dropPinDialog = (TutorialTooltipView)GetTemplateChild(DropPinDialogName);
            m_positionedDropPinDialog = new PositionedDialog(dropPinDialog, (x, y, w, h) =>
            {
                ((TranslateTransform)dropPinDialog.RenderTransform).X = x + w + dropPinDialog.ArrowPointHeight + DialogGap;
                ((TranslateTransform)dropPinDialog.RenderTransform).Y = y - (dropPinDialog.GetTooltipHeight() - h) - 2;
            });

            MyPinCreationButtonView myPinCreationButtonView = ViewHelpers.FindChildrenOfType<MyPinCreationButtonView>(m_mainWindow.MainGrid.Children).Single();
            m_dropPinPositionTracker = new TutorialTooltipPositionTracker(m_mainWindow, myPinCreationButtonView);
            m_dropPinPositionTracker.OnUpdateTransform += m_positionedDropPinDialog.DialogPosition;
            dropPinDialog.RenderTransformOrigin = new Point(0.0, 0.0);
            dropPinDialog.RenderTransform = new TranslateTransform();

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
