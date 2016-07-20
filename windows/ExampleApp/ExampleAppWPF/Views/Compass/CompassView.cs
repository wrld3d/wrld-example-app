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
        private Image m_compassPoint = new Image();
        private Image m_compassInner = new Image();

        private double m_yPosActive;
        private double m_yPosInactive;
        private double m_compassPointOffsetX;
        private double m_compassPointOffsetY;

        bool m_isActive = false;

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
        }

        public override void OnApplyTemplate()
        {
            m_compassPoint = (Image)GetTemplateChild("CompassArrow");
            m_compassInner.Visibility = Visibility.Collapsed;

            m_compassInner.Width = 30.0;
            m_compassInner.Height = 30.0;
            m_compassInner.RenderTransform = new TranslateTransform((Width - m_compassInner.Width) * 0.5, (Height - m_compassInner.Height) * 0.5);

            var canvas = (Canvas)GetTemplateChild("ImageCanvas");
            canvas.Children.Add(m_compassInner);
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

            double pointWidth = m_compassPoint.Width;
            double pointHeight = m_compassPoint.Height;

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
            float verticalPointOffsetPx = ((float)m_compassPoint.Height * 0.5f) + 7.0f;
            float theta = -headingAngleRadians;
            float sinTheta = (float)Math.Sin(theta);
            float cosTheta = (float)Math.Cos(theta);
            float x = (float)(-m_compassPoint.Width * 0.5);
            float y = (float)ConversionHelpers.AndroidToWindowsDip(-verticalPointOffsetPx);
            float newX = x * cosTheta - y * sinTheta;
            float newY = y * cosTheta + x * sinTheta;

            var translateTransform = new TranslateTransform(
                m_compassPointOffsetX + newX,
                m_compassPointOffsetY + newY);

            var rotateTransform = new RotateTransform(
                -headingAngleRadians * 180 / Math.PI);

            var transformGroup = new TransformGroup();
            transformGroup.Children.Add(rotateTransform);
            transformGroup.Children.Add(translateTransform);
            
            m_compassPoint.RenderTransform = transformGroup;
            m_compassPoint.Visibility = Visibility.Visible;
        }

        public void ShowGpsDisabledView()
        {
            m_compassInner.Visibility = Visibility.Collapsed;
        }

        public void ShowGpsFollowView()
        {
            m_compassInner.Visibility = Visibility.Visible;
            CreateBitmap(false);
        }

        public void ShowGpsCompassModeView()
        {
            m_compassInner.Visibility = Visibility.Visible;
            CreateBitmap(true);
        }

        public void NotifyGpsUnauthorized()
        {
            MessageBox.Show(
                "GPS Compass inaccessible: Location Services are not enabled for this application. You can change this in your device settings.",
                "Location Services disabled",
                MessageBoxButton.OK);
        }

        private void GetScreenDpi(out double dpiX, out double dpiY)
        {
            dpiX = 96.0;
            dpiY = 96.0;

            var source = PresentationSource.FromVisual(this);

            if (source != null)
            {
                dpiX *= source.CompositionTarget.TransformFromDevice.M11;
                dpiY *= source.CompositionTarget.TransformFromDevice.M22;
            }
        }

        private void CreateBitmap(bool filled)
        {
            double innerDiameter = m_compassInner.Width;
            var circle = new Ellipse();
            circle.Width = innerDiameter/2;
            circle.Height = innerDiameter/2;
            circle.Fill = filled ? Brushes.White : Brushes.Transparent;
            circle.Stroke = filled ? Brushes.Transparent : Brushes.White;

            double dpiX, dpiY;
            GetScreenDpi(out dpiX, out dpiY);
            var bitmap = new RenderTargetBitmap((int)innerDiameter, (int)innerDiameter,
                dpiX, dpiY, PixelFormats.Pbgra32);
            circle.Arrange(new Rect(new Size(innerDiameter, innerDiameter)));
            bitmap.Render(circle);
            m_compassInner.Source = bitmap;
            m_compassInner.InvalidateVisual();
        }
    }
}
