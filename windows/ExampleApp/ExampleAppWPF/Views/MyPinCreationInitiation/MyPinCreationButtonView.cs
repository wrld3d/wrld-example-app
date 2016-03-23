using System;
using System.Windows;
using System.Windows.Media;
using ExampleApp;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    /// <summary>
    /// Follow steps 1a or 1b and then 2 to use this custom control in a XAML file.
    ///
    /// Step 1a) Using this custom control in a XAML file that exists in the current project.
    /// Add this XmlNamespace attribute to the root element of the markup file where it is 
    /// to be used:
    ///
    ///     xmlns:MyNamespace="clr-namespace:ExampleAppWPF"
    ///
    ///
    /// Step 1b) Using this custom control in a XAML file that exists in a different project.
    /// Add this XmlNamespace attribute to the root element of the markup file where it is 
    /// to be used:
    ///
    ///     xmlns:MyNamespace="clr-namespace:ExampleAppWPF;assembly=ExampleAppWPF"
    ///
    /// You will also need to add a project reference from the project where the XAML file lives
    /// to this project and Rebuild to avoid compilation errors:
    ///
    ///     Right click on the target project in the Solution Explorer and
    ///     "Add Reference"->"Projects"->[Browse to and select this project]
    ///
    ///
    /// Step 2)
    /// Go ahead and use your control in the XAML file.
    ///
    ///     <MyNamespace:MyPinCreationView/>
    ///
    /// </summary>
    public class MyPinCreationButtonView : ButtonBase
    {
        private IntPtr m_nativeCallerPointer;
    
        private double m_yPosActive;
        private double m_yPosInactive;
        private bool m_isFirstLayout = true;
        private double m_stateChangeAnimationTimeMilliseconds = 200;

        static MyPinCreationButtonView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(MyPinCreationButtonView), new FrameworkPropertyMetadata(typeof(MyPinCreationButtonView)));
        }

        public MyPinCreationButtonView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            Click += MyPinCreationButtonView_Click;
            Loaded += PerformLayout;

            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged += PerformLayout;
            mainWindow.MainGrid.Children.Add(this);
        }

        private void MyPinCreationButtonView_Click(object sender, RoutedEventArgs e)
        {
            MyPinCreationViewCLIMethods.StartButtonPressed(m_nativeCallerPointer);
        }
        
        private void PerformLayout(object sender, RoutedEventArgs e)
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
                ConversionHelpers.AndroidToWindowsDip(32) + viewWidth * 0.5,
                layoutY);

            RenderTransform = transform;
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
