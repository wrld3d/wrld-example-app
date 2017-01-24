using System;
using System.Windows;
using System.Windows.Controls;

namespace ExampleAppWPF
{
    class AdminLoginView : ControlBase
    {
        public delegate void OnHideEvent();
        public OnHideEvent OnHide;

        private const int MaxPasswordLength = 4;

        private string m_adminPassword;
        private PasswordBox m_passwordBox;
        private Border m_passwordBorder;

        static AdminLoginView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(
                typeof(AdminLoginView),
                new FrameworkPropertyMetadata(typeof(AdminLoginView)));
        }

        public AdminLoginView(string adminPassword)
        {
            m_adminPassword = adminPassword;
        }

        void AddButtonClickHandlers()
        {
            foreach (var button in ViewHelpers.FindChildrenOfType<Button>(this))
            {
                button.Loaded += (sender, ev) =>
                {
                    string digit = button.Content?.ToString();
                    if (IsPasswordButtonLabel(digit))
                    {
                        button.Click += (o, e) => OnKeyClicked(digit);
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
            ((Button)GetTemplateChild("Ok")).Click += (o, e) => OnOkClicked();
            ((Button)GetTemplateChild("Del")).Click += (o, e) => OnDelClicked();
            ((Button)GetTemplateChild("Close")).Click += (o, e) => OnCloseClicked();
            AddButtonClickHandlers();
        }

        public void Dismiss()
        {
            Visibility = Visibility.Collapsed;
            if (m_passwordBox != null)
            {
                m_passwordBox.Password = String.Empty;
            }
            OnHide?.Invoke();
        }

        public void Show()
        {
            ClearErrorIndicator();
            Visibility = Visibility.Visible;
        }

        private void OnOkClicked()
        {
            if (m_adminPassword == m_passwordBox.Password)
            {
                Application.Current.Shutdown();
            }
            else
            {
                SetErrorIndicator();
            }
        }

        private void OnDelClicked()
        {
            int length = m_passwordBox.Password.Length - 1;
            m_passwordBox.Password = length > 0 ? m_passwordBox.Password.Substring(0, length) : String.Empty;
            ClearErrorIndicator();
        }

        private void OnCloseClicked()
        {
            Dismiss();
        }

        private void OnKeyClicked(string digit)
        {
            if (m_passwordBox.Password.Length < MaxPasswordLength)
            {
                ClearErrorIndicator();
                m_passwordBox.Password += digit;
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
