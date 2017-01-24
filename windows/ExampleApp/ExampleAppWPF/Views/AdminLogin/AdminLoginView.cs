using System;
using System.Windows;
using System.Windows.Controls;

using ExampleApp;
using ExampleApp.AdminLogin.View;

namespace ExampleAppWPF
{
    class AdminLoginView : ControlBase
    {
        public delegate void OnHideEvent();
        public OnHideEvent OnHide;

        private const int MaxPasswordLength = 4;

        private IntPtr m_nativeCallerPointer = IntPtr.Zero;
        private MainWindow m_currentWindow;
        private ManagedAdminLoginView m_adminLoginView;

        private PasswordBox m_passwordBox;
        private Border m_passwordBorder;

        static AdminLoginView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(
                typeof(AdminLoginView),
                new FrameworkPropertyMetadata(typeof(AdminLoginView)));
        }

        public AdminLoginView()
        {
        }

        public AdminLoginView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;
            Visibility = Visibility.Collapsed;
            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);
        }

        public void Initialise(string adminPassword)
        {
            m_adminLoginView = new ManagedAdminLoginView();
            m_adminLoginView.InitNative(GetType(), this, adminPassword);
        }

        void AddButtonClickHandlers(PasswordBox passwordBox)
        {
            foreach (var button in ViewHelpers.FindChildrenOfType<Button>(this))
            {
                button.Loaded += (sender, ev) =>
                {
                    string digit = button.Content?.ToString();
                    if (IsPasswordButtonLabel(digit))
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
            m_passwordBox = (PasswordBox)GetTemplateChild("PasswordBox");
            m_passwordBox.MaxLength = MaxPasswordLength;
            ((Button)GetTemplateChild("Ok")).Click += (o, e) => OnOkClicked(m_passwordBox);
            ((Button)GetTemplateChild("Del")).Click += (o, e) => OnDelClicked(m_passwordBox);
            ((Button)GetTemplateChild("Close")).Click += (o, e) => OnCloseClicked();
            AddButtonClickHandlers(m_passwordBox);
        }

        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void Dismiss()
        {
            Visibility = Visibility.Collapsed;
            m_passwordBox.Password = String.Empty;
            OnHide?.Invoke();
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
            if (m_nativeCallerPointer.Equals(IntPtr.Zero))
            {
                m_adminLoginView.HandleOkClicked(passwordBox.Password);
            }
            else
            {
                AdminLoginCLI.HandleOkClicked(m_nativeCallerPointer, passwordBox.Password);
            }
        }

        private void OnDelClicked(PasswordBox passwordBox)
        {
            int length = passwordBox.Password.Length - 1;
            passwordBox.Password = length > 0 ? passwordBox.Password.Substring(0, length) : String.Empty;
            ClearErrorIndicator();
        }

        private void OnCloseClicked()
        {
            Dismiss();
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

        private bool IsPasswordButtonLabel(string digit)
        {
            int digitValue;
            return int.TryParse(digit, out digitValue);
        }
    }
}
