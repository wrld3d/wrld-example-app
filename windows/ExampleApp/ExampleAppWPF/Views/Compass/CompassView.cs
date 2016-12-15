using ExampleApp;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace ExampleAppWPF
{   
    public class CompassView : ButtonBase
    {
        private IntPtr m_nativeCallerPointer;
        private double m_stateChangeAnimationTimeMilliseconds = 200;
        private Image m_compassNew = new Image();
        private Image m_compassNewLocate = new Image();
        private Image m_compassNewLocked = new Image();
        private Image m_compassNewUnlocked = new Image();

        private double m_yPosActive;
        private double m_yPosInactive;
        private double m_compassPointOffsetX;
        private double m_compassPointOffsetY;

        bool m_isActive = false;

        private WindowInteractionTouchHandler m_touchHandler;
        static CompassView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(CompassView), new FrameworkPropertyMetadata(typeof(CompassView)));
        }

        public CompassView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            
            Click += CompassView_Click;
            Loaded += PerformLayout;

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged += PerformLayout;
            mainWindow.MainGrid.Children.Add(this);
            ShowGpsDisabledView();
            m_touchHandler = new WindowInteractionTouchHandler(this, false, true, true);
        }

        public override void OnApplyTemplate()
        {
            m_compassNew = (Image)GetTemplateChild("CompassNew");
            m_compassNewLocate = (Image)GetTemplateChild("CompassNewLocate");
            m_compassNewLocked = (Image)GetTemplateChild("CompassNewLocked");
            m_compassNewUnlocked = (Image)GetTemplateChild("CompassNewUnlocked");

            m_compassNewLocate.RenderTransform = new TranslateTransform((m_compassNew.Width - m_compassNewLocate.Width)/2, (m_compassNew.Width - m_compassNewLocate.Height)/2);
            m_compassNewLocked.RenderTransform = new TranslateTransform((m_compassNew.Width - m_compassNewLocked.Width) / 2, (m_compassNew.Width - m_compassNewLocked.Height) / 2);
            m_compassNewUnlocked.RenderTransform = new TranslateTransform((m_compassNew.Width - m_compassNewUnlocked.Width) / 2, (m_compassNew.Width - m_compassNewUnlocked.Height) / 2);

            var canvas = (Canvas)GetTemplateChild("ImageCanvas");
        }

        private void CompassView_Click(object sender, RoutedEventArgs e)
        {
            CompassViewCLIMethods.HandleClick(m_nativeCallerPointer);
        }

        private void PerformLayout(object sender, RoutedEventArgs e)
        {
            Point currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            double screenHeight = mainWindow.MainGrid.ActualHeight;
            double screenWidth = mainWindow.MainGrid.ActualWidth;

            double viewHeight = ActualHeight;
            double viewWidth = ActualWidth;

            m_compassPointOffsetX = (viewWidth) * 0.5;
            m_compassPointOffsetY = (viewHeight) * 0.5;

            const double margin = 23.0;
            m_yPosActive = screenHeight * 0.5 - (viewHeight * 0.5) - (margin);
            m_yPosInactive = screenHeight * 0.5 + viewHeight * 0.5;

            var transform = new TranslateTransform(currentPosition.X, m_isActive ? m_yPosActive : m_yPosInactive);

            RenderTransform = transform;
        }
        
        public void Destroy()
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged -= PerformLayout;
            mainWindow.MainGrid.Children.Remove(this);
        }

        public void AnimateToInactive()
        {
            AnimateViewToY(m_yPosInactive);
            m_isActive = false;
        }

        public void AnimateToActive()
        {
            AnimateViewToY(m_yPosActive);
            m_isActive = true;
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


        public void UpdateHeading(float headingAngleRadians)
        {
            float verticalPointOffsetPx = ((float)m_compassNew.Height * 0.5f) + 7.0f;
            float theta = -headingAngleRadians;
            float sinTheta = (float)Math.Sin(theta);
            float cosTheta = (float)Math.Cos(theta);
            float x = (float)(-m_compassNew.Width * 0.5);
            float y = (float)ConversionHelpers.AndroidToWindowsDip(-verticalPointOffsetPx);
            float newX =  cosTheta  * sinTheta;
            float newY =  cosTheta  * sinTheta;

            var translateTransform = new TranslateTransform(
            m_compassPointOffsetX + newX,
                m_compassPointOffsetY + newY);

            var rotateTransform = new RotateTransform(
                -headingAngleRadians * 180 / Math.PI, m_compassNew.Width/2, m_compassNew.Height / 2);

            var transformGroup = new TransformGroup();
            transformGroup.Children.Add(rotateTransform);
            transformGroup.Children.Add(translateTransform);
            m_compassNew.RenderTransform = transformGroup;
            m_compassNew.Visibility = Visibility.Visible;
        }

        public void ShowGpsDisabledView()
        {
            m_compassNewLocate.Visibility = Visibility.Visible;
            m_compassNewLocked.Visibility = Visibility.Hidden;
            m_compassNewUnlocked.Visibility = Visibility.Hidden;
        }

        public void ShowGpsFollowView()
        {
            m_compassNewLocate.Visibility = Visibility.Hidden;
            m_compassNewLocked.Visibility = Visibility.Visible;
            m_compassNewUnlocked.Visibility = Visibility.Hidden;
        }

        public void ShowGpsCompassModeView()
        {
            m_compassNewLocate.Visibility = Visibility.Hidden;
            m_compassNewLocked.Visibility = Visibility.Hidden;
            m_compassNewUnlocked.Visibility = Visibility.Visible;
        }

        public void NotifyGpsUnauthorized()
        {
            MessageBox.Show(
                "GPS Compass inaccessible: Location Services are not enabled for this application. You can change this in your device settings.",
                "Location Services disabled",
                MessageBoxButton.OK);
        }
    }
}
