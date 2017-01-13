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
        private static Point Origin = new Point(0.0, 0.0);
        private static double StateChangeAnimationTimeMilliseconds = 200;

        private IntPtr m_nativeCallerPointer;

        private TimeSpan m_currentRenderArgsRenderingTime = TimeSpan.Zero;

        private Image m_compassNew = new Image();
        private Image m_compassNewLocate = new Image();
        private Image m_compassNewLocked = new Image();
        private Image m_compassNewUnlocked = new Image();

        private double m_compassPointOffsetX;
        private double m_compassPointOffsetY;
        private double m_currentHeading;
        private bool m_orientationDirty = true;
        private TranslateTransform m_translateTransform = new TranslateTransform();
        private RotateTransform m_rotateTransform = new RotateTransform();

        private double m_yPosActive;
        private double m_yPosInactive;
        private TranslateTransform m_positionTransform = new TranslateTransform();

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
            CompositionTarget.Rendering += CompositionTarget_Rendering;

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged += PerformLayout;
            mainWindow.MainGrid.Children.Add(this);
            ShowGpsDisabledView();
            m_touchHandler = new WindowInteractionTouchHandler(this, false, true, true);
        }

        public override void OnApplyTemplate()
        {
            m_compassNew = (Image)GetTemplateChild("CompassNew");
            InitialiseTransforms();

            m_compassNewLocate = (Image)GetTemplateChild("CompassNewLocate");
            m_compassNewLocked = (Image)GetTemplateChild("CompassNewLocked");
            m_compassNewUnlocked = (Image)GetTemplateChild("CompassNewUnlocked");

            m_compassNewLocate.RenderTransform = new TranslateTransform((m_compassNew.Width - m_compassNewLocate.Width)/2, (m_compassNew.Width - m_compassNewLocate.Height)/2);
            m_compassNewLocked.RenderTransform = new TranslateTransform((m_compassNew.Width - m_compassNewLocked.Width) / 2, (m_compassNew.Width - m_compassNewLocked.Height) / 2);
            m_compassNewUnlocked.RenderTransform = new TranslateTransform((m_compassNew.Width - m_compassNewUnlocked.Width) / 2, (m_compassNew.Width - m_compassNewUnlocked.Height) / 2);

            var canvas = (Canvas)GetTemplateChild("ImageCanvas");

            RenderTransform = m_positionTransform;
        }

        private void CompassView_Click(object sender, RoutedEventArgs e)
        {
            CompassViewCLIMethods.HandleClick(m_nativeCallerPointer);
        }

        private void PerformLayout(object sender, RoutedEventArgs e)
        {
            Point currentPosition = RenderTransform.Transform(Origin);

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            double screenHeight = mainWindow.MainGrid.ActualHeight;
            double screenWidth = mainWindow.MainGrid.ActualWidth;

            double viewHeight = ActualHeight;
            double viewWidth = ActualWidth;

            m_compassPointOffsetX = viewWidth * 0.5;
            m_compassPointOffsetY = viewHeight * 0.5;

            const double margin = 23.0;
            m_yPosActive = screenHeight * 0.5 - (viewHeight * 0.5) - margin;
            m_yPosInactive = screenHeight * 0.5 + viewHeight * 0.5;

            UpdatePositionTransform(currentPosition.X, m_isActive ? m_yPosActive : m_yPosInactive);
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
            var currentPosition = RenderTransform.Transform(Origin);
            var animation = new DoubleAnimation();
            animation.From = currentPosition.Y;
            animation.To = y;
            animation.Duration = new Duration(TimeSpan.FromMilliseconds(StateChangeAnimationTimeMilliseconds));
            animation.EasingFunction = new SineEase();

            UpdatePositionTransform(currentPosition.X, currentPosition.Y);
            m_positionTransform.BeginAnimation(TranslateTransform.YProperty, animation);
        }

        public void AnimateToIntermediateOnScreenState(float onScreenState)
        {
            Point currentPosition = RenderTransform.Transform(Origin);
            double viewY = currentPosition.Y;
            double newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;

            if (viewY != newY)
            {
                UpdatePositionTransform(currentPosition.X, newY);
                InvalidatePositionTransform();
            }
        }

        public void UpdateHeading(float headingAngleRadians)
        {
            m_orientationDirty = m_currentHeading != headingAngleRadians;
            m_currentHeading = headingAngleRadians;
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

        private void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            RenderingEventArgs renderArgs = (RenderingEventArgs)e;
            if (m_currentRenderArgsRenderingTime == renderArgs.RenderingTime)
            {
                return;
            }
            m_currentRenderArgsRenderingTime = renderArgs.RenderingTime;

            UpdateOrientationTransform((float)m_currentHeading);
            InvalidateTransforms();
        }

        private void InvalidateTransforms()
        {
            InvalidatePositionTransform();
            InvalidOrientationTransform();
        }

        private void InvalidatePositionTransform()
        {
            m_positionTransform.InvalidateProperty(TranslateTransform.XProperty);
            m_positionTransform.InvalidateProperty(TranslateTransform.YProperty);
        }

        private void InvalidOrientationTransform()
        {
            m_translateTransform.InvalidateProperty(TranslateTransform.XProperty);
            m_translateTransform.InvalidateProperty(TranslateTransform.YProperty);

            m_rotateTransform.InvalidateProperty(RotateTransform.AngleProperty);
            m_rotateTransform.InvalidateProperty(RotateTransform.CenterXProperty);
            m_rotateTransform.InvalidateProperty(RotateTransform.CenterYProperty);
        }

        private void UpdatePositionTransform(double x, double y)
        {
            m_positionTransform.X = x;
            m_positionTransform.Y = y;
        }

        private void UpdateOrientationTransform(float headingAngleRadians)
        {
            float verticalPointOffsetPx = ((float)m_compassNew.Height * 0.5f) + 7.0f;
            float theta = -headingAngleRadians;
            float sinTheta = (float)Math.Sin(theta);
            float cosTheta = (float)Math.Cos(theta);
            float x = (float)(-m_compassNew.Width * 0.5);
            float y = (float)ConversionHelpers.AndroidToWindowsDip(-verticalPointOffsetPx);
            float newX = cosTheta * sinTheta;
            float newY = cosTheta * sinTheta;

            m_translateTransform.X = m_compassPointOffsetX + newX;
            m_translateTransform.Y = m_compassPointOffsetY + newY;

            m_rotateTransform.CenterX = m_compassNew.Width / 2;
            m_rotateTransform.CenterY = m_compassNew.Height / 2;
            m_rotateTransform.Angle = -headingAngleRadians * 180 / Math.PI;
        }

        private void InitialiseTransforms()
        {
            var transformGroup = new TransformGroup();
            UpdateOrientationTransform(0.0f);

            transformGroup.Children.Add(m_rotateTransform);
            transformGroup.Children.Add(m_translateTransform);
            m_compassNew.RenderTransform = transformGroup;
            m_compassNew.Visibility = Visibility.Visible;
        }
    }
}
