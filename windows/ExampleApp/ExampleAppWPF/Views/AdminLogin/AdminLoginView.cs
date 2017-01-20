using System;
using System.Windows;
using System.Windows.Controls;

using ExampleApp;

namespace ExampleAppWPF
{
    class AdminLoginView : ControlBase
    {
        private const int MaxPasswordLength = 4;

        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;

        private Border m_passwordBorder;

        static AdminLoginView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(
                typeof(AdminLoginView),
                new FrameworkPropertyMetadata(typeof(AdminLoginView)));
        }

        public AdminLoginView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            Visibility = Visibility.Collapsed;
            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);
        }

        void AddButtonClickHandlers(PasswordBox passwordBox)
        {
            foreach (var button in ViewHelpers.FindChildrenOfType<Button>(this))
            {
                button.Loaded += (sender, ev) =>
                {
                    int digitValue;
                    string digit = button.Content?.ToString();
                    if (int.TryParse(digit, out digitValue))
                    {
                        button.Click += (o, e) => OnKeyClicked(passwordBox, digit);
                    }
                };
            }
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            m_passwordBorder = (Border)GetTemplateChild("PasswordBorder");
            PasswordBox passwordBox = (PasswordBox)GetTemplateChild("PasswordBox");
            passwordBox.MaxLength = MaxPasswordLength;
            ((Button)GetTemplateChild("Ok")).Click += (o, e) => OnOkClicked(passwordBox);
            ((Button)GetTemplateChild("Del")).Click += (o, e) => OnDelClicked(passwordBox);
            ((Button)GetTemplateChild("Close")).Click += (o, e) => OnCloseClicked();
            AddButtonClickHandlers(passwordBox);
        }

        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void Dismiss()
        {
            Visibility = Visibility.Collapsed;
        }

        public void Show()
        {
            ClearErrorIndicator();
            Visibility = Visibility.Visible;
        }

        public void OnPasswordAccepted(bool isAccepted)
        {
            if (isAccepted)
            {
                Application.Current.Shutdown();
            }
            else
            {
                SetErrorIndicator();
            }
        }

        private void OnOkClicked(PasswordBox passwordBox)
        {
            AdminLoginCLI.HandleOkClicked(m_nativeCallerPointer, passwordBox.Password);
        }

        private void OnDelClicked(PasswordBox passwordBox)
        {
            int length = passwordBox.Password.Length - 1;
            passwordBox.Password = length > 0 ? passwordBox.Password.Substring(0, length) : String.Empty;
            ClearErrorIndicator();
        }

        private void OnCloseClicked()
        {
            Visibility = Visibility.Collapsed;
        }

        private void OnKeyClicked(PasswordBox passwordBox, string digit)
        {
            if (passwordBox.Password.Length < MaxPasswordLength)
            {
                ClearErrorIndicator();
                passwordBox.Password += digit;
            }
        }

        private void ClearErrorIndicator()
        {
            VisualStateManager.GoToState(this, "Normal", true);
        }

        private void SetErrorIndicator()
        {
            VisualStateManager.GoToState(this, "Error", true);
        }
    }
}
