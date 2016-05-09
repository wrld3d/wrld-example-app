using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;

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

        static MyPinCreationConfirmationView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(MyPinCreationConfirmationView), new FrameworkPropertyMetadata(typeof(MyPinCreationConfirmationView)));
        }

        public MyPinCreationConfirmationView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            m_active = false;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            m_currentWindow.SizeChanged += UpdatePositionOnWindowResize;

            m_yPosActive = 0.0f;
            m_yPosInactive = Height;

            Visibility = Visibility.Hidden;
        }

        private void UpdatePositionOnWindowResize(object sender, SizeChangedEventArgs e)
        {
            m_yPosActive = 0.0f;
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
            m_acceptButton = GetTemplateChild("Ok") as Button;
            System.Diagnostics.Debug.Assert(m_acceptButton != null, "Ok Image not found in generic.xaml template");

            m_closeButton = GetTemplateChild("Close") as Button;
            System.Diagnostics.Debug.Assert(m_closeButton != null, "Close Image not found in generic.xaml template");

            m_acceptButton.Click += OnAcceptClicked;

            m_closeButton.Click += OnCloseClicked;
        }

        private void OnAcceptClicked(object sender, RoutedEventArgs e)
        {
            ExampleApp.MyPinCreationViewCLIMethods.ConfirmationOkButtonPressed(m_nativeCallerPointer);
        }

        private void OnCloseClicked(object sender, RoutedEventArgs e)
        {
            ExampleApp.MyPinCreationViewCLIMethods.ConfirmationCancelButtonPressed(m_nativeCallerPointer);
        }

        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void AnimateToInactive()
        {
            AnimateViewToY(m_yPosInactive);
            m_active = false;
        }

        public void AnimateToActive()
        {
            AnimateViewToY(m_yPosActive);
            Visibility = Visibility.Visible;
            m_active = true;
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
