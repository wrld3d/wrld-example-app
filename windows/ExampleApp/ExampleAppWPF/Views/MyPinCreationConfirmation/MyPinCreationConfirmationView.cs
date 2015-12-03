using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ExampleAppWPF
{
    public class MyPinCreationConfirmationView : Control
    {
        private IntPtr m_nativeCallerPointer;

        private double m_yPosActive;
        private double m_yPosInactive;
        private bool m_active;
        private double m_stateChangeAnimationTimeMilliseconds = 200;

        private Image m_acceptButton;
        private BitmapImage m_acceptButtonDown;
        private BitmapImage m_acceptButtonUp;
        private bool m_isAcceptButtonMouseDown = false;

        private Image m_closeButton;
        private BitmapImage m_closeButtonDown;
        private BitmapImage m_closeButtonUp;
        private bool m_isCloseButtonMouseDown = false;

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

            m_yPosActive = (m_currentWindow.Height * 0.5) - Height;
            m_yPosInactive = (m_currentWindow.Height * 0.5) + Height;

            Visibility = Visibility.Hidden;
        }

        private void UpdatePositionOnWindowResize(object sender, SizeChangedEventArgs e)
        {
            m_yPosActive = (e.NewSize.Height * 0.5) - Height;
            m_yPosInactive = (e.NewSize.Height * 0.5) + Height;

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
            m_acceptButton = GetTemplateChild("Ok") as Image;
            System.Diagnostics.Debug.Assert(m_acceptButton != null, "Ok Image not found in generic.xaml template");

            m_closeButton = GetTemplateChild("Close") as Image;
            System.Diagnostics.Debug.Assert(m_closeButton != null, "Close Image not found in generic.xaml template");

            m_acceptButton.MouseLeftButtonDown += OnAcceptClicked;
            m_acceptButton.MouseLeftButtonUp += OnAcceptRelease;
            m_acceptButton.MouseLeave += OnAcceptMouseLeave;
            m_acceptButtonUp = new BitmapImage(ViewHelpers.MakeUriForImage("button_ok_place_pin_off.png"));
            m_acceptButtonDown = new BitmapImage(ViewHelpers.MakeUriForImage("button_ok_place_pin_on.png"));

            m_closeButton.MouseLeftButtonDown += OnCloseClicked;
            m_closeButton.MouseLeftButtonUp += OnCloseRelease;
            m_closeButton.MouseLeave += OnCloseMouseLeave;
            m_closeButtonUp = new BitmapImage(ViewHelpers.MakeUriForImage("button_close_place_pin_off.png"));
            m_closeButtonDown = new BitmapImage(ViewHelpers.MakeUriForImage("button_close_place_pin_on.png"));
        }

        private void OnAcceptClicked(object sender, MouseButtonEventArgs e)
        {
            m_isAcceptButtonMouseDown = true;
            m_acceptButton.Source = m_acceptButtonDown;
        }

        private void OnAcceptMouseLeave(object sender, MouseEventArgs e)
        {
            if(m_isAcceptButtonMouseDown)
            {
                m_acceptButton.Source = m_acceptButtonUp;
            }

            m_isAcceptButtonMouseDown = false;
        }

        private void OnAcceptRelease(object sender, MouseButtonEventArgs e)
        {
            if(m_isAcceptButtonMouseDown)
            {
                ExampleApp.MyPinCreationViewCLIMethods.ConfirmationOkButtonPressed(m_nativeCallerPointer);
                m_acceptButton.Source = m_acceptButtonUp;
            }

            m_isAcceptButtonMouseDown = false;
        }

        private void OnCloseClicked(object sender, MouseButtonEventArgs e)
        {
            m_isCloseButtonMouseDown = true;
            m_closeButton.Source = m_closeButtonDown;
        }

        private void OnCloseRelease(object sender, MouseButtonEventArgs e)
        {
            if (m_isCloseButtonMouseDown)
            {
                ExampleApp.MyPinCreationViewCLIMethods.ConfirmationCancelButtonPressed(m_nativeCallerPointer);
                m_closeButton.Source = m_closeButtonUp;
            }

            m_isCloseButtonMouseDown = false;
        }

        private void OnCloseMouseLeave(object sender, MouseEventArgs e)
        {
            if(m_isCloseButtonMouseDown)
            {
                m_closeButton.Source = m_closeButtonUp;
            }

            m_isCloseButtonMouseDown = false;
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
