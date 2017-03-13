using System;
using System.Collections.Generic;
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

        private Dictionary<string, PositionedDialog> m_dialogs = new Dictionary<string, PositionedDialog>();
        private Dictionary<string, TutorialTooltipPositionTracker> m_positioners = new Dictionary<string, TutorialTooltipPositionTracker>();

        private Storyboard m_showAnimation;
        private bool m_hideAnimationRunning;
        private Storyboard m_hideAnimation;

        private readonly string SearchMenuDialogName = "SearchMenuDialog";
        private readonly string LocateMeDialogName = "LocateMeDialog";
        private readonly string ElevatorDialogName = "ElevatorDialog";
        private readonly string ExitDialogName = "ExitDialog";

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

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.AddHandler(UIElement.MouseLeftButtonDownEvent, (RoutedEventHandler)OnMouseLeftButtonDown, true);
            mainWindow.AddHandler(UIElement.TouchDownEvent, (RoutedEventHandler)OnMouseLeftButtonDown, true);

            TryAddDialogTemplateChild(SearchMenuDialogName,
                                      (dialog) => (x, y, w, h) =>
                                      {
                                          ((TranslateTransform)dialog.RenderTransform).X = x + w + dialog.ArrowPointHeight + DialogGap;
                                          ((TranslateTransform)dialog.RenderTransform).Y = y;
                                      });

            TryAddDialogTemplateChild(LocateMeDialogName,
                                      (dialog) => (x, y, w, h) =>
                                      {
                                          ((TranslateTransform)dialog.RenderTransform).X = x - dialog.GetTooltipWidth() / 2.0 + w / 2.0;
                                          ((TranslateTransform)dialog.RenderTransform).Y = y - dialog.GetTooltipHeight() - VerticalDialogGap;
                                      });

            TryAddDialogTemplateChild(ElevatorDialogName,
                                      (dialog) => (x, y, w, h) =>
                                      {
                                          ((TranslateTransform)dialog.RenderTransform).X = x - dialog.GetTooltipWidth() - DialogGap;
                                          ((TranslateTransform)dialog.RenderTransform).Y = y;
                                      });

            TryAddDialogTemplateChild(ExitDialogName,
                                      (dialog) => (x, y, w, h) =>
                                      {
                                          ((TranslateTransform)dialog.RenderTransform).X = x - dialog.GetTooltipWidth() - DialogGap;
                                          ((TranslateTransform)dialog.RenderTransform).Y = y;
                                      });

            m_showAnimation = (Storyboard)FindResource("ShowAnimation");
            m_hideAnimation = ((Storyboard)FindResource("HideAnimation")).Clone();
            m_hideAnimation.Completed += (o, e) =>
            {
                m_hideAnimationRunning = false;
                Visibility = Visibility.Hidden;
            };
        }

        public void OnMouseLeftButtonDown(object sender, RoutedEventArgs e)
        {
            if (IsVisible)
            {
                Hide();
            }
        }

        public void Show(bool showExitTutorial, bool showChangeFloorTutorial)
        {
            PositionedDialog dialog;
            if (m_dialogs.TryGetValue(ElevatorDialogName, out dialog))
            {
                dialog.Dialog.IsEnabled = showChangeFloorTutorial;
            }

            if (m_dialogs.TryGetValue(ExitDialogName, out dialog))
            {
                dialog.Dialog.IsEnabled = showExitTutorial;
            }

            SetDialogsVisibile(true);
            UpdateDialogPositions();

            Visibility = Visibility.Visible;
            m_showAnimation?.Seek(TimeSpan.Zero);
            m_showAnimation?.Begin(this);
        }

		public void Hide()
		{
            if (m_hideAnimation != null)
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
                SetDialogsVisibile(false);
                Visibility = Visibility.Hidden;
            }
        }

        public void SetTooltipControls(Window rootWindow, FrameworkElement searchMenuButton, FrameworkElement compassButton, FrameworkElement floorSliderButton, FrameworkElement exitButton)
        {
            Dictionary<string, FrameworkElement> elementForDialog = new Dictionary<string, FrameworkElement>
            {
                { SearchMenuDialogName, searchMenuButton },
                { LocateMeDialogName, compassButton },
                { ElevatorDialogName, floorSliderButton },
                { ExitDialogName, exitButton }
            };

            foreach (var dialog in m_dialogs)
            {
                TutorialTooltipPositionTracker positioner = MakeTooltipPositioner(rootWindow, dialog.Value.Dialog, elementForDialog[dialog.Key]);
                positioner.OnUpdateTransform += dialog.Value.DialogPosition;
                m_positioners.Add(dialog.Key, positioner);
            }
        }

        private TutorialTooltipPositionTracker MakeTooltipPositioner(Window rootWindow, Control tooltip, FrameworkElement element)
        {
            TutorialTooltipPositionTracker positioner = new TutorialTooltipPositionTracker(rootWindow, element);
            tooltip.RenderTransformOrigin = new Point(0.0, 0.0);
            tooltip.IsVisibleChanged += (o, e) => positioner.EnableChangeHooks(element.IsVisible);
            tooltip.RenderTransform = new TranslateTransform();
            return positioner;
        }

        private void UpdateDialogPositions()
        {
            foreach (var positioner in m_positioners.Values)
            {
                positioner.UpdateTransform();
            }
        }

        private void SetDialogsVisibile(bool visible)
        {
            foreach (var dialog in m_dialogs.Values)
            {
                dialog.Dialog.Visibility = visible && dialog.Dialog.IsEnabled ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private TutorialTooltipView GetEnabledTemplateChild(string xamlId)
        {
            TutorialTooltipView child = (TutorialTooltipView)GetTemplateChild(xamlId);
            if (child.IsEnabled)
            {
                return child;
            }
            else
            {
                child.Visibility = Visibility.Collapsed;
                return null;
            }
        }

        private TutorialTooltipView TryAddDialogTemplateChild(string xamlId, Func<TutorialTooltipView, TutorialTooltipPositionTracker.OnUpdateTransformEvent> positionDialog)
        {
            TutorialTooltipView dialog = GetEnabledTemplateChild(xamlId);
            if (dialog != null)
            {
                m_dialogs.Add(xamlId, new PositionedDialog(dialog, positionDialog(dialog)));
            }
            return dialog;
        }
	}
}
