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
        private TranslateTransform m_translateTransform = new TranslateTransform();
        private RotateTransform m_rotateTransform = new RotateTransform();
        private RotateTransform m_compassLockedRotateTransform = new RotateTransform();

        private double m_yPosActive;
        private double m_yPosInactive;

        bool m_isActive = false;

        private bool m_isInKioskMode = false;

        private WindowInteractionTouchHandler m_touchHandler;

        private static Duration RotationHighlightAnimationMilliseconds = new Duration(TimeSpan.FromMilliseconds(200));
        private static Duration NeedleLockRotationAnimationMilliseconds = new Duration(TimeSpan.FromMilliseconds(200));

        private const float CompassOuterShapeInactiveAlpha = 0.5f;
        private const float CompassOuterShapeActiveAlpha = 1.0f;

        static CompassView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(CompassView), new FrameworkPropertyMetadata(typeof(CompassView)));
        }

        public CompassView(IntPtr nativeCallerPointer, bool isInKioskMode)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            m_isInKioskMode = isInKioskMode;
            
            Click += CompassView_Click;
            Loaded += PerformLayout;
            CompositionTarget.Rendering += CompositionTarget_Rendering;

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged += PerformLayout;
            mainWindow.MainGrid.Children.Add(this);
            
            m_touchHandler = new WindowInteractionTouchHandler(this, false, true, true);
        }

        public override void OnApplyTemplate()
        {
            m_compassNew = (Image)GetTemplateChild("CompassNew");
            InitialiseTransforms();

            m_compassNewLocate = (Image)GetTemplateChild("CompassNewLocate");
            m_compassNewLocked = (Image)GetTemplateChild("CompassNewLocked");
            m_compassNewUnlocked = (Image)GetTemplateChild("CompassNewUnlocked");

            var compassNewLockedTransforms = new TransformGroup();
            m_compassLockedRotateTransform.CenterX = m_compassNewLocked.Width / 2;
            m_compassLockedRotateTransform.CenterY = m_compassNewLocked.Height / 2;
            compassNewLockedTransforms.Children.Add(m_compassLockedRotateTransform);
            compassNewLockedTransforms.Children.Add(new TranslateTransform((m_compassNew.Width - m_compassNewLocked.Width) / 2, (m_compassNew.Width - m_compassNewLocked.Height) / 2));
            m_compassNewLocked.RenderTransform = compassNewLockedTransforms;

            m_compassNewLocate.RenderTransform = new TranslateTransform((m_compassNew.Width - m_compassNewLocate.Width)/2, (m_compassNew.Width - m_compassNewLocate.Height)/2);
            m_compassNewUnlocked.RenderTransform = new TranslateTransform((m_compassNew.Width - m_compassNewUnlocked.Width) / 2, (m_compassNew.Width - m_compassNewUnlocked.Height) / 2);

            var canvas = (Canvas)GetTemplateChild("ImageCanvas");

            ShowGpsDisabledView();
        }

        public FrameworkElement GetCompassElement()
        {
            return m_compassNewLocate;
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

            RenderTransform = new TranslateTransform(currentPosition.X, m_isActive ? m_yPosActive : m_yPosInactive);
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

            var positionTransform = new TranslateTransform(currentPosition.X, currentPosition.Y);
            RenderTransform = positionTransform;
            positionTransform.BeginAnimation(TranslateTransform.YProperty, animation);
        }

        public void AnimateToIntermediateOnScreenState(float onScreenState)
        {
            Point currentPosition = RenderTransform.Transform(Origin);
            double viewY = currentPosition.Y;
            double newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;

            if (viewY != newY)
            {
                RenderTransform = new TranslateTransform(currentPosition.X, newY);
            }
        }

        public void UpdateHeading(float headingAngleRadians)
        {
            m_currentHeading = headingAngleRadians;
        }

        public void ShowGpsDisabledView()
        {
            if (m_isInKioskMode)
            {
                EnableKioskCompassLocateButton(true);
            }

            m_compassNewLocate.Visibility = Visibility.Visible;
            m_compassNewLocked.Visibility = Visibility.Hidden;
            m_compassNewUnlocked.Visibility = Visibility.Hidden;
        }

        public void ShowGpsFollowView()
        {
            if (m_isInKioskMode)
            {
                EnableKioskCompassLocateButton(false);
            }
            else
            {
                m_compassNewLocate.Visibility = Visibility.Hidden;
                m_compassNewLocked.Visibility = Visibility.Visible;
                m_compassNewUnlocked.Visibility = Visibility.Hidden;
            }
        }

        public void ShowGpsCompassModeView()
        {
            if(m_isInKioskMode)
            {
                EnableKioskCompassLocateButton(false);
            }
            else
            {
                m_compassNewLocate.Visibility = Visibility.Hidden;
                m_compassNewLocked.Visibility = Visibility.Hidden;
                m_compassNewUnlocked.Visibility = Visibility.Visible;
            }
        }

        public void SetRotationHighlight(bool shouldShowRotationHighlight)
        {
            m_compassNew.BeginAnimation(Image.OpacityProperty,
                                        new DoubleAnimation
                                        {
                                            To = shouldShowRotationHighlight
                                                   ? CompassOuterShapeActiveAlpha
                                                   : CompassOuterShapeInactiveAlpha,
                                            Duration = RotationHighlightAnimationMilliseconds
                                        });

            if (m_isInKioskMode)
            {
                EnableKioskCompassLocateButton(true);
            }
        }

        private void EnableKioskCompassLocateButton(bool enable)
        {
            Opacity = enable ? 1.0f : 0.5f;
            IsEnabled = enable;
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
            m_compassLockedRotateTransform.Angle = Rad2Deg((float)-m_currentHeading);
            InvalidateOrientationTransforms();
        }

        private void InvalidateOrientationTransforms()
        {
            m_translateTransform.InvalidateProperty(TranslateTransform.XProperty);
            m_translateTransform.InvalidateProperty(TranslateTransform.YProperty);

            m_rotateTransform.InvalidateProperty(RotateTransform.AngleProperty);
            m_compassLockedRotateTransform.InvalidateProperty(RotateTransform.AngleProperty);
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

            m_rotateTransform.Angle = Rad2Deg(-headingAngleRadians);
        }

        private void InitialiseTransforms()
        {
            var transformGroup = new TransformGroup();
            UpdateOrientationTransform(0.0f);

            m_rotateTransform.CenterX = m_compassNew.Width / 2;
            m_rotateTransform.CenterY = m_compassNew.Height / 2;

            transformGroup.Children.Add(m_rotateTransform);
            transformGroup.Children.Add(m_translateTransform);
            m_compassNew.RenderTransform = transformGroup;
            m_compassNew.Visibility = Visibility.Visible;
        }

        private static float Rad2Deg(float rads)
        {
            return rads * 180.0f / (float) Math.PI;
        }
    }
}
