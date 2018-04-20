using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    class InteriorStreamingDialogView : Control
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_mainWindow;

        private FrameworkElement m_mainContainer;
        private StackPanel m_interiorStreamingDialogView;

        private Image m_spinnerImage;
        private Image m_loadedImage;

        static InteriorStreamingDialogView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(InteriorStreamingDialogView), new FrameworkPropertyMetadata(typeof(InteriorStreamingDialogView)));
        }

        public InteriorStreamingDialogView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_mainWindow = (MainWindow)Application.Current.MainWindow;
            m_mainWindow.MainGrid.Children.Add(this);

            Visibility = Visibility.Hidden;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            m_mainContainer = (FrameworkElement)GetTemplateChild("MainContainer");
            m_interiorStreamingDialogView = (StackPanel)GetTemplateChild("InteriorStreamingDialogView");

            m_spinnerImage = (Image)GetTemplateChild("SpinnerImage");
            m_loadedImage = (Image)GetTemplateChild("LoadedImage");
        }

        public void Destroy()
        {
            m_mainWindow.MainGrid.Children.Remove(this);
        }

        public void OpenInteriorStreamingDialogView()
        {
            m_mainWindow.DisableInput();
            m_mainWindow.IsEnabled = false;

            Visibility = Visibility.Visible;

            m_spinnerImage.Visibility = Visibility.Visible;
            m_loadedImage.Visibility = Visibility.Collapsed;

            m_mainContainer.BeginAnimation(UIElement.OpacityProperty, FadeInAnimation());
        }

        public void DismissInteriorStreamingDialogView()
        {
            m_spinnerImage.Visibility = Visibility.Collapsed;
            m_loadedImage.Visibility = Visibility.Visible;

            m_mainContainer.BeginAnimation(UIElement.OpacityProperty, FadeOutAnimation(2000));
        }

        public void CancelInteriorStreamingDialogView()
        {
            m_mainContainer.BeginAnimation(UIElement.OpacityProperty, FadeOutAnimation(0));
        }

        public DoubleAnimation FadeInAnimation()
        {
            DoubleAnimation fadeInAnimation = new DoubleAnimation(0.0f, 1.0f, TimeSpan.FromMilliseconds(500));
            return fadeInAnimation;
        }

        public DoubleAnimation FadeOutAnimation(int fadeOutDelay)
        {
            DoubleAnimation fadeOutAnimation = new DoubleAnimation(1.0f, 0.0f, TimeSpan.FromMilliseconds(500));
            fadeOutAnimation.BeginTime = TimeSpan.FromMilliseconds(fadeOutDelay);
            fadeOutAnimation.Completed += (sender, eventArgs) =>
            {
                Visibility = Visibility.Hidden;
                m_mainWindow.IsEnabled = true;
                m_mainWindow.EnableInput();
            };

            return fadeOutAnimation;
        }
    }
}
