using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Threading;

namespace ExampleAppWPF
{
    public class MyPinCreationConfirmationView : ControlBase
    {
        private IntPtr m_nativeCallerPointer;

        private double m_yPosActive;
        private double m_yPosInactive;
        private bool m_active;
        private double m_stateChangeAnimationTimeMilliseconds = 200;

        private Button m_acceptButton;
        private Button m_closeButton;

        private MainWindow m_currentWindow;

        private MyPinCreationConfirmationTutorialDialogBox m_tutorialDialogBox;
        private Button m_tutorialAcceptButton;
        private Button m_tutorialCancelButton;
        private int m_tutorialViewCount = 0;

        private bool m_isInKioskMode;

        static MyPinCreationConfirmationView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(MyPinCreationConfirmationView), new FrameworkPropertyMetadata(typeof(MyPinCreationConfirmationView)));
        }

        public MyPinCreationConfirmationView(IntPtr nativeCallerPointer, bool isInKioskMode)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            m_isInKioskMode = isInKioskMode;
            m_active = false;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            m_currentWindow.SizeChanged += UpdatePositionOnWindowResize;

            m_yPosInactive = Height;

            Visibility = Visibility.Hidden;
        }

        private void UpdatePositionOnWindowResize(object sender, SizeChangedEventArgs e)
        {
            m_yPosInactive = Height;

            if(m_active)
            {
                AnimateToActive();
            }
            else
            {
                Visibility = Visibility.Hidden;
                AnimateToInactive();
            }
        }

        public override void OnApplyTemplate()
        {
            m_yPosActive = -((double)Application.Current.Resources["PinCreationConfirmationBottomMargin"]);

            m_acceptButton = GetTemplateChild(m_isInKioskMode ? "OkKiosk" : "Ok") as Button;
            System.Diagnostics.Debug.Assert(m_acceptButton != null, "Ok Image not found in generic.xaml template");

            m_closeButton = GetTemplateChild(m_isInKioskMode ? "CloseKiosk" : "Close") as Button;
            System.Diagnostics.Debug.Assert(m_closeButton != null, "Close Image not found in generic.xaml template");

            m_acceptButton.Click += OnAcceptClicked;

            m_closeButton.Click += OnCloseClicked;
        }

        private void OnAcceptClicked(object sender, RoutedEventArgs e)
        {
            IsEnabled = false;
            ExampleApp.MyPinCreationViewCLIMethods.ConfirmationOkButtonPressed(m_nativeCallerPointer);
        }

        private void OnCloseClicked(object sender, RoutedEventArgs e)
        {
            IsEnabled = false;
            ExampleApp.MyPinCreationViewCLIMethods.ConfirmationCancelButtonPressed(m_nativeCallerPointer);
        }

        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);

            RemoveTutorialDialog();
        }
        
        private void ShowTutorialDialog()
        {
            m_tutorialDialogBox = new MyPinCreationConfirmationTutorialDialogBox("Create Pin", "Please use this feature to create a pin.", "Create Pin");
            m_tutorialDialogBox.Owner = m_currentWindow;
            m_tutorialDialogBox.Show();

            m_tutorialAcceptButton = (Button)m_tutorialDialogBox.FindName("AcceptButton");
            m_tutorialAcceptButton.Click += AcceptTutorialDialog;

            m_tutorialCancelButton = (Button)m_tutorialDialogBox.FindName("CancelButton");
            m_tutorialCancelButton.Click += CancelTutorialDialog;
        }

        private void CancelTutorialDialog(object sender, EventArgs e)
        {
            ExampleApp.MyPinCreationViewCLIMethods.ConfirmationCancelButtonPressed(m_nativeCallerPointer);

            RemoveTutorialDialog();
        }

        private void AcceptTutorialDialog(object sender, EventArgs e)
        {
            AnimateToActive();

            RemoveTutorialDialog();
        }

        private void RemoveTutorialDialog()
        {
            if(m_tutorialAcceptButton != null)
            {
                m_tutorialAcceptButton.Click -= AcceptTutorialDialog;
                m_tutorialAcceptButton = null;
            }

            if(m_tutorialCancelButton != null)
            {
                m_tutorialCancelButton.Click -= CancelTutorialDialog;
                m_tutorialCancelButton = null;
            }

            if(m_tutorialDialogBox != null)
            {
                m_tutorialDialogBox.Close();
                m_tutorialDialogBox = null;
            }
        }

        public void ResetTutorialViewCount()
        {
            m_tutorialViewCount = 0;
        }

        public void AnimateToInactive()
        {
            AnimateViewToY(m_yPosInactive);
            m_active = false;

            RemoveTutorialDialog();
        }

        public void AnimateToActive()
        {
            if(m_isInKioskMode && !m_active && m_tutorialViewCount == 0)
            {
                ++m_tutorialViewCount;
                ShowTutorialDialog();
            }
            else
            {
                AnimateViewToY(m_yPosActive);
                Visibility = Visibility.Visible;
            }

            m_active = true;

            IsEnabled = true;
        }

        public void AnimateViewToY(double y)
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            var animation = new DoubleAnimation();
            animation.From = currentPosition.Y;
            animation.To = y;
            animation.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));
            animation.EasingFunction = new SineEase();

            var transform = new TranslateTransform(currentPosition.X, currentPosition.Y);
            RenderTransform = transform;
            transform.BeginAnimation(TranslateTransform.YProperty, animation);
        }

        public void AnimateToIntermediateOnScreenState(float onScreenState)
        {
            Point currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            double viewY = currentPosition.Y;
            double newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;

            if (viewY != newY)
            {
                RenderTransform = new TranslateTransform(currentPosition.X, newY);
            }
        }
    }
}
