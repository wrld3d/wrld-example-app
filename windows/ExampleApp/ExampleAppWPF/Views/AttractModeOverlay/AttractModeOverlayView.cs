using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    class AttractModeOverlayView : ControlBase
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;
        private Storyboard m_resetBannerTransform;
        private Storyboard m_hideAnimation;

        static AttractModeOverlayView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(AttractModeOverlayView), new FrameworkPropertyMetadata(typeof(AttractModeOverlayView)));
        }

        public AttractModeOverlayView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            Visibility = Visibility.Collapsed;
            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_hideAnimation = (Storyboard)FindResource("HideAnimation");
            m_resetBannerTransform = (Storyboard)FindResource("Reload");
            RegisterName("border", GetTemplateChild("border"));
            RegisterName("title", GetTemplateChild("title"));
            RegisterName("subtitle", GetTemplateChild("subtitle"));
        }

        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void OnAttractModeStart()
        {
            if (m_resetBannerTransform != null)
            {
                m_resetBannerTransform.Seek(TimeSpan.Zero);
                m_resetBannerTransform.Begin(this);
            }
            Visibility = Visibility.Visible;
        }

        public void OnAttractModeStop()
        {
            m_hideAnimation?.Stop();
            Visibility = Visibility.Collapsed;
        }

        public void OnAttractModeExiting()
        {
            m_hideAnimation.Seek(TimeSpan.Zero);
            m_hideAnimation.Begin(this);
        }
    }
}
