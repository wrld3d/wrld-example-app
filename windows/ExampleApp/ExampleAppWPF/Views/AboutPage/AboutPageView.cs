using System;
using System.Windows;
using System.Linq;
using ExampleApp;
using System.Diagnostics;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Navigation;
using System.Windows.Documents;

namespace ExampleAppWPF
{
    class AboutPageView : Control
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;

        private TextBlock m_aboutTextView;
        private Button m_closeButton;
        private FrameworkElement m_mainContainer;
        private ScrollViewer m_AboutPageView;


        static AboutPageView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(AboutPageView), new FrameworkPropertyMetadata(typeof(AboutPageView)));
        }

        public AboutPageView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            Visibility = Visibility.Hidden;
        }

        private DependencyObject CheckAndGetProperty(string name)
        {
            var prop = GetTemplateChild(name);
            Debug.Assert(prop != null, "Property cannot be found!!");
            return prop;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            m_aboutTextView = CheckAndGetProperty("AppText") as TextBlock;
            m_closeButton = CheckAndGetProperty("CloseButton") as Button;

            m_closeButton.Click += OnCloseClicked;
            m_mainContainer = (FrameworkElement)GetTemplateChild("MainContainer");

            m_mainContainer.MouseDown += OnContainerMouseDown;

            m_AboutPageView = (ScrollViewer)GetTemplateChild("AboutPageView");
            m_AboutPageView.TouchDown += OnPinDetailsTouchDown;  
            m_AboutPageView.TouchUp += OnPinDetailsTouchUp;
            m_AboutPageView.ManipulationBoundaryFeedback += OnPinDetailsBoundaryFeedback;

            ((Hyperlink)GetTemplateChild("LinkTos")).RequestNavigate += RequestNavigate;
            ((Hyperlink)GetTemplateChild("LinkPrivacy")).RequestNavigate += RequestNavigate;
            ((Hyperlink)GetTemplateChild("LinkLegal")).RequestNavigate += RequestNavigate;
            ((Hyperlink)GetTemplateChild("LinkTeam")).RequestNavigate += RequestNavigate;
        }

        private void OnPinDetailsBoundaryFeedback(object sender, ManipulationBoundaryFeedbackEventArgs e)
        {
            e.Handled = true;
        }

        private void OnPinDetailsTouchUp(object sender, TouchEventArgs e)
        {
            m_AboutPageView.ReleaseTouchCapture(e.TouchDevice);
        }

        private void OnPinDetailsTouchDown(object sender, TouchEventArgs e)
        {
            m_aboutTextView.CaptureTouch(e.TouchDevice);
        }

        private void OnContainerMouseDown(object sender, MouseButtonEventArgs e)
        {
            e.Handled = true;
        }

        private void OnCloseClicked(object sender, RoutedEventArgs e)
        {
            AboutPageCLI.CloseButtonClicked(m_nativeCallerPointer);
        }

        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void DisplayContent(string content)
        {
            m_aboutTextView.Text = content;
        }

        public void OpenAboutPage()
        {
            Visibility = Visibility.Visible;
            m_currentWindow.DisableInput();
        }

        public void DismissAboutPage()
        {
            Visibility = Visibility.Hidden;
            m_currentWindow.EnableInput();
        }

        private void RequestNavigate(object sender, RequestNavigateEventArgs e)
        {
            Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri));
            e.Handled = true;
        }
    }
}
