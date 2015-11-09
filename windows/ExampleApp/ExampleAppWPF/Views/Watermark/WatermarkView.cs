using System;
using System.Windows;
using System.Windows.Media;
using ExampleApp;
using System.Windows.Media.Animation;
using System.Windows.Controls;
using System.Diagnostics;

namespace ExampleAppWPF
{
    class WatermarkView : Control
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;

        private int m_stateChangeAnimationTimeMilliseconds = 200;
        private double m_yPosInactive;
        private double m_yPosActive;
        private bool m_isFirstLayout = true;
        private string m_googleAnalyticsReferrerToken;

        static WatermarkView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(WatermarkView), new FrameworkPropertyMetadata(typeof(WatermarkView)));
        }

        public WatermarkView(IntPtr nativeCallerPointer, string googleAnalyticsReferrerToken)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            m_googleAnalyticsReferrerToken = googleAnalyticsReferrerToken;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);
            m_currentWindow.SizeChanged += OnLayoutChanged;
            Loaded += OnLayoutChanged;

            Opacity = 0.8;

            this.MouseDown += OnClick;
        }

        private void OnClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            var appName = AppDomain.CurrentDomain.FriendlyName;
            string message = "The " + appName.Substring(0, appName.Length - 4) + " app is opensource. It's built using the eeGeo maps SDK, a cross platform API for building engaging, customizable apps. Find out more?";
            var result = MessageBox.Show(message, "Maps by eeGeo", MessageBoxButton.YesNo);

            WatermarkCLI.OnSelected(m_nativeCallerPointer);

            if (result == MessageBoxResult.Yes)
            {
                string url = "http://eegeo.com/findoutmore?utm_source=" + m_googleAnalyticsReferrerToken + "&utm_medium=referral&utm_campaign=eegeo";
                Process.Start(new ProcessStartInfo(url));
            }
        }

        private void OnLayoutChanged(object sender, RoutedEventArgs e)
        {
            Point currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            double onScreenState = (currentPosition.Y - m_yPosInactive) / (m_yPosActive - m_yPosInactive);

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            double screenHeight = mainWindow.ActualHeight;
            double screenWidth = mainWindow.ActualWidth;
            double viewHeight = ActualHeight;
            double viewWidth = ActualWidth;
            m_yPosActive = screenHeight * 0.5 - (viewHeight * 0.5 + ConversionHelpers.AndroidToWindowsDip(16));
            m_yPosInactive = screenHeight * 0.5 + viewHeight * 0.5;
            double layoutY = m_yPosInactive;

            if (!m_isFirstLayout)
            {
                layoutY = onScreenState * (m_yPosActive - m_yPosInactive) + m_yPosInactive;
            }

            m_isFirstLayout = false;

            var transform = new TranslateTransform(
                (screenWidth * 0.5) - Width,
                layoutY);

            RenderTransform = transform;
        }

        void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void AnimateToInactive()
        {
            AnimateViewToY(m_yPosInactive);
        }

        public void AnimateToActive()
        {
            AnimateViewToY(m_yPosActive);
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
