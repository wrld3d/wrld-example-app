using ExampleApp;
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

                    InitialExperienceIntroCLIMethods.HandleClick(m_nativeCallerPointer);
                }
            }
            else
            {
                Visibility = Visibility.Hidden;
            }
        }
    }
}
