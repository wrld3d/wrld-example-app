using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public class GpsMarkerTutorialView : Control
    {
        protected Storyboard m_fadeInAnim;
        protected Storyboard m_fadeOutAnim;

        static GpsMarkerTutorialView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(GpsMarkerTutorialView), new FrameworkPropertyMetadata(typeof(GpsMarkerTutorialView)));
        }

        public GpsMarkerTutorialView(IntPtr nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);

            Opacity = 0;
        }

        public override void OnApplyTemplate()
        {
            m_fadeInAnim = ((Storyboard)Template.Resources["FadeIn"]).Clone();
            m_fadeOutAnim = ((Storyboard)Template.Resources["FadeOut"]).Clone();
        }

        public void UpdateScreenLocation(float x, float y)
        {
            Point currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));

            MainWindow mainWindow = (MainWindow) Application.Current.MainWindow;
            double screenHeight = mainWindow.MainGrid.ActualHeight;
            double screenWidth = mainWindow.MainGrid.ActualWidth;
            double marginX = 25;

            TranslateTransform transform = new TranslateTransform(x - (screenWidth * 0.5f) + (ActualWidth * 0.5f) + marginX,
                                                                  y - (screenHeight * 0.5f));
            RenderTransform = transform;
        }

        public void AnimateToActive()
        {
            m_fadeOutAnim.Stop();
            m_fadeInAnim.Begin(this);
        }

        public void AnimateToInactive()
        {
            m_fadeInAnim.Stop();
            m_fadeOutAnim.Begin(this);
        }
    }
}
