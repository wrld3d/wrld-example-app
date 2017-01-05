using System;
using System.Windows;

namespace ExampleAppWPF
{
    class AttractModeOverlayView : ControlBase
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;

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

        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void OnAttractModeStart()
        {
            Visibility = Visibility.Visible;
        }

        public void OnAttractModeStop()
        {
            Visibility = Visibility.Collapsed;
        }
    }
}
